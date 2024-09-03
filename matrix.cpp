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

color* intToRgb(int colorRange)
{
    static color rgb = {.r = 0, .g = 0, .b = 0};

    if(colorRange < COLOR_RESOLUTION_MAX)
    {
        rgb.r = COLOR_RESOLUTION_MAX - colorRange;
        rgb.g = colorRange;
        rgb.b = 0;

    } else if(colorRange >= COLOR_RESOLUTION_MAX && colorRange < COLOR_RESOLUTION_MAX*2){
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

	return &rgb;
};

color* intToRgbStrength(int colorRange, double strength)
{

    if(strength > 10){
        strength = 10;
    }
    else if(strength < 0)
    {
        strength = 0;
    }

    color* rgb_ptr = intToRgb(colorRange);

    strength = ((double) strength * COLOR_VALUE_MAX / (COLOR_STRENGTH_MAX * 100));

    rgb_ptr->r = (int) (rgb_ptr->r * (double) strength); // x [0-100] * Y = color
    rgb_ptr->g = (int) (rgb_ptr->g * (double) strength); // color max/ strength
    rgb_ptr->b = (int) (rgb_ptr->b * (double) strength);

    return rgb_ptr;

};

int setPixel(pixel seaMatrix[], int place, color* rgb)
{
    place = snakeToMatrix(place);
    seaMatrix[place] = *createPixel(place, *rgb);
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
    return &p;
};