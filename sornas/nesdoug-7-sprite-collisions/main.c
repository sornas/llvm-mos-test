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

enum color : uint8_t {
  DARKGRAY = 0x00,
  BLACK = 0x0f,
  LIGHTGRAY = 0x10,
  BLUE = 0x12,
  YELLOW = 0x28,
  WHITE = 0x30,
};

const char text[] = "Sprite collisions";

const uint8_t palette_bg[16] = {
    BLACK, DARKGRAY, LIGHTGRAY, WHITE, //
    0x00,  0x00,     0x00,      0x00,  //
    0x00,  0x00,     0x00,      0x00,  //
    0x00,  0x00,     0x00,      0x00,  //
};

const uint8_t palette_sp[16] = {
    BLACK, BLACK, BLACK, YELLOW, //
    BLACK, BLACK, BLACK, BLUE,   //
    0x00,  0x00,  0x00,  0x00,   //
    0x00,  0x00,  0x00,  0x00,   //
};

struct box {
  uint8_t x, y;
  uint8_t w, h;
};

struct box box1 = {20, 20, 15, 15};
struct box box2 = {70, 20, 15, 15};

void move_box(struct box *box, uint8_t pad) {
  if (pad & PAD_LEFT)
    box->x -= 1;
  else if (pad & PAD_RIGHT)
    box->x += 1;

  if (pad & PAD_UP)
    box->y -= 1;
  else if (pad & PAD_DOWN)
    box->y += 1;
}

int main() {
  ppu_off();

  pal_bg(palette_bg);
  pal_spr(palette_sp);

  bank_spr(1);

  vram_adr(NTADR_A(7, 14));
  vram_write(text, sizeof(text));
  ppu_on_all();

  for (;;) {
    ppu_wait_nmi();

    move_box(&box1, pad_poll(0));
    move_box(&box2, pad_poll(1));

    if (check_collision(&box1, &box2))
      pal_col(0, DARKGRAY);
    else
      pal_col(0, BLACK);

    oam_clear();
    oam_meta_spr(box1.x, box1.y, yellow_sprite);
    oam_meta_spr(box2.x, box2.y, blue_sprite);
  }
}
