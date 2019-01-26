# diynsxled

DIY LEDS for your NSX

# Pre-requisites
1. A 3D printer is required to print the brackets and enclosure
2. A custom PCB can be made for about $30 from www.jlcpcb.com
3. Familiarize yourself with Arduino programming
4. Comfortable soldering with beginner skills.

# Risks
The NSX taillights are old, and so there is a real risk that you'll break something. The bolts that connect to the car are fragile, the acrylic lenses are prone to cracking, etc. Just know that it's a real possibility that something can go wrong. Proceed at your own risk. 

Playing with high amperage is dangerous! Both tail lights on at full red brightness can use 5A. If you use White, even more. 

# Reading (optional)
* [NeoPixels UberGuide](https://learn.adafruit.com/adafruit-neopixel-uberguide/the-magic-of-neopixels)
* [Install Arduino IDE](https://www.arduino.cc/en/Guide/HomePage)
* [Arduino bootloader](https://learn.sparkfun.com/tutorials/installing-an-arduino-bootloader/all)

# Components

The component list links to websites for the number of items you would need to order. They are usually in sold in bundles and I have also listed the actual qty needed (if different) in case you can source these parts individually. For example, you need 6 diodes, but they only sell them in packs of 20.

If you're familiar with digikey and mouser, you can order a lot of these parts from there, too. However, some things were more expensive. 

### Amazon
* When installing LEDs, you'll get fast blinking turnsignals unless you use load resistors or the bulb sockets (both are listed as optional, pick one if you want regular speed blinking).
* The AVR programmer is optional, explained later on, but allows the Arduino to be programmed to wake up instantly without delay. 

|  Component | QTY | Actual QTY items needed | Notes |
| --- | --- | --- | --- |
|  [Pololu 5v regulator](https://www.amazon.com/Pololu-Step-Down-Voltage-Regulator-D24V90F5/dp/B01IGGR6TW?tag=diynsxled-20) | 1 |  |  |
|  [5mm terminals 2/3P pack](https://www.amazon.com/Gikfun-Terminal-Connector-Arduino-EK8365/dp/B015E3O4GS?tag=diynsxled-20) | 1 | 6x2pin, 2x3pin |  |
|  [2.5mm terminals 3P pack](https://www.amazon.com/Simpo-Terminal-300v10a-Drawing-Drawing/dp/B018OTAKJO?tag=diynsxled-20) | 1 | 28 |  |
|  [Capacitor](https://www.amazon.com/gp/product/B01DYJEHZ2?tag=diynsxled-20) | 1 |  |  |
|  [5A diode](https://www.amazon.com/gp/product/B079KCWPWQ?tag=diynsxled-20) | 1 | 6 |  |
|  [Resistors](https://www.amazon.com/gp/product/B072BL2VX1?tag=diynsxled-20) | 1 | 2x450, 5x4.7k, 5x1k |  |
|  [18ga Wire red](https://www.amazon.com/gp/product/B000HACYOS?tag=diynsxled-20) | 1 | optional if you have wire |  |
|  [18 ga Wire black](https://www.amazon.com/gp/product/B003J699RW?tag=diynsxled-20) | 1 | optional if you have wire |  |
|  [18 ga Wire green](https://www.amazon.com/gp/product/B003J65A84?tag=diynsxled-20) | 1 | optional if you have wire |  |
|  [18 ga wire pack](https://www.amazon.com/gp/product/B00N51OO7Q?tag=diynsxled-20) | 1 | optional if you have wire |  |
|  [Crimp tool](https://www.amazon.com/gp/product/B00OMM4YUY?tag=diynsxled-20) | 1 | optional, use with the cycle terminal crimps |  |
|  [Plug connectors](https://www.amazon.com/gp/product/B07DB7X9R9?tag=diynsxled-20) | 1 | optional | I prefer the ones from CycleTerminal, but you can also use these.|
|  [DC power supply](https://www.amazon.com/gp/product/B071RNT1CD?tag=diynsxled-20) | 1 | optional, great for testing with or use a spare car battery |  |
|  [Socket adapters DIP](https://www.amazon.com/QLOUNI-122Pcs-2-54mm-Sockets-Adaptor/dp/B07CJ87NVT?tag=diynsxled-20) | 1 | Optional [1x6pin, 1x16pin] | For chips from digikey |
|  [Stacking headers for Nano](https://www.amazon.com/Shield-Stacking-Header-Arduino-Pack/dp/B0756KRCFX?tag=diynsxled-20) | 1 |  |  |
|  [Arduino Nano (Brand name)](https://www.amazon.com/Arduino-A000005-ARDUINO-Nano/dp/B0097AU5OU?tag=diynsxled-20) | 1 |  | Brand name. Knock off just as good.|
|  [Arduino Nano (china)](https://www.amazon.com/ATmega328P-Microcontroller-Board-Cable-Arduino/dp/B00NLAMS9C?tag=diynsxled-20) | 1 |  |  |
|  [AVR Programmer](https://www.amazon.com/gp/product/B004G54E9I?tag=diynsxled-20) | 1 | Optional |  |
|  [Turn Signal Bulbs](https://www.amazon.com/gp/product/B07DFYSM5J?tag=diynsxled-20) | 1 | Optional |  |
|  [Load resistor](https://www.amazon.com/Resistors-Signal-License-Warning-Cancellor-x/dp/B004EDF8HY/ref=sr_1_8?tag=diynsxled-20) | 1 | Optional |  |
|  [5 wire connector](https://www.amazon.com/Wago-222-415-LEVER-NUTS-Conductor-Connectors/dp/B07CN5974J?tag=diynsxled-20) | 1 | 5, optional | There are better ways to splice wires together |
|  [Morimoto Butyl](https://www.amazon.com/RetroRubber-Grade-Butyl-Headlight-Sealant/dp/B01N5PM29J?tag=diynsxled-20) | 1 |  |  |

**Note that the Amazon links have an affiliate link attached to them. This helps me recoupe some of the cost of development, and future dev work.* 



### Digikey
|  Component | QTY Needed | Actual items needed | Notes |
| --- | --- | --- | --- |
|  [Pin headers for Pololu regulator](https://www.digikey.com/products/en?mpart=TSW-202-07-T-S&v=612) | 2 |  |  |
|  [Opto 4ch](https://www.digikey.com/product-detail/en/PS2501-4-A/PS2501-4A-ND/770687) | 1 |  |  |
|  [Opto 2ch](https://www.digikey.com/product-detail/en/4N35/4N35-ND/1738522) | 1 |  |  |

### Aliexpress
* The LED panels are cheapest on Aliexpress. With regards to quality issues, I feel that all the panels i've bought have for the most part been great. Only 2 died on me, and I think that had more to do with me than them. In any case, purchasing extras might be good insurance since they take awhile to ship. 
* In total, you need 12 panels, 65mm square. The name branded NeoPixel panels from AdaFruit are 71mm.....do not use those unless you want to update the STL files.
* The White panels are used for the reverse light area. You can opt to use all black led panels, too.

|  Component | QTY Needed | Actual items needed | Notes |
| --- | --- | --- | --- |
|  [White LED panels](https://www.aliexpress.com/item/WS2812B-8x8-64-Bit-Full-Color-5050-RGB-LED-Lamp-Panel-Light-for-Arduino-OS857/32822265747.html?spm=a2g0s.9042311.0.0.27424c4ddvDGry) | 2 |  |  |
|  [Black LED panels](https://www.aliexpress.com/item/WS2812-LED-5050-RGB-8x8-64-LED-Matrix-for-Arduino/32622872541.html?spm=a2g0s.9042311.0.0.27424c4ddvDGry) | 12 |  |  |

### Cycle Terminal
These connectors connect to the OEM connectors for a really clean install. The optional parts are used in place of using a bulb socket adapter to wire things up. This is explained later on, but I recommend getting these optional components because it makes things more compact. 

|  Component | QTY Needed | Actual items needed | Notes |
| --- | --- | --- | --- |
|  ET250-4 Male | 1 |  | (OEM Acc power) |
|  HD 090-2 Male | 2 |  | (OEM Turn signal) |
|  HD 090-8 Male | 1 |  | (OEM main wiring) |
|  HD 090-6 Female | 1 |  | (OEM brake lamp defeat) |
|  3 pin HD 090  Female Connector | 6 | Optional | (data lines) |
|  3 pin HD 090  Male Connector | 6 | Optional | (data lines) |
|  2 pin HD 090  Female Connector  3 (power lines) (same as TS) | 3 | Optional | (voltage drop) |
|  2 pin HD 090  Male Connector | 3 | Optional | (voltage drop) |


# 3D printed parts
The parts are easy to print. However, you should use ABS. PETG might work, but probably not worth the risk. 

# Opening up your tail lights
Search google for opening up your tail light housing

# PCB and Soldering
Use the gerber zip file and send it to www.jlcpcb.com to get made

# Wiring guide
## LED panels
tbd
* Note, the white panels are labeled backwards, probably!

## PCB to LEDs
tbd 
## Car to PCB
tbd

# Testing (pre-flight)
Load the test code, and let it run overnight to break-in the LED panels. 

# Sealing your lights
Use morimoto butyl

