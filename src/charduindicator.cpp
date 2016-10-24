#include <Arduino.h>
#define SERIALCOMMAND_ECHO
#include <SerialCommand.h>
SerialCommand sCmd;

#include <Chaplex.h>
byte ctrlpins[5] = {2,3,4,5,6};    //Arduino pins controlling charlieplexed leds

Chaplex myCharlie(ctrlpins, sizeof(ctrlpins));     //control instance

charlieLed myLeds[20]  = {

  {3,4},{2,4},{1,4},{0,4},{4,3},
  //1     2     3     4     5
  {2,3},{1,3},{0,3},{4,2},{3,2},
  //6     7     8     9     10
  {1,2},{0,2},{4,1},{3,1},{2,1},
  //11    12    13    14    15
  {0,1},{4,0},{3,0},{1,0},{2,0}
  //16    17    18    19    20
};

void unrecognized(const char *command) {
  Serial.println("What?");
}

void clear() {
  myCharlie.allClear();
}

void ledOn() {
  char *ledStr;
  ledStr = sCmd.next();
  int led = atoi(ledStr) - 1;
  myCharlie.ledWrite(myLeds[led], 1);
}

void ledOff() {
  char *ledStr;
  ledStr = sCmd.next();
  int led = atoi(ledStr) - 1;
  myCharlie.ledWrite(myLeds[led],0);
}
void setup() {
  // Initialize charlieplex array — turn off all LEDs.
  myCharlie.allClear();
  myCharlie.outRow();

  // initialize serial:
  Serial.begin(9600);
  sCmd.addCommand("on", ledOn);
  sCmd.addCommand("off", ledOff);
  sCmd.addCommand("clear", clear);
  sCmd.setDefaultHandler(unrecognized);
  Serial.println("Ready");
}


void loop() {
  sCmd.readSerial();
  myCharlie.outRow();
}
