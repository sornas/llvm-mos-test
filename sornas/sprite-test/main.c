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
    RGBI_RED, RGBI_GREEN, RGBI_BLUE, RGBI_YELLOW, //
    0x00,     0x00,       0x00,      0x00,        //
    0x00,     0x00,       0x00,      0x00,        //
    0x00,     0x00,       0x00,      0x00,        //
};

// Here's a neslib metasprite. It contains four bytes per sprite in the
// metasprite.
//
// - x offset of sprite
// - y offset of sprite
// - tile adress in data file
// - oam attribute
//
// The last element is 128 (EOF).
const uint8_t sprite_data[] = {
    0,  0, 0x02, 0, //
    0,  8, 0x12, 0, //
    8,  0, 0x03, 0, //
    8,  8, 0x13, 0, //
    128             //
};

int main() {
  ppu_off();
  pal_bg(palette_bg);
  pal_spr(palette_sp);
  bank_spr(0);
  bank_bg(1); // point bg to empty data
  ppu_on_all();

  for (;;) {
    ppu_wait_nmi();

    oam_clear();
    // This metasprite is drawn manually. The sprite data is 16x16 tiles, so the
    // first nibble is Y, the second X
    oam_spr(10, 10, 0x00, 0);
    oam_spr(18, 10, 0x01, 0);
    oam_spr(10, 18, 0x10, 0);
    oam_spr(18, 18, 0x11, 0);

    oam_meta_spr(40, 40, &sprite_data);
  }
}
