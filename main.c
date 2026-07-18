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

// clang-format off
const char font_mapping[256] = {
  ['0'] = 0,
  ['1'] = 1,
  ['2'] = 2,
  ['3'] = 3,
  ['4'] = 4,
  ['5'] = 5,
  ['6'] = 6,
  ['7'] = 7,
  ['8'] = 8,
  ['9'] = 9,
  ['a'] = 10,
  ['b'] = 11,
  ['c'] = 12,
  ['d'] = 13,
  ['e'] = 14,
  ['f'] = 15,
  ['g'] = 16,
  ['h'] = 17,
  ['i'] = 18,
  ['j'] = 19,
  ['k'] = 20,
  ['l'] = 21,
  ['m'] = 22,
  ['n'] = 23,
  ['o'] = 24,
  ['p'] = 25,
  ['q'] = 26,
  ['r'] = 27,
  ['s'] = 28,
  ['t'] = 29,
  ['u'] = 30,
  ['v'] = 31,
  ['w'] = 32,
  ['x'] = 33,
  ['y'] = 34,
  ['z'] = 35,
  ['!'] = 36,
  ['$'] = 37,
  [':'] = 38,
  [';'] = 38,
  ['-'] = 39,
  ['.'] = 40,
  ['\''] = 41,
  [','] = 42,
  // BLOCK CHARACTER HERE AT 43
  ['_'] = 44,
  [' '] = 45,
  // Repeat for large characters.
  ['A'] = 10,
  ['B'] = 11,
  ['C'] = 12,
  ['D'] = 13,
  ['E'] = 14,
  ['F'] = 15,
  ['G'] = 16,
  ['H'] = 17,
  ['I'] = 18,
  ['J'] = 19,
  ['K'] = 20,
  ['L'] = 21,
  ['M'] = 22,
  ['N'] = 23,
  ['O'] = 24,
  ['P'] = 25,
  ['Q'] = 26,
  ['R'] = 27,
  ['S'] = 28,
  ['T'] = 29,
  ['U'] = 30,
  ['V'] = 31,
  ['W'] = 32,
  ['X'] = 33,
  ['Y'] = 34,
  ['Z'] = 35,
};
// clang-format on

void clear_display() {
  vram_adr(NTADR_A(0, 0));
  for (size_t i = 0; i < 32 * 30; i++) {
    vram_put(font_mapping[(size_t)' ']);
  }
}

void render_text(uint16_t line, uint16_t col, const char *str, size_t n) {
  vram_adr(NTADR_A(col, line));
  for (size_t i = 0; i < n && str[i] != '\0'; i++) {
    char data = font_mapping[(size_t)str[i]];
    vram_put(data);
  }
}

const uint8_t palette_bg[16] = {
    BLACK, LT_GY, DK_GY, WHITE, // grayscale
    BLACK, LT_GY, DK_GY, WHITE, // grayscale
    BLACK, LT_GY, DK_GY, WHITE, // grayscale
    0x0f,  0x16,  0x1a,  0x12,  // black red green blue
};

void update() {
  ppu_off();

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

  ppu_on_all();
}

int main() {
  // Print to extension port, a debugger now.
  printf("Starting...");

  ppu_off();
  clear_display();
  pal_bg(palette_bg);
  ppu_on_all();

  for (;;) {
    ppu_wait_nmi();
    update();
  }
}
