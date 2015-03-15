http://1.bp.blogspot.com/-u3cLE44b0Vo/TnTgw4yxrdI/AAAAAAAAA_s/41UlbbtW9Dw/s400/DSCF5040.JPG

SerialCouple is an easy-to-use thermocouple adapter, allowing you to plug a standard K type thermocouple into a computer or other microcontroller project. Once plugged into a computer, the current thermocouple temperature can be easily monitored and logged to a file using any standard serial port software such as Hyperterminal or Putty.

These boards operate by controlling a Maxim thermocouple ADC with an AVR microcontroller, which then sends the readings out the relatively standard 6 pin 3.3V serial port. This means, in addition to a fully populated SerialCouple board, you also will need:
  * An FTDI-compatible USB-to-serial adapter (i.e. [this one on AdaFruit](https://www.adafruit.com/products/284))
  * A thermocouple matching the ADC on the board.  The SerialCouple boards are normally populated with K type ADCs, which are the most typical junction type, being able to handle -200C to +1350C at the junction (although likely much less in the cladding, so check your specific thermocouple).  AdaFruit sells a [standard K thermocouple that would work](http://www.adafruit.com/products/270).  Slightly cheaper ones, and ones in other styles (encased in steel, etc), can be had on eBay.

[Initial announcement](http://kennethfinnegan.blogspot.com/2011/06/serialcouple-thermocouple-adc.html)

[Monitoring thermocouple temperature demo](http://kennethfinnegan.blogspot.com/2011/09/serialcouple-v1-demo.html)

[Monitoring oven temperature demo](http://kennethfinnegan.blogspot.com/2011/09/monitoring-oven-with-serialcouple.html)

Once all major hardware and software issues have been ironed out, I plan to make these available for sale.  If you would be interested in buying one when they become available, or have any questions, feel free to send me an email: kennethfinnegan2007@gmail.com.