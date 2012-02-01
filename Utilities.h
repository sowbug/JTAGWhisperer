/*
  The JTAG Whisperer: An Arduino library for JTAG.

  By Mike Tsao <http://github.com/sowbug>.

  Copyright © 2012 Mike Tsao. Use, modification, and distribution are
  subject to the BSD-style license as described in the accompanying
  LICENSE file.

  See README for complete attributions.
*/

#ifndef INCLUDE_JTAG_WHISPERER_UTILITIES_H
#define INCLUDE_JTAG_WHISPERER_UTILITIES_H

#include <stdio.h>
#include <Arduino.h>

#define BYTE_COUNT(bit_count) ((int)((bit_count + 7) >> 3))
#define BYTES(bits) ((int)((bits + 7) >> 3))
#define HANDLE(x) case x: return handle_##x()
#define NAME_FOR(x) case x: return #x;

#endif  // INCLUDE_JTAG_WHISPERER_UTILITIES_H
