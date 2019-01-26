# diynsxled

DIY LEDS for your NSX

# Prerequisites
1. A 3D printer is required to print the brackets and enclosure
2. A custom PCB can be made for about $30 from www.jlcpcb.com
3. [Install Arduino IDE](https://www.arduino.cc/en/Guide/HomePage)
4. Some soldering experience, or watch a few youtube videos first :)
5. Read this guide three times or more. There's a lot of info and if you're confused, open an issue above and I will try to help you out.

# Risks
The NSX taillights are old, and so there is a real risk that you'll break something. The bolts that connect to the car are fragile, the acrylic lenses are prone to cracking, etc. Just know that it's a real possibility that something can go wrong. Proceed at your own risk. 

Playing with high amperage is dangerous! Both tail lights on at full red brightness can use 5A. If you use White, even more. 

# Reading (optional)
* [NeoPixels UberGuide](https://learn.adafruit.com/adafruit-neopixel-uberguide/the-magic-of-neopixels)
* [Arduino bootloader](https://learn.sparkfun.com/tutorials/installing-an-arduino-bootloader/all) for instant start up time.

# 10,000 foot summary

The instructions below can be a bit overwelming. The high level steps are as follows:

1. Gather all the components, 3d printed parts and pcb.
2. Open tail lights and make cuts for led panels
3. Solder the pcb components
4. Wire the led together
5. Test led wiring
6. Wiring Harness - Car to PCB
7. Wiring Harness - PCB to LED Panels
8. Put brackets and leds in tail light
9. Test before sealing with car's wiring
10. Seal tail lights
11. Connect wiring

# Components

The component list links to websites for the number of items you would need to order. They are usually in sold in bundles and I have also listed the actual qty needed (if different) in case you can source these parts individually. For example, you need 6 diodes, but they only sell them in packs of 20.

If you're familiar with digikey and mouser, you can order a lot of these parts from there, too. However, some things were more expensive. 

### Custom Components
* Download the gerber zip file and send it to www.jlcpcb.com to get made. You get 10 for the same price, good if you mess up or for a group buy.
* Print the 3D printed parts in the `stl/` directory.
  * For tail light pieces, only drivers side is included. Use your slicer to mirror the brake and turn signal brackets for the passenger side. The reverse light bracket can be used on either side.
  * The parts are easy to print and do not require supports or anything special. 
  * Print with ABS. PETG should work, but ABS if you can.
  * In your slicer, split the parts up for the enclosure and print individually (and for bulb mount if using that).


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
|  [Resistors](https://www.amazon.com/gp/product/B072BL2VX1?tag=diynsxled-20) | 1 | 2x465, 5x4.7k, 5x1k |  |
|  [18ga Wire red](https://www.amazon.com/gp/product/B000HACYOS?tag=diynsxled-20) | 1 | optional if you have wire |  |
|  [18 ga Wire black](https://www.amazon.com/gp/product/B003J699RW?tag=diynsxled-20) | 1 | optional if you have wire |  |
|  [18 ga Wire green](https://www.amazon.com/gp/product/B003J65A84?tag=diynsxled-20) | 1 | optional if you have wire |  |
|  [18 ga wire pack](https://www.amazon.com/gp/product/B00N51OO7Q?tag=diynsxled-20) | 1 | optional if you have wire |  |
|  [Crimp tool](https://www.amazon.com/gp/product/B00OMM4YUY?tag=diynsxled-20) | 1 | optional, use with the cycle terminal crimps |  |
|  [Plug connectors](https://www.amazon.com/gp/product/B07DB7X9R9?tag=diynsxled-20) | 1 | optional | I prefer the ones from CycleTerminal, but you can also use these.|
|  [Benchtop DC power supply](https://www.amazon.com/gp/product/B071RNT1CD?tag=diynsxled-20) | 1 | optional, great for testing with or use a spare car battery |  |
|  [Socket adapters DIP](https://www.amazon.com/QLOUNI-122Pcs-2-54mm-Sockets-Adaptor/dp/B07CJ87NVT?tag=diynsxled-20) | 1 | Optional [1x6pin, 1x16pin] | For chips from digikey |
|  [Stacking headers for Nano](https://www.amazon.com/Shield-Stacking-Header-Arduino-Pack/dp/B0756KRCFX?tag=diynsxled-20) | 1 |  |  |
|  [Arduino Nano (Brand name)](https://www.amazon.com/Arduino-A000005-ARDUINO-Nano/dp/B0097AU5OU?tag=diynsxled-20) | 1 | optional (pick this or 3rd party) | Brand name. 3rd party just as good.|
|  [Arduino Nano (china)](https://www.amazon.com/ATmega328P-Microcontroller-Board-Cable-Arduino/dp/B00NLAMS9C?tag=diynsxled-20) | 1 | optional  |  |
|  [AVR Programmer](https://www.amazon.com/gp/product/B004G54E9I?tag=diynsxled-20) | 1 | Optional |  |
|  [Turn Signal Bulbs](https://www.amazon.com/gp/product/B07DFYSM5J?tag=diynsxled-20) | 1 | Optional |  |
|  [Load resistor](https://www.amazon.com/Resistors-Signal-License-Warning-Cancellor-x/dp/B004EDF8HY/ref=sr_1_8?tag=diynsxled-20) | 1 | Optional |  |
|  [5 wire connector](https://www.amazon.com/Wago-222-415-LEVER-NUTS-Conductor-Connectors/dp/B07CN5974J?tag=diynsxled-20) | 1 | 5, optional | There are better ways to splice wires |  
|  [Morimoto Butyl](https://www.amazon.com/RetroRubber-Grade-Butyl-Headlight-Sealant/dp/B01N5PM29J?tag=diynsxled-20) | 1 |  |  |
|  [M2/M3 bolts and nuts](https://www.amazon.com/gp/product/B07CSSVRPL?tag=diynsxled-20) | 1 | 6xM2, 10xM3 |  |
|  [Jumper wires](https://www.amazon.com/gp/product/B005TZJ0AM?tag=diynsxled-20) | 1 | optional | These will make wiring the panels together easier. We only need the short 4.7in ones.. |

**Note that the Amazon links have an affiliate link attached to them. This helps me recoupe some of the cost of development, and future dev work.* 



### Digikey
|  Component | QTY Needed | Actual items needed | Notes |
| --- | --- | --- | --- |
|  [Pin headers for Pololu regulator](https://www.digikey.com/products/en?mpart=TSW-202-07-T-S&v=612) | 2 |  |  |
|  [Opto 4ch](https://www.digikey.com/product-detail/en/PS2501-4-A/PS2501-4A-ND/770687) | 1 |  |  |
|  [Opto 2ch](https://www.digikey.com/product-detail/en/4N35/4N35-ND/1738522) | 1 |  |  |

### Aliexpress
* The LED panels are cheapest on Aliexpress. With regards to quality issues, I feel that all the panels i've bought have for the most part been great. Only 2 died on me, and I think that had more to do with me than them. In any case, purchasing extras might be good insurance since they take awhile to ship. 
* In total, you need 14 panels, 65mm square. The name branded NeoPixel panels from AdaFruit are 71mm.....do not use those unless you want to update the STL files.
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
|  2 pin HD 090  Female Connector | 4 | Optional | (power lines) (same as TS) (voltage drop) |
|  2 pin HD 090  Male Connector | 4 | Optional | (voltage drop) |


# Opening up your tail lights
Search google for opening up your tail light housing. You'll need to remove the gasket and electrical wiring and brake lamp detector box. 

# Tail Light Prep
You need to make these cuts to your tail lights. They are not visible if you decide to revert back to stock:

1. In the brake light area, there is a strip of plastic that comes flush to the rest of the light. This needs to be cut down. 
2. Next to the strip that you just cut, you'll need to make a small hole for the screw terminal to fit through. Save this step for when you test fit the 3d printed brackets and leds. 
3. Reverse light area, make two cuts so let the led panel sit flush.
tbd - include images of cuts

Next:
1. Remove the reflectors in the brake, reverse, and turnsignal areas.
2. You can keep all the diffusers.
3. you will not reuse the inner clear panel that is on the brake lamp area.


# LED Panel Prep
### soldering
Solder the two 3-pin 2.54mm terminals to each panel. 
tbd - image

### panel orientation and prep
The order of the panels goes from reverse light to brake lights to turn signals.
1 reverse light panels
5 brake lights panels
1 turn signal panels

For the 5 brake light panels, you need to glue the ends together. Each panel has an input terminal and output terminal. You want to glue them together so that the output terminal of one panel is next to the input terminal of another. 

tbd see image



# PCB Soldering

The holes will guide you. If it doesn't fit, you have the wrong part. 

Misc notes:
1. 5mm pins are used with the biggest holes in the voltage regulator. Only the center two on each end need to be soldered. 
2. The DIP sockets on the two chips are optional, but allow you to change the chips out if they get damaged without having to desolder everything. 
3. The nano uses header pins to easy connect and disconnect. There are 15 pins on each side. On my board, I only had 14 pin stacking headers, so my last row of pins near the usb is not used but that's ok because no connections are there. 
4. PCB uses M2 screws to mount to enclosure. 

<img width="100" height="100" src="https://github.com/tdiggity/diynsxled/blob/master/pics/pcb_annotated.png?raw=true">

Notes about image:
* Red boxes - Diode orientation matters
* Red dot - Note grey strip on capacitor
* Blue dots - These note pin 1 of the chip, usually a notch or dot on the chip
* Yellow arrow - Voltage In to Voltage Out


tbd - insert resistor diagram here
Resistors
* 465 ohm - R11, R12
* 1k ohm - R10, 20, 30, 40, 50
* 4.7k ohm - R6, R7, R8, R9, R100

# Wiring guide
## LED panels
tbd
* Note, the white panels are labeled backwards, probably!

## PCB to LEDs
tbd 
## Car to PCB
tbd


# Test fit parts in tail lights
Test mount the 3d printed brackets in the tail light with the led panels. Ensure that the panels fit flush. They should slide in easily. If not, you might need to shave off some more of the cuts you previously made. 

If everything fits, first glue the 3d printed brackets to the tail lights with some superglue and/or hot glue. Once that sets, use hotglue on the tabs and attach the led panels. Super glue and hot glue don't conduct electricity.

Tip: Ensure that the brackets are flush with the border of the tail lights. Hot glue sets quickly enough for you to get them  lined up well. 

# Loading the arduino code
For testing - open the test file in the `test/` folder and upload it using the arduino IDE. 
For driving use - open the diynsxled.ino file and upload it using the arduino IDE. 

### Advanced - use the AVR programmer to load the code
The Arduino is only on when the key is in ACC position (2nd key position and also when engine is on). Otherwise it is off and not using any power.

In stock form, it takes about 1-2 seconds before any code can be run when first powering up. WHen the car is running, the Arduino is always on, so there is no worry of delay. 

When the Arduino is off, the LEDS will not work correctly in certain cases because the arduino does not have power long enough to get past the startup stage:
* When the emergency lights are on
* If you have a security system that blinks the leds upon activation/deactivation. 

This can be fixed by using an [AVR programmer](https://www.amazon.com/gp/product/B004G54E9I?tag=diynsxled-20) to remove the 1-2 second delay and instantly execute the LED program. Follow the instructions here: [AVR Guide](https://learn.sparkfun.com/tutorials/pocket-avr-programmer-hookup-guide/all) (pay attention to the "Programming with Arduino" section.)


# Testing (pre-flight)
Load the test code in the `tests/` folder. The first time you run the test code, let them run for a few hours or overnight. If you're using the [Benchtop DC power supply](https://www.amazon.com/gp/product/B071RNT1CD?tag=diynsxled-20), this won't be a problem. If using a car battery, i'm not sure how long they will last. But something is better than nothing. It's been said that if an electrical thing will fail, it'll fail earlier rather than later. 

It's advised to do testing at various stages to check your wiring:
* After all terminals and wires soldered, but before glueing panels together
* After brake panels are glued together
* After mounting into taillights but before sealing
* After sealing


# Sealing your lights
Use morimoto butyl

