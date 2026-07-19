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

const char text[] = "Sprites";

const uint8_t palette_bg[16] = {
    BLACK,
    DARKGRAY,
    LIGHTGRAY,
    WHITE,
};

const uint8_t palette_sp[16] = {
    BLACK,
    BLACK,
    BLACK,
    LIGHTYELLOW,
};

int main() {
  ppu_off();

  pal_bg(palette_bg);
  pal_spr(palette_sp);

  bank_spr(1);

  vram_adr(NTADR_A(7, 14));
  vram_write(text, sizeof(text));
  ppu_on_all();

  uint8_t x = 0x88, x2 = 0xa0, x3 = 0xc0, y = 0x40;

  for (;;) {
    ppu_wait_nmi();
    oam_clear();
    oam_spr(x, y, 0, 0);
    oam_meta_spr(x2, y, metasprite);
    oam_meta_spr(x3, y, metasprite2);
    y++;
  }
}
