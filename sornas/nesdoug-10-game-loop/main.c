#include "color.h"
#include <mapper.h>
#include <nes.h>
#include <nesdoug.h>
#include <neslib.h>
#include <stdint.h>
#include <string.h>

#define CLAMP(X, LO, HI) MIN(MAX((X), (LO)), (HI))

MAPPER_PRG_ROM_KB(32);
MAPPER_CHR_ROM_KB(128);
MAPPER_PRG_RAM_KB(8);
MAPPER_USE_VERTICAL_MIRRORING;

asm(".section .chr_rom_0_1,\"a\",@progbits");
asm(".incbin \"breaky.chr\"");

const uint8_t paddle_spr[] = {
    0,   0, 0x00, 0, //
    8,   0, 0x00, 0, //
    16,  0, 0x00, 0, //
    24,  0, 0x00, 0, //
    128,             //
};

const uint8_t ball_spr[] = {
    0,   0, 0x01, 0, //
    128,             //
};

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

const uint8_t background_data[223] = {
    0x01, 0x10, 0x01, 0x41, 0x00, 0x01, 0x0b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x0b, 0x10, 0x01, 0x03, 0x00, 0x00, 0x53, 0x43, 0x4f, 0x52, 0x45, 0x3a,
    0x30, 0x30, 0x00, 0x00, 0x10, 0x01, 0x03, 0x00, 0x00, 0x4c, 0x49, 0x56,
    0x45, 0x53, 0x3a, 0x30, 0x30, 0x00, 0x00, 0x10, 0x01, 0x43, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x01, 0x03, 0x00, 0x01,
    0x1b, 0x10, 0x01, 0x03, 0x00, 0x01, 0x1b, 0x10, 0x10, 0x00, 0x01, 0x07,
    0xc0, 0xf0, 0x01, 0x05, 0x30, 0x84, 0xa5, 0x01, 0x05, 0x21, 0x4c, 0x5f,
    0x01, 0x05, 0x13, 0xc8, 0xfa, 0x01, 0x05, 0x32, 0x84, 0xa5, 0x01, 0x05,
    0x21, 0x00, 0x01, 0x0e, 0x00, 0x01, 0x00};

const uint8_t collision_data[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, //
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, //
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, //
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, //
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, //
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, //
                                                    //
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  //
};

uint8_t collision_map[256];
uint8_t lives = 3;
uint8_t score = 0;

struct box {
  uint8_t x, y, w, h;
};

struct box ball = {0xff, 0xff, 5, 5};
const uint8_t ball_min = 0x10;
const uint8_t ball_max = 0xea;
const uint8_t ball_max_up = 0x30;
const uint8_t ball_max_down = 0xe0;
enum { BALL_OFF, BALL_STUCK, BALL_ACTIVE } ball_state;
enum { DIRECTION_UP, DIRECTION_DOWN } ball_direction;
uint8_t ball_wait = 0;
uint8_t ball_x_rel;

const uint8_t paddle_min = 0x10;
const uint8_t paddle_max = 0xd0;
struct box paddle = {0x75, paddle_max, 0x1f, 7};

void draw_background() {
  ppu_off();

  vram_adr(NAMETABLE_A);
  vram_unrle(background_data);
  memcpy(collision_map, collision_data, 256);

  vram_adr(NTADR_A(0, 6));

  for (uint8_t y = 0; y < 16; y++) {
    for (uint8_t x = 0; x < 16; x++) {
      uint8_t adr = (y << 4) + x;
      if ((x == 0) || (x == 15)) {
        // wall
        vram_put(0x10);
        vram_put(0x10);
      } else if (collision_map[adr]) {
        // block
        vram_put(0x11);
        vram_put(0x12);
      } else {
        // empty
        vram_put(0x00);
        vram_put(0x00);
      }
    }
  }

  ppu_on_all();
}

void draw_score() {
  one_vram_buffer('0' + (score / 10), NTADR_A(10, 3));
  one_vram_buffer('0' + (score % 10), NTADR_A(11, 3));
  one_vram_buffer('0', NTADR_A(26, 3));
  one_vram_buffer('0' + lives, NTADR_A(27, 3));
}

void draw_lives() {}

void hit_block(uint8_t x, uint8_t y, uint8_t addr) {
  // +1 point
  score++;
  // Ball should move down after bouncing
  ball_direction = DIRECTION_DOWN;
  ball.y += 3;

  // Don't collide with the tile
  collision_map[addr] = 0;

  // Don't draw the tile
  int ppu_addr = get_ppu_addr(0, x, y) & 0xfffe;
  one_vram_buffer(0x00, ppu_addr);
  ppu_addr++;
  one_vram_buffer(0x00, ppu_addr);
}

void update_paddle(uint8_t pad) {
  if (pad & PAD_LEFT)
    paddle.x = MAX(paddle.x - 2, paddle_min);
  if (pad & PAD_RIGHT)
    paddle.x = MIN(paddle.x + 2, paddle_max);

  switch (ball_state) {
  case BALL_OFF:
    ball_wait++;
    if (ball_wait > 60) {
      ball_state = BALL_STUCK;
      ball_x_rel = 0x0d;
      ball_wait = 0;
      return;
    }
    break;
  case BALL_STUCK:
    ball.x = paddle.x + ball_x_rel;
    ball.y = paddle.y - 4;

    if (pad & (PAD_A | PAD_B)) {
      ball_state = BALL_ACTIVE;
      ball_direction = DIRECTION_UP;
      ball.x = CLAMP(ball.x, ball_min, ball_max);
      break;
    }
    break;
  case BALL_ACTIVE:
    // Move ball, check ceiling, floor and paddle
    switch (ball_direction) {
    case DIRECTION_UP:
      ball.y -= 3;
      if (ball.y < ball_max_up)
        ball_direction = DIRECTION_DOWN;
      break;
    case DIRECTION_DOWN:
      ball.y += 3;

      if (ball.y > ball_max_down) {
        lives--;
        ball_state = BALL_OFF;
      }

      if (check_collision(&ball, &paddle)) {
        ball_state = BALL_STUCK;
        ball_x_rel = ball.x - paddle.x;
      }
      break;
    }

    // Check collision with blocks
    uint8_t x = (ball.x + 1) & 0xf0; // tiles are 16 px wide
    uint8_t y = (ball.y + 2) & 0xf8; // tiles are 8 px high
    uint8_t addr = (x << 4) + (((y - 0x30) << 1) & 0x0f);
    if (y < 0xaf) { // "y of 0x30 + 16 * 8 = b0. ball.y > b0 => off the c_map"
      if (collision_map[addr]) {
        hit_block(x, y, addr);
        break;
      }
    }

    // "Check a little more to the right"
    x = (ball.x + 4) & 0xf0;
    y = (ball.y + 2) & 0xf8;
    if (y < 0xaf) {
      uint8_t addr = (x << 4) + (((y - 0x30) << 1) & 0x0f);
      if (collision_map[addr]) {
        hit_block(x, y, addr);
        break;
      }
    }
    break;
  }

  if (ball_state == BALL_STUCK) {
  }
}

void draw_paddle() {
  oam_clear();
  oam_meta_spr(paddle.x, paddle.y, paddle_spr);
  oam_meta_spr(ball.x, ball.y, ball_spr);
}

int main() {
  ppu_off();
  pal_bg(palette_bg);
  pal_spr(palette_sp);

  bank_bg(0);
  bank_spr(1);

  set_scroll_y(0xff);
  draw_background();

  set_vram_buffer();

  for (;;) {
    ppu_wait_nmi();

    const uint8_t pad1 = pad_poll(0);

    draw_score();
    draw_lives();

    if (lives) {
      update_paddle(pad1);
      draw_paddle();
    } else {
      oam_clear();
    }
  }
}
