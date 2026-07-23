#include "box.h"
#include <neslib.h>

void move_box_x(struct box *box, uint8_t pad) {
  if (pad & PAD_LEFT)
    box->x -= 1;
  else if (pad & PAD_RIGHT)
    box->x += 1;
}

void move_box_y(struct box *box, uint8_t pad) {
  if (pad & PAD_UP)
    box->y -= 1;
  else if (pad & PAD_DOWN)
    box->y += 1;
}
