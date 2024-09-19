#ifndef MATRIX_H
#define MATRIX_H
#include <Adafruit_NeoPixel.h>

typedef struct{
    int r;
    int g;
    int b;    
}color;

typedef struct{
    int place;
    color color;
}pixel;

typedef struct{
    int pixelAmount;
    int pixelRow;
    int pixelColumn;
    pixel pixelArray[100];
    Adafruit_NeoPixel* pixelsAdafruit;
}pixelMatrix;

#define RED     0
#define GREEN   1
#define BLUE    2

color intToRgbStrength(int colorInt, double strength);
color intToRgb(int colorInt);
int snakeToMatrix(int pos);
int setPixel(pixel seaMatrix[], int place, color rgb);
pixel* createPixel(int place, color rgb);

#endif