#include "matrix.h"
#include <stdio.h>


#define COLOR_RESOLUTION_MAX    100
#define COLOR_VALUE_MAX         100
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

color* intToColor(int colorRange)
{
    static color rgb = {.r = 0, .g = 0, .b = 0};

    if(colorRange < COLOR_RESOLUTION_MAX)
    {
        rgb.r = COLOR_RESOLUTION_MAX - colorRange;
        rgb.g = colorRange;
        rgb.b = 0;

    } else if(colorRange >= COLOR_RESOLUTION_MAX && colorRange > COLOR_RESOLUTION_MAX*2){
        colorRange = COLOR_RESOLUTION_MAX - colorRange;
        

        rgb.g = colorRange - COLOR_RESOLUTION_MAX;
        rgb.b = colorRange;
        rgb.r = 0;
    
    } else if(colorRange > COLOR_RESOLUTION_MAX*3){
        colorRange = COLOR_RESOLUTION_MAX*2 - colorRange;
        
        rgb.b = colorRange - COLOR_RESOLUTION_MAX;
        rgb.r = colorRange;
        rgb.g = 0;
	}

	return &rgb;
};

color* setColor(int colorRange, double strength)
{
    static color rgb = {.r = 0, .g = 0, .b = 0};
    static color* rgb_ptr = &rgb;

    if(strength > 10){
        strength = 10;
    }
    else if(strength < 0)
    {
        strength = 0;
    }

    rgb_ptr = intToColor(colorRange);

    strength = (COLOR_VALUE_MAX / COLOR_STRENGTH_MAX) * strength;

    rgb_ptr->r = rgb_ptr->r*strength;
    rgb_ptr->r = rgb_ptr->r*strength;
    rgb_ptr->r = rgb_ptr->r*strength;

    return rgb_ptr;

};


/* int setColor(int color, int pixel, Adafruit_NeoPixel pixels)
{
    pixels.setPixelColor(i, pixels.Color(1, 1, 0));
}; */