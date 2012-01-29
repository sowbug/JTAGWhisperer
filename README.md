The JTAG Whisperer
==================

A crude attempt at teaching an Arduino to send JTAG commands in XSVF files.

Instructions
============

First of all, don't get your hopes up; it doesn't work yet. Now that that's out of the way... Set up your Arduino by downloading the sketch to it. Then hook up your target's JTAG pins as follows:

*  Pin 8 to TMS.
*  Pin 9 to TDI.
*  Pin 10 to TDO.
*  Pin 11 to TCK.

Do whatever you need to do to power the device. Try asking it its device ID as follows:

`send_xsvf XC9572XL/DeviceID.xsvf /dev/tty.wherever_your_arduino_is`

You should see a back-and-forth that ends up displaying your target's device ID. Although the DeviceID.xsvf file was generated with the XC9572XL in mind, it ought to fail in a meaningful way (noting that the returned ID doesn't match) with another device, which will at least show that the sketch and script are working.

Generate your own XSVF files using Xilinx iMPACT.

Credits
=======

By [Mike Tsao](http://www.sowbug.com/). Project on [GitHub](https://github.com/sowbug/JTAGWhisperer/).

Many thanks to [Ben](https://github.com/ben0109/XSVF-Player/), who adapted the
Xilinx XAPP058 code into something comprehensible.
