#include <Arduino.h>

#include <SerialCommand.h>
SerialCommand sCmd;

#include <Chaplex.h>

byte ctrlpins[5] = {2,3,4,5,6};    //Arduino pins controlling charlieplexed leds
#define PINS 5                //number of these pins

Chaplex myCharlie(ctrlpins, sizeof(ctrlpins));     //control instance

charlieLed myLeds[20]  = {
                         { 0 , 1 },
                         { 0 , 2 },
                         { 0 , 3 },
                         { 0 , 4 },
                         { 1 , 0 },
                         { 1 , 2 },
                         { 1 , 3 },
                         { 1 , 4 },
                         { 2 , 0 },
                         { 2 , 1 },
                         { 2 , 3 },
                         { 2 , 4 },
                         { 3 , 0 },
                         { 3 , 1 },
                         { 3 , 2 },
                         { 3 , 4 },
                         { 4 , 0 },
                         { 4 , 1 },
                         { 4 , 2 },
                         { 4 , 3 },
                       };

//long goneTime;


void unrecognized(const char *command) {
  Serial.println("What?");
}



void ledOn() {
  char *ledStr;
  ledStr = sCmd.next();
  int led = atoi(ledStr);
  led = led + 1;
  myCharlie.ledWrite(myLeds[led], 1);
  //myCharlie.outRow();
}

void ledOff() {
  char *ledStr;
  ledStr = sCmd.next();
  int led = atoi(ledStr);
  led = led + 1;
  myCharlie.ledWrite(myLeds[led],0);
  //myCharlie.outRow();
}
void setup() {
  // Initialize charlieplex array — turn off all LEDs.
  for (byte i=0; i<20; i++){ myCharlie.ledWrite(myLeds[i], 0); }
  myCharlie.outRow();

  // initialize serial:
  Serial.begin(9600);
  sCmd.addCommand("ON", ledOn);
  sCmd.addCommand("OFF", ledOff);
  sCmd.setDefaultHandler(unrecognized);
  Serial.println("Ready");
}


void loop() {
  sCmd.readSerial();
  myCharlie.outRow();
}
