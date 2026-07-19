#pragma once

#include "box.h"
#include <stdint.h>

struct bg_collision {
  uint8_t left : 2, right : 2, up : 2, down : 2;
};

void bg_next();
struct bg_collision bg_check_collision(struct box *box);
void bg_draw();
