#include "matrix.h"
#include <stdio.h>
// #include "battleSips.ino"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define COLOR_RESOLUTION_MAX 100
#define COLOR_VALUE_MAX 250
#define COLOR_STRENGTH_MAX 10
#define COLOR_STRENGTH_MIN 0

/**
 * Color:   RED 	 R/G         GREEN     G/B        BLUE     B/R
 * i:       0     1   -   99  100	101	-	199	200	201 -	299
 * R:       100   99  -   1   0   0   -   0   0   1   -   99
 * G:       0     1   -   99  100 99  -   1   0   0   -   0
 * B:       0     0   -   0   0   1   -   99  100 99  -   1
 */

color intToRgb(int colorRange)
{
    color rgb = {.r = 0, .g = 0, .b = 0};
    if (colorRange < COLOR_RESOLUTION_MAX)
    {
        // RED
        rgb.r = COLOR_RESOLUTION_MAX - colorRange;
        rgb.g = colorRange;
        rgb.b = 0;
    }
    else if (colorRange >= COLOR_RESOLUTION_MAX && colorRange <= (COLOR_RESOLUTION_MAX * 2))
    {
        // GREEN
        colorRange = colorRange - COLOR_RESOLUTION_MAX;

        rgb.g = COLOR_RESOLUTION_MAX - colorRange;
        rgb.b = colorRange;
        rgb.r = 0;
    }
    else if (colorRange > COLOR_RESOLUTION_MAX * 2)
    {
        // BLUE
        colorRange = colorRange - COLOR_RESOLUTION_MAX * 2;

        rgb.b = COLOR_RESOLUTION_MAX - colorRange;
        rgb.r = colorRange;
        rgb.g = 0;
    }

    return rgb;
};

color intToRgbStrength(int colorRange, double strength)
{

    if (strength > COLOR_STRENGTH_MAX)
    {
        strength = COLOR_STRENGTH_MAX;
    }
    else if (strength < COLOR_STRENGTH_MIN)
    {
        strength = COLOR_STRENGTH_MIN;
    }

    color rgb;
    rgb.r = intToRgb(colorRange).r;
    rgb.g = intToRgb(colorRange).g;
    rgb.b = intToRgb(colorRange).b;

    strength = ((double)strength * COLOR_VALUE_MAX / (COLOR_STRENGTH_MAX * 100));

    rgb.r = (int)(rgb.r * (double)strength);
    rgb.g = (int)(rgb.g * (double)strength);
    rgb.b = (int)(rgb.b * (double)strength);

    return rgb;
};

int setPixel(pixel *pixel, int place, color rgb)
{
    pixel->place = place;
    pixel->color.r = rgb.r;
    pixel->color.g = rgb.g;
    pixel->color.b = rgb.b;
}

int snakeToMatrix(int pos)
{
    if (((pos / 5) % 2) != 0)
    {
        pos = ((pos / 5) * (5)) + (4 - (pos % 5));
    }
    return pos;
};

pixel *createPixel(int place, color rgb)
{
    static pixel p = {place, rgb};
    return &p;
};