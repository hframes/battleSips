// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include "pushbutton.h"
#include "matrix.h"
#include <Adafruit_NeoPixel.h>

//int* rgb[3] = {0, 0, 0};
//int* rgb[3] = {0, 0, 0};
color rgb;
color* rgb_ptr = &rgb;

int colorTrack = 0;
#define PIN        9

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 40 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels


void setup() {
  Serial.begin(9600);
  pixels.begin();

}

void loop() {


  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    
    rgb_ptr = setColor(colorTrack, 1);
    
    pixels.setPixelColor(i, pixels.Color(rgb_ptr->r, rgb_ptr->g, rgb_ptr->b));

    Serial.print("R: ");
    Serial.print(rgb_ptr->r);
    Serial.print(" G: ");
    Serial.print(rgb_ptr->g);
    Serial.print(" B: ");
    Serial.println(rgb_ptr->b);

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    (colorTrack > 298) ? colorTrack = 0 : colorTrack++  ;
  }

for(int i=NUMPIXELS; i>=0; i--) { // For each pixel...


    pixels.setPixelColor(i, pixels.Color(0, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}

int printINO(char* msg){
  Serial.println(msg);
}