# charduindicator
(*char*lieplexed *ardu*ino *indicator*)

This is an Arduino project that controls a 4x5 LED charlieplexed display, via simple serial commands such as `on 1` (to turn on the first LED) and `off 20` (to turn off the twentieth LED).

It has been tested with an Arduino Uno and a 4x5 LED display I soldered by hand. The wiring is very, and a schematic can be seen [here](http://www.instructables.com/id/Controlling-20-Leds-from-5-Arduino-pins-using-Cha/step3/The-first-problem-Wiring-it-properly/) (NOT my own schematic/instructable).

## Serial Commands:
The serial input acts as a simple shell. You enter a command (possibly with an argument) and the Arduino will change the state of the charlieplexed LED array to match:

`on <led>`
  turns on LED number \<led> (a 1-indexed number)
  
`off <led>`
  turns off LED number \<led>
  
`clear`
  turns off all LEDs
