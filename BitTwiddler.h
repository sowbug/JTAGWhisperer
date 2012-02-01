/*
  The JTAG Whisperer: An Arduino library for JTAG.

  By Mike Tsao <http://github.com/sowbug>.

  Copyright © 2012 Mike Tsao. Use, modification, and distribution are
  subject to the BSD-style license as described in the accompanying
  LICENSE file.

  See README for complete attributions.
*/

#ifndef INCLUDE_JTAG_WHISPERER_BIT_TWIDDLER_H
#define INCLUDE_JTAG_WHISPERER_BIT_TWIDDLER_H

#include <Arduino.h>

// Knows how to set MCU-specific pins in a JTAG-relevant way.
class BitTwiddler {
 public:
 BitTwiddler() : portb_(0) {
    DDRB = TMS | TDI | TCK;
  }

  inline void pulse_clock() {
    clr_port(TCK);
    delayMicroseconds(1);
    set_port(TCK);
  }

  bool pulse_clock_and_read_tdo() {
    clr_port(TCK);
    delayMicroseconds(1);
    uint8_t pinb = PINB;
    set_port(TCK);
    return pinb & TDO;
  }

  void wait_time(unsigned long microsec) {
    unsigned long until = micros() + microsec;
    while (microsec--) {
      pulse_clock();
    }
    while (micros() < until) {
      pulse_clock();
    }
  }

  void set_tms() {
    set_port(TMS);
  }

  void clr_tms() {
    clr_port(TMS);
  }

  void set_tdi() {
    set_port(TDI);
  }

  void clr_tdi() {
    clr_port(TDI);
  }

 private:
  enum {
    TMS = _BV(PINB0),  // Arduino 8
    TDI = _BV(PINB1),  // Arduino 9
    TDO = _BV(PINB2),  // Arduino 10
    TCK = _BV(PINB3)   // Arduino 11
  };

  inline void write_portb_if_tck(uint8_t pin) {
    if (pin == TCK) {
      PORTB = portb_;
    }
  }

  inline void set_port(uint8_t pin) {
    portb_ |= pin;
    write_portb_if_tck(pin);
  }

  inline void clr_port(uint8_t pin) {
    portb_ &= ~pin;
    write_portb_if_tck(pin);
  }

  // The current PORTB state. We write this only when we twiddle TCK.
  uint8_t portb_;
};

#endif  // INCLUDE_JTAG_WHISPERER_BIT_TWIDDLER_H
