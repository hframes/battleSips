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
const uint8_t but_no  = 0b11111;

// Player pins
const int pin_p1_select = 19;
const int pin_p1_upp = 18;
const int pin_p1_right = 17;
const int pin_p1_left = 16;
const int pin_p1_down = 15;

const int pin_p2_select = 14;
const int pin_p2_upp = 10;
const int pin_p2_left = 12;
const int pin_p2_right = 11;
const int pin_p2_down = 13;

const int p1ea_pin = 2;
const int p1eb_pin = 3;

const int p2ea_pin = 7;
const int p2eb_pin = 8;


Encoder p1Enc(p1ea_pin, p1eb_pin);
const uint8_t pins_p1[nbr_user_inputs] = {
  [but_sel]   = pin_p1_select,
  [but_up]    = pin_p1_upp, 
  [but_left]  = pin_p1_left,
  [but_right] = pin_p1_right,
  [but_down]  = pin_p1_down,
};


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
uint8_t p1B;
uint8_t p2A;
uint8_t p2B;

uint8_t p1EncA;
uint8_t p1EncB;
uint8_t p1EncPos;

uint8_t p2EncA;
uint8_t p2EncB;
uint8_t p2EncPos;

// MATRIX
uint8_t matrixPlacementP1 = 0;
uint8_t matrixPlacementP2 = 0;

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
    //delay(200);
    updateInputs();

    pixels.setPixelColor(translateMatrix(matrixPlacementP1), pixels.Color(0, 5, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

  pixels.clear(); // Set all pixel colors to 'off'


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
  uint8_t buttonResponse;
  if (alternating) {
    updateButtonInput(&p1A, pins_p1);
    //updateEncInput(&p1EncA, &p1EncB, p1ea_pin, p1eb_pin, &p1EncPos);
    buttonResponse = checkButtonPress(p1A, p1B);
  } else {
    updateButtonInput(&p1B, pins_p1);
    //updateEncInput(&p1EncB, &p1EncA, p1ea_pin, p1eb_pin, &p1EncPos);
    buttonResponse = checkButtonPress(p1B, p1A);
  }
  alternating = !alternating;
  p1EncPos = p1Enc.read();
  Serial.println(p1EncPos);
  matrixMovement(&matrixPlacementP1, buttonResponse);
  return buttonResponse;
}

int checkButtonPress(uint8_t newButton, uint8_t oldButton){
  if(oldButton =  0b11111){
    switch (newButton)
    {
    case 0b11111 & ~(1 << but_sel):
      return but_sel;
    case 0b11111 & ~(1 << but_up):
      return but_up;
    case 0b11111 & ~(1 << but_left):
      return but_left;
    case 0b11111 & ~(1 << but_right):
      return but_right;
    case 0b11111 & ~(1 << but_down):
      return but_down;
    default:
      return 0b11111;
      break;
    }
  }
}

uint8_t caseInput(uint8_t input){

}

uint8_t matrixMovement(uint8_t* matrixPosPlayer, uint8_t dir){
  switch (dir)
  {
  case but_sel:
    // SELECT
    break;
  case but_up:
    if(*matrixPosPlayer > 4){
      *matrixPosPlayer = *matrixPosPlayer - 5;
    }
    break;
  case but_left:
    if((*matrixPosPlayer % 5) > 0){
      *matrixPosPlayer = *matrixPosPlayer - 1;
    }
    break;
  case but_right:
    if((*matrixPosPlayer % 5) < 4){
      *matrixPosPlayer = *matrixPosPlayer + 1;
    }
    break;
  case but_down:
    if(*matrixPosPlayer < 34){
      *matrixPosPlayer = *matrixPosPlayer + 5;
    }
    break;
  default:
    break;
  }
}

uint8_t translateMatrix(uint8_t pos){
  if(((pos / 5) % 2) != 0){
    pos = ((pos / 5) * (5))  + (4 - (pos % 5));
  }
  return pos;
}

uint8_t updateMatrix(uint8_t* matrix){
  for(int i=0; i<NUMPIXELS; i++) {
  
    pixels.setPixelColor(translateMatrix(i), pixels.Color(0, 5, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}


void updateEncInput(uint8_t* enc_statusNew, uint8_t* enc_statusOld, const uint8_t encoderPinA, const uint8_t encoderPinB, uint8_t* encPos){
    *enc_statusNew = digitalRead(encoderPinA);
    if(*enc_statusNew != *enc_statusOld){
      if(digitalRead(encoderPinB)){
        *encPos = *encPos + 1;
        Serial.print("++: ");
        Serial.println(*encPos);
      } else {
        *encPos = *encPos - 1;
        Serial.print("--: ");
        Serial.println(*encPos);
      }
    }
}


// uint8_t updateEncoder(uint8_t* newState, uint8_t* oldState){
//   newState = digitalRead(p1ea_pin);
// }