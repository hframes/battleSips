#include <Arduino.h>
//#include "Particle.h"



#define NBR_BUTTONS 5

#define BIT_SEL     0
#define BIT_UP      1
#define BIT_LEFT    2
#define BIT_RIGHT   3
#define BIT_DOWN    4
#define BIT_DOWN    4
#define BIT_NO      0b11111

typedef struct buttons{
// Pins
int pinSelect;
int pinUp;
int pinLeft;
int pinRight;
int pinDown;

// Pin states (binary)
int stateA;
int stateB;

// Timing array
int timeLastPress[5];

} buttons;

// Initialize pins
int initializePins(buttons b){
  pinMode(b.pinSelect, INPUT);
  pinMode(b.pinUp, INPUT);
  pinMode(b.pinLeft, INPUT);
  pinMode(b.pinRight, INPUT);
  pinMode(b.pinDown, INPUT);
}


// // Print button status
// void printButtonStatus(int buttons)
// {
//   ((buttons >> BIT_SEL) & 1)    ? Serial.print("-,\t") : Serial.print("S,\t");
//   ((buttons >> BIT_UP) & 1)     ? Serial.print("-,\t") : Serial.print("U,\t");
//   ((buttons >> BIT_LEFT) & 1)   ? Serial.print("-,\t") : Serial.print("L,\t");
//   ((buttons >> BIT_RIGHT) & 1)  ? Serial.print("-,\t") : Serial.print("R,\t");
//   ((buttons >> BIT_DOWN) & 1)   ? Serial.print("-,\t") : Serial.print("D,\t");
//   Serial.println();
// }

// // Read button states and update array
// void updateButtonInput(int *but_status, const int *pins_player)
// {
//   *but_status = (*but_status & ~(1 << BIT_SEL))   | digitalRead(pins_player[BIT_SEL]) << BIT_SEL;
//   *but_status = (*but_status & ~(1 << BIT_UP))    | digitalRead(pins_player[BIT_UP]) << BIT_UP;
//   *but_status = (*but_status & ~(1 << BIT_LEFT))  | digitalRead(pins_player[BIT_LEFT]) << BIT_LEFT;
//   *but_status = (*but_status & ~(1 << BIT_RIGHT)) | digitalRead(pins_player[BIT_RIGHT]) << BIT_RIGHT;
//   *but_status = (*but_status & ~(1 << BIT_DOWN))  | digitalRead(pins_player[BIT_DOWN]) << BIT_DOWN;
// }