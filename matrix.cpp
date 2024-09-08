#include "matrix.h"
#include <stdio.h>
//#include "battleSips.ino"
#include <Arduino.h>

#define COLOR_RESOLUTION_MAX    100
#define COLOR_VALUE_MAX         250
#define COLOR_STRENGTH_MAX      10




typedef struct{
    int numberOfPixels;

    //Adafruit_NeoPixel pixels;
}matrix;





/**
 * i: 0     1   -   99  100	101	-	199	200	201 -	299
 * R: 100   99  -   1   0   0   -   0   0   1   -   99  
 * G: 0     1   -   99  100 99  -   1   0   0   -   0   
 * B: 0     0   -   0   0   1   -   99  100 99  -   1  
 */

color intToRgb(int colorRange)
{
    color rgb = {.r = 0, .g = 0, .b = 0};

    if(colorRange < COLOR_RESOLUTION_MAX)
    {
        rgb.r = COLOR_RESOLUTION_MAX - colorRange;
        rgb.g = colorRange;
        rgb.b = 0;

    } else if(colorRange >= COLOR_RESOLUTION_MAX && colorRange <= (COLOR_RESOLUTION_MAX*2)){
        colorRange = colorRange - COLOR_RESOLUTION_MAX;
        

        rgb.g = COLOR_RESOLUTION_MAX - colorRange;
        rgb.b = colorRange;
        rgb.r = 0;
    
    } else if(colorRange > COLOR_RESOLUTION_MAX*2){
        colorRange =  colorRange - COLOR_RESOLUTION_MAX*2;
        
        rgb.b = COLOR_RESOLUTION_MAX - colorRange;
        rgb.r = colorRange;
        rgb.g = 0;
	}
  Serial.print("intToRgb  | r: ");
  Serial.print(rgb.r);
  Serial.print(", g: ");
  Serial.print(rgb.g);
  Serial.print(", b: ");
  Serial.println(rgb.b);
	return rgb;
};

color intToRgbStrength(int colorRange, double strength)
{

    if(strength > 10){
        strength = 10;
    }
    else if(strength < 0)
    {
        strength = 0;
    }

    color rgb;
    rgb.r = intToRgb(colorRange).r;
    rgb.g = intToRgb(colorRange).g;
    rgb.b = intToRgb(colorRange).b;
    
    strength = ((double) strength * COLOR_VALUE_MAX / (COLOR_STRENGTH_MAX * 100));

    rgb.r = (int) (rgb.r * (double) strength); // x [0-100] * Y = color
    rgb.g = (int) (rgb.g * (double) strength); // color max/ strength
    rgb.b = (int) (rgb.b * (double) strength);
    
    Serial.print("intToRgbStrength | r: ");
    Serial.print(rgb.r);
    Serial.print(", g: ");
    Serial.print(rgb.g);
    Serial.print(", b: ");
    Serial.println(rgb.b);

    return rgb;

};

int setPixel(pixel* pixel, int place, color rgb)
{
    pixel->place = place;
    pixel->color.r = rgb.r;
    pixel->color.g = rgb.g;
    pixel->color.b = rgb.b;

    // Serial.print("setPixel - Place: ");
    // Serial.println(place);
    //place = snakeToMatrix(place);
    // Serial.print("setPixel - seaMatrix[place]: ");
    // Serial.println((&seaMatrix[0]));
    //seaMatrix[place] = createPixel(place, *rgb);
}

int snakeToMatrix(int pos)
{
  if(((pos / 5) % 2) != 0){
    //Serial.println(pos);
    pos = ((pos / 5) * (5))  + (4 - (pos % 5));
    //Serial.println(pos);
  }
  return pos;
};

pixel* createPixel(int place, color rgb)
{
    static pixel p = {place, rgb};
    // Serial.print("createPixel - &p:");
    // Serial.println((&p));
    return &p;
};