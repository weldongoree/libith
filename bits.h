#ifndef __LIBITH_BITS_H
#define __LIBITH_BITS_H

#include "alphabet.h"
#include <stdint.h>

typedef struct bytebits_ {
  uint8_t bits[8];
} bytebits;

bytebits explode_byte(uint8_t);

#endif
