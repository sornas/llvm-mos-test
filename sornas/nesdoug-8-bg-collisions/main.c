#include "background.h"
#include "box.h"
#include "color.h"
#include "sprite_data.h"
#include <mapper.h>
#include <nes.h>
#include <nesdoug.h>
#include <neslib.h>
#include <stdint.h>

MAPPER_PRG_ROM_KB(32);
MAPPER_CHR_ROM_KB(128);
MAPPER_PRG_RAM_KB(8);
MAPPER_USE_VERTICAL_MIRRORING;

uint8_t pad1, pad1_new;
struct box box1 = {64, 80, 15, 14};

const uint8_t palette_bg[16] = {
    BLACK, DARKGRAY, LIGHTGRAY, WHITE, //
    0x00,  0x00,     0x00,      0x00,  //
    0x00,  0x00,     0x00,      0x00,  //
    0x00,  0x00,     0x00,      0x00,  //
};

const uint8_t palette_sp[16] = {
    BLACK, BLACK, BLACK, LIGHTYELLOW, //
    BLACK, BLACK, BLACK, MEDIUMBLUE,  //
    0x00,  0x00,  0x00,  0x00,        //
    0x00,  0x00,  0x00,  0x00,        //
};

void draw_sprites() {
  oam_clear();
  oam_meta_spr(box1.x, box1.y, yellow_sprite);
}

void movement() {
  struct box before;
  struct bg_collision collision;

  before = box1;
  move_box_x(&box1, pad1);

  collision = bg_check_collision(&box1);
  if (collision.left || collision.right)
    box1 = before;

  before = box1;
  move_box_y(&box1, pad1);

  collision = bg_check_collision(&box1);
  if (collision.up || collision.down)
    box1 = before;
}

int main() {
  ppu_off();

  pal_bg(palette_bg);
  pal_spr(palette_sp);

  bank_spr(1);
  set_scroll_y(0xff); // shift bg down 1 pixel, to match sprites
  bg_draw();

  for (;;) {
    ppu_wait_nmi();
    pad1 = pad_poll(0);
    pad1_new = get_pad_new(0);

    if (pad1_new & PAD_START) {
      bg_next();
      bg_draw();
    }

    movement();
    draw_sprites();
  }
}
