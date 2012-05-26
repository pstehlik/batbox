batbox
======

Ultrasonic distance measurement with LED based distance indicator using Arduino

---
BatBox - Signaling distance measurements via LEDs using Arduino

Allows connecting 3-pin and 4-pin ultrasonic distance sensors and translating the distance into 
LEDs that light up when certain thresholds are hit.

For the 3-pin ultrasonic sensor I used a parallax PING))
   http://www.parallax.com/StoreSearchResults/tabid/768/txtSearch/PING/List/0/SortField/4/ProductID/92/Default.aspx

For the 4-pin ultrasonic sensor I used a HC-SR04 (much cheaper than the PING)
   http://www.amazon.com/gp/product/B004U8TOE6


Variable amount of LEDs can be set up by adding the LED pins to the led array and maintaining the distance (in inch) 
that triggers the LEDs pin to turn on.

If the LEDs should blink, the blinkDelay can be set to the blink frequency (in msec)

To debug your distance measurements you can attach the serial monitor.

Copyright May 26th 2012 - Philip Stehlik
No warranties given - use as is.

---
Resources:
Batman logo - http://uncyclopedia.wikia.com/wiki/File:Batman_logo_top.gif
