#ifndef MATRIX_H
#define MATRIX_H
//#include <Adafruit_NeoPixel.h>

typedef struct{
    int r;
    int g;
    int b;    
}color;

typedef struct{
    int place;
    color color;
}seaDex;

#define RED     0
#define GREEN   1
#define BLUE    2

color* setColor(int colorRange, double strength);
color* intToColor(int colorInt);


#endif