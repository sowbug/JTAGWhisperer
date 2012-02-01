/*
  The JTAG Whisperer: An Arduino library for JTAG.

  By Mike Tsao <http://github.com/sowbug>.

  Copyright © 2012 Mike Tsao. Use, modification, and distribution are
  subject to the BSD-style license as described in the accompanying
  LICENSE file.

  See README for complete attributions.
*/

#ifndef INCLUDE_JTAG_WHISPERER_SERIAL_COMM_H
#define INCLUDE_JTAG_WHISPERER_SERIAL_COMM_H

#include <Arduino.h>

#define DEBUG 0

class SerialComm {
 public:
 SerialComm()
   : read_ptr_(buffer_),
    write_ptr_(buffer_),
    stream_sum_(0),
    stream_count_(0) {
    Serial.begin(115200);
    Ready("XSVF");
  }

  virtual ~SerialComm() {
    Important("Checksum %lx/%lx.", stream_sum_, stream_count_);
    Quit("Exiting!");
  }

  uint8_t GetNextByte() {
    uint8_t c = get();
    stream_sum_ += c;
    ++stream_count_;
    return c;
  }

  void Important(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char tmp[128];
    vsnprintf(tmp, 128, format, args);

    va_end(args);

    Serial.print("! ");
    Serial.println(tmp);
  }

  void Ready(const char* message) {
    Serial.print("\nR");
    Serial.println(message);
  }

  void Quit(const char* message) {
    Serial.print("\nQ ");
    Serial.println(message);
  }

#if DEBUG == 1
  void Debug(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char tmp[128];
    vsnprintf(tmp, 128, format, args);

    va_end(args);

    Serial.print("D ");
    Serial.println(tmp);
  }

  void DebugBytes(const char* s, const uint8_t* p, uint8_t n)  {
    Serial.print("D ");
    Serial.print(s);
    print_bytes(p, n);
    Serial.println();
  }
#else
  void Debug(const char* format, ...) {}
  void DebugBytes(const char* s, const uint8_t* p, uint8_t n)  {}
#endif

 private:
  void p(const char *fmt, ... ) {
    char tmp[128];
    va_list args;
    va_start(args, fmt);
    vsnprintf(tmp, 128, fmt, args);
    va_end(args);
    Serial.print(tmp);
  }

  void print_bytes(const uint8_t* pb, uint8_t count) {
    while (count--) {
      p("%02x", *pb++);
    }
  }

  uint8_t get() {
    if (!available()) {
      fill();
    }
    uint8_t next_byte = *read_ptr_++;
    if (read_ptr_ == buffer_ + BUFFER_SIZE) {
      read_ptr_ -= BUFFER_SIZE;
    }
    return next_byte;
  }

  bool available() {
    return read_ptr_ != write_ptr_;
  }

  void fill() {
    load();
    if (!available()) {
      Ready("SEND");
      int delay_time = 5;
      do {
        delay(delay_time);
        load();
        delay_time = delay_time + delay_time;
      } while (!available());
    }
  }

  void load() {
    while (Serial.available() > 0) {
      uint8_t c = Serial.read();
      *write_ptr_++ = c;
      if (write_ptr_ == buffer_ + BUFFER_SIZE) {
        write_ptr_ -= BUFFER_SIZE;
      }
      if (!available()) {
        Important("Overran serial buffer");
      }
    }
  }

  enum { BUFFER_SIZE = 128 };
  uint8_t buffer_[BUFFER_SIZE];
  uint8_t* read_ptr_;
  uint8_t* write_ptr_;
  uint32_t stream_sum_;
  uint32_t stream_count_;
};

#endif  // INCLUDE_JTAG_WHISPERER_SERIAL_COMM_H
