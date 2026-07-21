#include "color.h"
#include <mapper.h>
#include <nes.h>
#include <nesdoug.h>
#include <neslib.h>
#include <stdint.h>

MAPPER_PRG_ROM_KB(32);
MAPPER_CHR_ROM_KB(128);
MAPPER_PRG_RAM_KB(8);
MAPPER_USE_VERTICAL_MIRRORING;

const uint8_t palette_bg[16] = {
    BLACK, DARKGRAY, LIGHTGRAY, WHITE, //
    0x00,  0x00,     0x00,      0x00,  //
    0x00,  0x00,     0x00,      0x00,  //
    0x00,  0x00,     0x00,      0x00,  //
};

const uint8_t palette_sp[16] = {
    RGBI_BLACK, RGBI_RED, RGBI_GREEN, RGBI_BLUE, //
    0x00,       0x00,     0x00,       0x00,      //
    0x00,       0x00,     0x00,       0x00,      //
    0x00,       0x00,     0x00,       0x00,      //
};

int main() {
  ppu_off();
  pal_bg(palette_bg);
  pal_spr(palette_sp);
  bank_bg(0);
  bank_spr(1);
  ppu_on_all();

  for (;;) {
    ppu_wait_nmi();
  }
}
