// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include "pushbutton.h"
#include "matrix.h"
#include <Adafruit_NeoPixel.h>

#define DELAYVAL 1000 // Time (in milliseconds) to pause between pixels

#define PIN        9
#define NUMPIXELS 40 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

int colorTrack = 0;
color rgb;
color* rgb_ptr = &rgb;

pixel sea[NUMPIXELS];


void setup() {
  Serial.begin(9600);
  pixels.begin();

}

void loop() {

  for(int i = 0; i < NUMPIXELS; i++){
    setPixel(sea, i, intToRgbStrength(200, 1));
  }

  for(int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(snakeToMatrix(i), pixels.Color(sea[i].color.r, sea[i].color.g, sea[i].color.b));
      //pixels.setPixelColor(snakeToMatrix(i), pixels.Color(10, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.
      delay(DELAYVAL); // Pause before next pass through loop
  }

    pixels.clear();
//    pixels.show();   // Send the updated pixel colors to the hardware.
}
