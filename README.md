The JTAG Whisperer
==================

A preliminary attempt at teaching an Arduino to send JTAG commands in XSVF files.

Instructions
============

Don't get your hopes up; it doesn't work yet. Now that that's out of the way...

Get a Xilinx XC9572XL CPLD. Set up your Arduino by downloading the sketch to it. Then hook up your CPLD's JTAG pins as follows:

*  Pin 8 to TMS.
*  Pin 9 to TDI.
*  Pin 10 to TDO.
*  Pin 11 to TCK.

Do whatever you need to do to power the CPLD (note that it's a 3.3-volt device!). Try asking it its device ID as follows, from the root of the source directory:

`./send_xsvf -p /dev/tty.your_arduino_serial_port XC9572XL/DeviceID.xsvf`

You should see a back-and-forth that ends up with a "Success" message. If you rebuild the sketch with the DEBUG messages enabled, you'll see the actual device ID that's reported.

Generate your own XSVF files using Xilinx iMPACT. You'll discover that programming your device probably doesn't work (yet).

Credits
=======

By [Mike Tsao](http://www.sowbug.com/). Project on [GitHub](https://github.com/sowbug/JTAGWhisperer/).

Many thanks to [Ben](https://github.com/ben0109/XSVF-Player/), who adapted the Xilinx XAPP058 code into something comprehensible. This code evolved from his project.
