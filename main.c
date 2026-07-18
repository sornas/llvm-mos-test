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
  BLACK = 0x0f,
  DK_GY = 0x00,
  LT_GY = 0x10,
  WHITE = 0x30,
};

const char text[] = "Hello World!";

const uint8_t palette[16] = {
    0x0f, 0x10, 0x20, 0x30, // grayscale
    0x0f, 0x10, 0x20, 0x30, // grayscale
    0x0f, 0x10, 0x20, 0x30, // grayscale
    0x0f, 0x10, 0x20, 0x30, // grayscale
};

int main() {
  ppu_off();

  pal_bg(palette);

  vram_adr(NTADR_A(10, 10));
  vram_write(text, sizeof(text) - 1);

  ppu_on_all();

  for (;;) {
    asm volatile("");
  }
}
