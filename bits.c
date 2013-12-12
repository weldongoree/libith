#include "bits.h"

bytebits explode_byte(uint8_t byte)
{
  bytebits bb;
  bb.bits[0] = byte & 0x80;
  bb.bits[1] = byte & 0x40;
  bb.bits[2] = byte & 0x20;
  bb.bits[3] = byte & 0x10;
  bb.bits[4] = byte & 0x08;
  bb.bits[5] = byte & 0x04;
  bb.bits[6] = byte & 0x02;
  bb.bits[7] = byte & 0x01;
  return bb;
}

