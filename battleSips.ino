#include <Encoder.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Number of inputs
const uint8_t nbr_user_inputs = 5;
const uint8_t but_sel   = 0;
const uint8_t but_up    = 1;
const uint8_t but_left  = 2;
const uint8_t but_right = 3;
const uint8_t but_down  = 4;

// Player pins
const int pin_p1_select = 14;
const int pin_p1_upp = 10;
const int pin_p1_left = 12;
const int pin_p1_right = 11;
const int pin_p1_down = 13;
const int p1ea_pin = 2;
const int p1eb_pin = 3;
Encoder p1Enc(p1ea_pin, p1eb_pin);
const uint8_t pins_p1[nbr_user_inputs] = {
  [but_sel]   = pin_p1_select,
  [but_up]    = pin_p1_upp, 
  [but_left]  = pin_p1_left,
  [but_right] = pin_p1_right,
  [but_down]  = pin_p1_down,
};





const int pin_p2_select = 19;
const int pin_p2_upp = 18;
const int pin_p2_left = 17;
const int pin_p2_right = 16;
const int pin_p2_down = 15;
const int p2ea_pin = 7;
const int p2eb_pin = 8;
Encoder p2Enc(p2ea_pin, p2eb_pin);
const uint8_t pins_p2[nbr_user_inputs] = {
  [but_sel]   = pin_p2_select,
  [but_up]    = pin_p2_upp, 
  [but_left]  = pin_p2_left,
  [but_right] = pin_p2_right,
  [but_down]  = pin_p2_down,
};

// Input states
uint8_t p1A;
uint8_t p2A;
uint8_t p1B;
uint8_t p2B;
uint8_t p1_clicked = 0;
uint8_t p2_clicked = 0;

#define PIN        9 

#define NUMPIXELS 40 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  Serial.begin(115200);

  pinMode(pin_p1_select,  INPUT);
  pinMode(pin_p1_upp,     INPUT);
  pinMode(pin_p1_left,    INPUT);
  pinMode(pin_p1_right,   INPUT);
  pinMode(pin_p1_down,    INPUT);

  pinMode(pin_p2_select,  INPUT);
  pinMode(pin_p2_upp,     INPUT);
  pinMode(pin_p2_left,    INPUT);
  pinMode(pin_p2_right,   INPUT);
  pinMode(pin_p2_down,    INPUT);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  Serial.println("Welcometo BattleSips Board Bringup!");

}

void loop() {



  pixels.clear(); // Set all pixel colors to 'off'

  for(int i=0; i<NUMPIXELS; i++) {
  updateInputs();

    pixels.setPixelColor(i, pixels.Color(50, 150, 50));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}


void printButtonStatus(uint8_t buttons){
  ((buttons >> but_sel)   & 1) ? Serial.print("-,\t") : Serial.print("S,\t");
  ((buttons >> but_up)    & 1) ? Serial.print("-,\t") : Serial.print("U,\t");
  ((buttons >> but_left)  & 1) ? Serial.print("-,\t") : Serial.print("L,\t");
  ((buttons >> but_right) & 1) ? Serial.print("-,\t") : Serial.print("R,\t");
  ((buttons >> but_down)  & 1) ? Serial.print("-,\t") : Serial.print("D,\t");
  Serial.println();
}

void updateButtonInput(uint8_t* but_status, const uint8_t* pins_player){
  *but_status = (*but_status & ~(1 << but_sel))   | digitalRead(pins_player[but_sel])     << but_sel;
  *but_status = (*but_status & ~(1 << but_up))    | digitalRead(pins_player[but_up])      << but_up;
  *but_status = (*but_status & ~(1 << but_left))  | digitalRead(pins_player[but_left])    << but_left;
  *but_status = (*but_status & ~(1 << but_right)) | digitalRead(pins_player[but_right])   << but_right;
  *but_status = (*but_status & ~(1 << but_down))  | digitalRead(pins_player[but_down])    << but_down;
}

uint8_t updateInputs(){
  static bool alternating;
  if (alternating) {
    Serial.println("A");
    updateButtonInput(&p1A, pins_p1);
    if(p1B != 0b11111){
      if(p1A == 0b11111){

      }
    }
    p1_clicked = (p1A >> but_sel) & (p1A >> but_sel ^ p1B >> but_sel) << but_sel;

    updateButtonInput(&p2A, pins_p2);
    printButtonStatus(p1A);
    printButtonStatus(p2A);
  } else {
    Serial.println("B");
    updateButtonInput(&p1B, pins_p1);
    p1_clicked = (p1B >> but_sel) & (p1B >> but_sel ^ p1A >> but_sel) << but_sel;
    Serial.println(p1_clicked);
    // p1_clicked = (p1A >> but_sel) & (p1A >> but_sel ^ p1B >> but_sel) << but_sel;
    // p1_clicked = (p1A >> but_sel) & (p1A >> but_sel ^ p1B >> but_sel) << but_sel;
    // p1_clicked = (p1A >> but_sel) & (p1A >> but_sel ^ p1B >> but_sel) << but_sel;

    updateButtonInput(&p2B, pins_p2);
    
  }
}

// uint8_t determineButton(uint8_t butValue){
//   switch (butValue):
//     case (31 << 0):
    
//     break;
// }