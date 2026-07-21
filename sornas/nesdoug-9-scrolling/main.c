#include "color.h"
#include <ines.h>
#include <mapper.h>
#include <nes.h>
#include <nesdoug.h>
#include <neslib.h>
#include <stdint.h>

// compressed bg data
#include "N0.h"
#include "N1.h"

MAPPER_PRG_ROM_KB(32);
MAPPER_CHR_ROM_KB(128);
MAPPER_PRG_RAM_KB(8);
MAPPER_USE_HORIZONTAL_MIRRORING;

const uint8_t palette_bg[16] = {
    BLACK, DARKGRAY, LIGHTGRAY, WHITE, //
    0x00,  0x00,     0x00,      0x00,  //
    0x00,  0x00,     0x00,      0x00,  //
    0x00,  0x00,     0x00,      0x00,  //
};

const uint8_t palette_sp[16] = {
    BLACK, BLACK, BLACK, RGBI_YELLOW, //
    BLACK, BLACK, BLACK, RGBI_RED,    //
    0x00,  0x00,  0x00,  0x00,        //
    0x00,  0x00,  0x00,  0x00,        //
};

// clang-format off
const uint8_t yellow_sprite[]={
    0,  0,0x10,0,
    8,  0,0x10,0|OAM_FLIP_H,
    0,  8,0x20,0,
    8,  8,0x20,0|OAM_FLIP_H,
  128
};

const uint8_t blue_sprite[]={
    0,  0,0x10,1,
    8,  0,0x10,1|OAM_FLIP_H,
    0,  8,0x20,1,
    8,  8,0x20,1|OAM_FLIP_H,
  128
};
// clang-format on

uint16_t scroll_x, scroll_y;
uint8_t sprite_x = 0x80, sprite_y = 0x80;

void update_scroll(uint8_t pad) {
  if (pad & PAD_LEFT)
    scroll_x -= 1;
  else if (pad & PAD_RIGHT)
    scroll_x += 1;

  if (pad & PAD_UP)
    scroll_y = sub_scroll_y(1, scroll_y);
  else if (pad & PAD_DOWN)
    scroll_y = add_scroll_y(1, scroll_y);

  set_scroll_x(scroll_x);
  set_scroll_y(scroll_y);
}

void draw_sprites() {
  oam_clear();
  oam_meta_spr(sprite_x, sprite_y, yellow_sprite);
  oam_spr(20, 20, 0xfe, 1);
  oam_spr(28, 20, (scroll_x & 0xff) >> 4, 1);
  oam_spr(36, 20, (scroll_x & 0x0f), 1);

  oam_spr(50, 20, 0xff, 1);
  oam_spr(58, 20, (scroll_y & 0xff) >> 4, 1);
  oam_spr(66, 20, (scroll_y & 0x0f), 1);
}

int main() {
  ppu_off();

  bank_bg(0);
  bank_spr(1);
  set_chr_bank_1(1); // otherwise sprites read from chr_0 ??
  pal_bg(palette_bg);
  pal_spr(palette_sp);

  set_mirroring(MIRROR_HORIZONTAL);
  vram_adr(NAMETABLE_A);
  vram_unrle(N0);
  vram_adr(NAMETABLE_C); // why not NAMETABLE_B here ??? NAMETABLE_D also works.
                         // maybe because they also get mirrored?
  vram_unrle(N1);

  ppu_on_all();

  for (;;) {
    ppu_wait_nmi();

    update_scroll(pad_poll(0));
    draw_sprites();
  }
}
