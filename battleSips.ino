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
color *rgb_ptr = &rgb;

pixelMatrix seaMatrix = {
  .pixelAmount = 40,
  .pixelRow = 5,
  .pixelColumn = 8
};

int length = 20;

int column = 4;

int array[20];



void setup() {

  for (int i = 0; i<length; i++){
  array[i] = i;
}
  Serial.begin(9600);
  pixels.begin();

  Serial.println("\n\n------------------------");
  Serial.println("Welcome to BattleSips!");
  Serial.println("------------------------");

  seaMatrix.pixelsAdafruit = &pixels;
}


void loop() {

  // Serial.println("- Running 'Knightrider'");
  // lightrider(5, &seaMatrix);

  // Serial.println("\n- Running 'animationWave'");
  // animationWave(30, &seaMatrix);

  Serial.println("\n-> matrix test <-");
    Serial.print("row:   \t\t[0,\t 1,\t 2,\t 3]\n");
    for (int anim = 0; anim < length-column+1; anim++) {

      Serial.print("\nanim(");
      Serial.print(anim);
      Serial.print(")  \t[");
      Serial.print(array[anim]);
      Serial.print(",\t ");
      Serial.print(array[anim+1]);
      Serial.print(",\t ");
      Serial.print(array[anim+2]);
      Serial.print(",\t ");
      Serial.print(array[anim+3]);
      Serial.print("]");
  }
  delay(10000);
}
