#include "random.h"
#include <stdlib.h>

char *generate_random_data(uint32_t buf_size, uint32_t min, uint32_t max) {
  char *buf = malloc(sizeof(char) * buf_size);
  for (u_int32_t i = 0; i < buf_size; i++) {
    buf[i] = min + (rand() % (max - min));
  }
  return buf;
}