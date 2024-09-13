// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include "pushbutton.h"
#include "matrix.h"
#include <Adafruit_NeoPixel.h>

#define DELAYVAL 0  // Time (in milliseconds) to pause between pixels

#define PIN 9
#define NUMPIXELS 40
#define ROW 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

int colorTrack = 0;
color rgb;
color* rgb_ptr = &rgb;

pixel sea[NUMPIXELS];

int row = 1;
int dir = 0;
int rangeLow = 0;
int rangeHigh = 0;

void setup() {
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
  
  rangeLow = row*5;
  rangeHigh = row*5+5;

  //Serial.print("row:");
  //Serial.println(row);

  for (int i = 0; i < NUMPIXELS; i++) {
    if (i >= rangeLow  && i < rangeHigh ){
      setPixel(&sea[i], i, intToRgbStrength(100, 8));
    } else {
      setPixel(&sea[i], i, intToRgbStrength(120, 0));
    }

  }

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(snakeToMatrix(i), pixels.Color(sea[i].color.r, sea[i].color.g, sea[i].color.b));
    pixels.show();  // Send the updated pixel colors to the hardware.
  }

//  delay(DELAYVAL);
  if (dir){
    row++;
  } else {
    row--;
  }
  if(row > 6 || row < 1 ){
    dir = !dir;
  }
  //pixels.clear();
  //    pixels.show();   // Send the updated pixel colors to the hardware.
}
