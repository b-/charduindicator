#include <Arduino.h>
#define SERIALCOMMAND_ECHO
#include <SerialCommand.h>
SerialCommand sCmd;

#include <Chaplex.h>
byte ctrlpins[5] = {2,3,4,5,6};    //Arduino pins controlling charlieplexed leds
#define DELAY 100             //speed of switching leds in bar on and off

byte timer2TCNT2 = 178;    //preload timer 256-16MHz/1024/78 = near 5 ms
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


ISR(TIMER2_OVF_vect) {          //timer2 interrupt routine
  myCharlie.outRow();           //output for one led row
  TCNT2 = timer2TCNT2;          //preload timer for next interrupt
}

void unrecognized(const char *command) {
  Serial.println("What?");
}

void clear() {
  // Initialize charlieplex array — turn off all LEDs.
  myCharlie.allClear();
//  myCharlie.outRow();
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
void cycle() {
  int cled = 0;
  while( cled < 20 ) {
    myCharlie.ledWrite(myLeds[cled],1);
//    myCharlie.outRow();
    delay(10);
    cled++;
    //myCharlie.allClear();

  }
  myCharlie.allClear();
  cled = 20;
  while( cled > 0 ) {
    myCharlie.ledWrite(myLeds[cled],1);
//    myCharlie.outRow();
    delay(10);
    cled--;
    //myCharlie.allClear();

  }
  myCharlie.allClear();

}
void setup() {
  // initialize timer2
  noInterrupts();                 //disable all interrupts
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = timer2TCNT2;
  TCCR2B |= (0 << CS22) | (1 << CS21) | (0 << CS20);  //prescaler 1024 = 64 micro secs
  TIMSK2 |= (1 << TOIE2);        //enable timer overflow interrupt
  interrupts();                  //enable all interrupts

  cycle();
  // Initialize charlieplex array — turn off all LEDs.
  myCharlie.allClear();

  // initialize serial:
  Serial.begin(9600);
  sCmd.addCommand("on", ledOn);
  sCmd.addCommand("off", ledOff);
  sCmd.addCommand("clear", clear);
  sCmd.addCommand("cycle",cycle);
  sCmd.setDefaultHandler(unrecognized);
  Serial.println("Ready");
}


void loop() {
  sCmd.readSerial();
//  myCharlie.outRow();
}
