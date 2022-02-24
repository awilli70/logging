#ifndef RAND_FUNCS
#define RAND_FUNCS

#include <stdint.h>

extern char *generate_random_data(u_int32_t bufsize, u_int32_t min,
                                  uint32_t max);

#endif
