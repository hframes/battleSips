// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include "pushbutton.h"
#include "matrix.h"
#include "matrixAnimation.h"

#include <Adafruit_NeoPixel.h>

#define DELAYVAL 0  // Time (in milliseconds) to pause between pixels

#define PIN 9
#define NUMPIXELS 40
#define ROW 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

int colorTrack = 0;
color rgb;
color* rgb_ptr = &rgb;

pixelMatrix seaMatrix = {
  .pixelAmount = 40,
  .pixelRow = 5,
  .pixelColumn = 8
};
  

void setup() {
  Serial.begin(9600);
  pixels.begin();

  Serial.println("------------------------");
  Serial.println("Welcome to BattleSips!");
  Serial.println("------------------------");

  seaMatrix.pixelsAdafruit =  &pixels;
}

void loop() {
  Serial.println("- Running 'Knightrider'");
  lightrider(5, &seaMatrix);

}
