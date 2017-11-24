Nokia 6610 LCD Display Driver for MSP430
=========================================

This is a library to interface Nokia 6610 (6100, 6610, 7210, 7250 and 5100) color LCD displays with MSP430s. The code is specific to the displays containing Philips PCF8833 controllers (see below for details).

Typical display modules available for a microcontroller/electronics hobbyist are monochrome LCD dotmatrix character and graphic displays.
While they usually serve the purpose, they're not particularly interesting, and very little can be done with them.
Moreover, apart from the simplest of the character displays, most others are fairly expensive.

Nokia 6610 (6100, 6610, 7210, 7250 and 5100) LCDs (and knock-offs) are 132x132 displays supporting 4096 colors, and for whatever reason, are easily available and very inexpensive.
You can usually buy one for less than the cost of an average microcontroller chip. And to top it all, they're fairly easy to interface with!

There are many projects available around the net for interfacing these displays with various microcontrollers. But there were none for interfacing them with MSP430s (which happen to be my favourite due to the [MSP430 Launchpad](http://processors.wiki.ti.com/index.php/MSP430_LaunchPad)s). This library addresses that.

These displays do have quirks of their own, but those are fairly minor compared to the advantages. One of the quirks is that these aren't made for hobbyists (obviously). Therefore, the connector is small, and delicate. While there are breakout boards available that make it easier to connect these, you still have to be careful not to put too much pressure on the connectors.

The other quirk is that these displays are driven by one of the two controllers: Philips PCF8833 or Epson S1D15G00. And it's not easy to tell which controller is in the display you've bought. There are minor differences in the controllers that can cause some confusion.

This driver is based largely on the information provided here: [http://www.sparkfun.com/tutorial/Nokia%206100%20LCD%20Display%20Driver.pdf](http://www.sparkfun.com/tutorial/Nokia%206100%20LCD%20Display%20Driver.pdf) and the [PCF8833 datasheet](http://google.com/?q=Philips%20PCF8833%20datasheet).
