#include "random.h"
#include <stdlib.h>

char *generate_random_data(u_int32_t buf_size, u_int32_t min, u_int32_t max) {
  char *buf = malloc(sizeof(char) * buf_size);
  for (u_int32_t i = 0; i < buf_size; i++) {
    buf[i] = min + (rand() % (max - min));
  }
  return buf;
}