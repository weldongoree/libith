#include "bits.h"

bytebits explode_byte(uint8_t byte)
{
  bytebits bb;
  bb.bits[0] = byte & 0x80 ? 1 : 0;
  bb.bits[1] = byte & 0x40 ? 1 : 0;
  bb.bits[2] = byte & 0x20 ? 1 : 0;
  bb.bits[3] = byte & 0x10 ? 1 : 0;
  bb.bits[4] = byte & 0x08 ? 1 : 0;
  bb.bits[5] = byte & 0x04 ? 1 : 0;
  bb.bits[6] = byte & 0x02 ? 1 : 0;
  bb.bits[7] = byte & 0x01 ? 1 : 0;
  return bb;
}

