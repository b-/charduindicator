# charduindicator
(*char*lieplexed *ardu*ino *indicator*)

This is an Arduino project that controls a 4x5 LED charlieplexed display, via simple serial commands such as `on 1` (to turn on the first LED) and `off 20` (to turn off the twentieth LED).

It was prototyped with an Arduino Uno and a 4x5 LED display I soldered by hand (the wiring is rather simple, and a schematic can be seen [here](http://www.instructables.com/id/Controlling-20-Leds-from-5-Arduino-pins-using-Cha/step3/The-first-problem-Wiring-it-properly/) (NOT my own schematic/instructable, and my own schematic is based off it).

There is a Fritzing (.fzz) file for a PCB of the circuit with an onboard ATMEGA328p and 16MHz oscillator, but *no* power supply. That means that you need to provide regulated power to it. No external wall warts or anything like that; you'll probably break it. The Fritzing project is meant to be used with a pin header soldered to the angled set of six pins in the corner, and an "FTDI Basic" breakout plugged into those six pins. The FTDI breakout board itself is open source and very inexpensive. You can get a "real" one for maybe $10-15 USD, and a knockoff one with a fake FTDI chip for half that or less. I haven't tested this with a fake breakout, but remember that there is *no* power supply circuit on this board.

Also, you'll need an ICSP programmer for the board. You can buy one for cheap, or make one out of an Arduino (while I was waiting for my programmer to come in I was using a programmer sketch on the Arduino I used to prototype the project). The `platformio.ini` is set to use a generic USBTinyISP programmer you can purchase or build yourself for cheap. I also have a programmer or two with a ZIF socket coming, because burning the chip using the socket on an Arduino is a pain, and I'd like to be able to program the chip before assembly.

I should have added pins to jumper the DTR to a capacitor to provide Arduino-compatible autoreset, and thus programmability via the FTDI. I specifically didn't want autoreset, as it got in the way of the intentional serial communication, but had I thought of a jumper this would have allowed it to be enabled or disabled at will. This will hopefully come in a future revision.

## Serial Commands:
The serial input acts as a simple shell. You enter a command (possibly with an argument) and the Arduino will change the state of the charlieplexed LED array to match:

`on <led>`
  turns on LED number \<led> (a 1-indexed number)
  
`off <led>`
  turns off LED number \<led>
  
`clear`
  turns off all LEDs

## Coming soon:
I intend on writing a simple boot routine that cycles each LED on and then off in order to demonstrate a successful bootup. Currently the program code provides no power-on feedback apart from an incoming `Ready` on the serial line. I also want to add a command to perform an LED cycle and clear (for testing purposes), and see if I can route my traces nicer. One board needed a bodge wire because two traces were so close that I accidentally clipped and lifted one while soldering to another. Also, it would be nice to have a way to mount the board to something... That's kind of important.
