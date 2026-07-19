#include "font/chr.h"
#include <mapper.h>
#include <nes.h>
#include <nesdoug.h>
#include <neslib.h>
#include <stdint.h>
#include <stdio.h>

typedef uint16_t addr;

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

void clear_display() {
  vram_adr(NTADR_A(0, 0));
  for (size_t i = 0; i < 32 * 30; i++) {
    vram_put(font_mapping[(size_t)' ']);
  }
}

void render_text(uint16_t line, uint16_t col, const char *str, size_t n) {
  for (size_t i = 0; i < n && str[i] != '\0'; i++) {
    char data = font_mapping[(size_t)str[i]];
    one_vram_buffer(data, NTADR_A(col + i, line));
  }
}

const uint8_t palette_bg[16] = {
    BLACK, LT_GY, DK_GY, WHITE, // grayscale
    BLACK, LT_GY, DK_GY, WHITE, // grayscale
    BLACK, LT_GY, DK_GY, WHITE, // grayscale
    0x0f,  0x16,  0x1a,  0x12,  // black red green blue
};

void update() {
  static int frame = 0;
  static int count = 0;

  frame++;
  if (frame > 10) {
    count++;
    printf("Asd %d\n", count);
    frame -= 10;
  }

  render_text(10, 10, "Hello world!!!!!", count);

  if (count > 100) {
    render_text(11, 7, "Are you still here ...", count - 100);
  }
  if (count > 120) {
    render_text(12, 9, "This is awkward...", count - 120);
  }
}

int main() {
  // Print to extension port, a debugger now.
  printf("Starting...");

  ppu_off();
  // Set the palette
  pal_bg(palette_bg);
  // Clear the display, initially.
  clear_display();

  // Set the vram buffer to update during nmi
  set_vram_buffer();
  ppu_on_all();

  for (;;) {
    ppu_wait_nmi();
    update();
  }
}
