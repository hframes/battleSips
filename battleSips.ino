#include <Encoder.h>
#include <Adafruit_NeoPixel.h>

#define DEBOUNCE          300
#define NBR_USER_INPUTS   5

// Number of inputs
const uint8_t but_sel   = 0;
const uint8_t but_up    = 1;
const uint8_t but_left  = 2;
const uint8_t but_right = 3;
const uint8_t but_down  = 4;
const uint8_t but_no    = 0b11111;

// Player pins
const int pin_p1_select = 19;
const int pin_p1_upp    = 18;
const int pin_p1_right  = 17;
const int pin_p1_left   = 16;
const int pin_p1_down   = 15;

const int pin_p2_select = 14;
const int pin_p2_upp    = 10;
const int pin_p2_left   = 12;
const int pin_p2_right  = 11;
const int pin_p2_down   = 13;

const int p1ea_pin = 2;
const int p1eb_pin = 3;

const int p2ea_pin = 7;
const int p2eb_pin = 8;

Encoder encoder_p1(p1ea_pin, p1eb_pin);
const uint8_t pins_p1[NBR_USER_INPUTS] = {
    [but_sel] = pin_p1_select,
    [but_up] = pin_p1_upp,
    [but_left] = pin_p1_left,
    [but_right] = pin_p1_right,
    [but_down] = pin_p1_down,
};

Encoder p2Enc(p2ea_pin, p2eb_pin);
const uint8_t pins_p2[NBR_USER_INPUTS] = {
    [but_sel] = pin_p2_select,
    [but_up] = pin_p2_upp,
    [but_left] = pin_p2_left,
    [but_right] = pin_p2_right,
    [but_down] = pin_p2_down,
};

// Input states
uint8_t buttonStateA_p1;
uint8_t buttonStateB_p1;
uint8_t buttonStateA_p2;
uint8_t buttonStateB_p2;
uint32_t buttonTime_p1[NBR_USER_INPUTS];
uint32_t buttonTime_p2[NBR_USER_INPUTS];

uint8_t p1EncA;
uint8_t p1EncB;
uint16_t encoderPos_p1;

uint8_t p2EncA;
uint8_t p2EncB;
uint16_t encoderPos_p2;

// MATRIX
uint8_t positionMatrix_p1 = 0;
uint8_t positionMatrix_p2 = 0;

#define PIN 9
#define NUMPIXELS 40

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

// GAME
uint8_t game;
// - BATTLE SIPS
#define GAME_BATTLE_SIPS (uint8_t)0

uint8_t gameStateBattleSips;

// - PAINTING
#define GAME_PAINTING (uint8_t)1

uint8_t gameStatePainting;
uint16_t matrixColors[40] = {510, 510, 510, 510, 510,
                             510, 510, 510, 510, 510,
                             510, 510, 510, 510, 510,
                             510, 510, 510, 510, 510,
                             510, 510, 510, 510, 510,
                             510, 510, 510, 510, 510,
                             510, 510, 510, 510, 510,
                             510, 510, 510, 510, 510};

void setup()
{
  Serial.begin(115200);

  pinMode(pin_p1_select, INPUT);
  pinMode(pin_p1_upp, INPUT);
  pinMode(pin_p1_left, INPUT);
  pinMode(pin_p1_right, INPUT);
  pinMode(pin_p1_down, INPUT);

  pinMode(pin_p2_select, INPUT);
  pinMode(pin_p2_upp, INPUT);
  pinMode(pin_p2_left, INPUT);
  pinMode(pin_p2_right, INPUT);
  pinMode(pin_p2_down, INPUT);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  Serial.println("Welcometo BattleSips Board Bringup!");

}

void loop()
{
  caseInput(GAME_PAINTING, &positionMatrix_p1, updateInputs());

  updateMatrix(matrixColors);

  Serial.println(positionMatrix_p1);
}

// Print button status
void printButtonStatus(uint8_t buttons)
{
  ((buttons >> but_sel) & 1)    ? Serial.print("-,\t") : Serial.print("S,\t");
  ((buttons >> but_up) & 1)     ? Serial.print("-,\t") : Serial.print("U,\t");
  ((buttons >> but_left) & 1)   ? Serial.print("-,\t") : Serial.print("L,\t");
  ((buttons >> but_right) & 1)  ? Serial.print("-,\t") : Serial.print("R,\t");
  ((buttons >> but_down) & 1)   ? Serial.print("-,\t") : Serial.print("D,\t");
  Serial.println();
}

// Read button states and update array
void updateButtonInput(uint8_t *but_status, const uint8_t *pins_player)
{
  *but_status = (*but_status & ~(1 << but_sel)) | digitalRead(pins_player[but_sel]) << but_sel;
  *but_status = (*but_status & ~(1 << but_up)) | digitalRead(pins_player[but_up]) << but_up;
  *but_status = (*but_status & ~(1 << but_left)) | digitalRead(pins_player[but_left]) << but_left;
  *but_status = (*but_status & ~(1 << but_right)) | digitalRead(pins_player[but_right]) << but_right;
  *but_status = (*but_status & ~(1 << but_down)) | digitalRead(pins_player[but_down]) << but_down;
}

uint8_t updateInputs()
{
  static bool alternating;
  uint8_t buttonResponse;
  if (alternating)
  {
    updateButtonInput(&buttonStateA_p1, pins_p1);
    // updateEncInput(&p1EncA, &p1EncB, p1ea_pin, p1eb_pin, &encoderPos_p1);
    buttonResponse = checkButtonPress(buttonStateA_p1, buttonStateB_p1, buttonTime_p1);
  }
  else
  {
    updateButtonInput(&buttonStateB_p1, pins_p1);
    // updateEncInput(&p1EncB, &p1EncA, p1ea_pin, p1eb_pin, &encoderPos_p1);
    buttonResponse = checkButtonPress(buttonStateB_p1, buttonStateA_p1, buttonTime_p1);
  }
  alternating = !alternating;
  matrixColors[positionMatrix_p1] = encoder_p1.read();
  // Serial.println(encoderPos_p1);
  matrixMovement(positionMatrix_p1, buttonResponse);
  return buttonResponse;
}

// Checks if button has been pressed and returns pressed button
int checkButtonPress(uint8_t newButton, uint8_t oldButton, uint32_t* time)
{
  if (oldButton = 0b11111)
  {
    switch (newButton)
    {
    case 0b11111 & ~(1 << but_sel):
      if(millis() - time[but_sel] > DEBOUNCE){
        time[but_sel] = millis();
        Serial.println("Sel");
        return but_sel;
      }
      break;
    case 0b11111 & ~(1 << but_up):
      if(millis() - time[but_up] > DEBOUNCE){
        time[but_up] = millis();
        Serial.println("Up");
        return but_up;
      }
      break;
    case 0b11111 & ~(1 << but_left):
      if(millis() - time[but_left] > DEBOUNCE){
        time[but_left] = millis();
        Serial.println("left");
        return but_left;
      }
      break;
    case 0b11111 & ~(1 << but_right):
      if(millis() - time[but_right] > DEBOUNCE){
        time[but_right] = millis();
        Serial.println("Right");
        return but_right;
      }
      break;
    case 0b11111 & ~(1 << but_down):
      if(millis() - time[but_down] > DEBOUNCE){
        time[but_down] = millis();
        Serial.println("Down");
        return but_down;
      }
      break;
    default:
      return 0b11111;
      break;
    }
  }
  return 0b11111;
}

uint8_t caseInput(uint8_t stateGame, uint8_t *matrixPos, uint8_t button)
{
  switch (button)
  {
  case but_sel:
    *matrixPos = matrixMovement(*matrixPos, but_sel);
    break;
  case but_up:
    *matrixPos = matrixMovement(*matrixPos, but_up);
    Serial.println("[CASE INPUT] up");
    encoder_p1.write(matrixColors[*matrixPos]);
    break;
  case but_left:
    *matrixPos = matrixMovement(*matrixPos, but_left);
    Serial.println("[CASE INPUT] left");
    encoder_p1.write(matrixColors[*matrixPos]);
    break;
  case but_right:
    *matrixPos = matrixMovement(*matrixPos, but_right);
    encoder_p1.write(matrixColors[*matrixPos]);
    Serial.println("[CASE INPUT] right");
    break;
  case but_down:
    *matrixPos = matrixMovement(*matrixPos, but_down);
    encoder_p1.write(matrixColors[*matrixPos]);
    Serial.println("[CASE INPUT] down");
    break;

  default:
    break;
  }
}

// Updates  matrix position from buttons
uint8_t matrixMovement(uint8_t position, uint8_t dir)
{
  switch (dir)
  {
  case but_sel:
    // SELECT
    break;
  case but_up:
    if (position > 4)
    {
      position = position - 5;
    }
    break;
  case but_left:
    if ((position % 5) > 0)
    {
      position = position - 1;
    }
    break;
  case but_right:
    if ((position % 5) < 4)
    {
      position = position + 1;
    }
    break;
  case but_down:
    if (position < 34)
    {
      position = position + 5;
    }
    break;
  default:
    break;
  }
  return position;
}

// Translates matrix position to corresponding snake position
uint8_t translateMatrix(uint8_t pos)
{
  if (((pos / 5) % 2) != 0)
  {
    pos = ((pos / 5) * (5)) + (4 - (pos % 5));
  }
  return pos;
}

// void updateEncInput(uint8_t *enc_statusNew, uint8_t *enc_statusOld, const uint8_t encoderPinA, const uint8_t encoderPinB, uint8_t *encPos)
// {
//   *enc_statusNew = digitalRead(encoderPinA);
//   if (*enc_statusNew != *enc_statusOld)
//   {
//     if (digitalRead(encoderPinB))
//     {
//       *encPos = *encPos + 1;
//       Serial.print("++: ");
//       Serial.println(*encPos);
//     }
//     else
//     {
//       *encPos = *encPos - 1;
//       Serial.print("--: ");
//       Serial.println(*encPos);
//     }
//   }
// }

// Translate linear color to 3-dimensional color and update LED
uint8_t setColor(uint16_t value, uint8_t led)
{
  value = value % 765;
  int red, green, blue;
  if (value < 255)
  {
    red = 255 - value;
    green = value;
    blue = 0;
  }
  else if (value < 510)
  {
    red = 0;
    green = 510 - value;
    blue = value - 255;
  }
  else
  {
    red = value - 510;
    green = 0;
    blue = 765 - value;
  }

  pixels.setPixelColor(translateMatrix(led), pixels.Color(red, green, blue));
}

// Updates all leds in matrix
uint8_t updateMatrix(uint16_t *matrix)
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    setColor(matrix[i], i);
    pixels.show(); // Send the updated pixel colors to the hardware.
  }
}