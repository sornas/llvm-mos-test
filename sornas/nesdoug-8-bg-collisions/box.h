#pragma once

#include <stdint.h>

struct box {
  uint8_t x, y;
  uint8_t w, h;
};

void move_box_x(struct box *box, uint8_t pad);
void move_box_y(struct box *box, uint8_t pad);
