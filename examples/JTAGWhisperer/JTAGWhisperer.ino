/*
  The JTAG Whisperer: An Arduino library for JTAG.

  By Mike Tsao <http://github.com/sowbug>.

  Copyright © 2012 Mike Tsao. Use, modification, and distribution are
  subject to the BSD-style license as described in the accompanying
  LICENSE file.

  See README for complete attributions.
*/

#include <BitTwiddler.h>
#include <JTAGWhisperer.h>
#include <SerialComm.h>

void setup() {
}

// This is out of loop() so we get RAII without looping.
void do_it() {
  SerialComm serial_comm;
  BitTwiddler twiddler;
  JTAGWhisperer whisperer(serial_comm, twiddler);
  uint32_t instruction_count = 0;

  while (true) {
    uint8_t instruction = whisperer.read_next_instruction();
    if (!whisperer.handle_instruction(instruction)) {
      if (!whisperer.reached_xcomplete()) {
        serial_comm.Important("Failure at instruction #%d", instruction_count);
      }
      break;
    }
    ++instruction_count;
  }
  serial_comm.Important("Processed %d instructions.", instruction_count);
}

void loop() {
  do_it();
  while (true) {
  }
}
