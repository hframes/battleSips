#include "matrixAnimation.h"

int knightrider(int seconds, pixelMatrix *pixelMatrix)
{

    int end = millis() + seconds * 1000;

    int row = 1;
    int dir = 0;
    int rangeLow = 0;
    int rangeHigh = 0;

    while (millis() < end)
    {
        rangeHigh = row * 5 + 5;
        rangeLow = row * 5;

        for (int i = 0; i < pixelMatrix->pixelAmount; i++)
        {
            if (i >= rangeLow && i < rangeHigh)
            {
                setPixel(&pixelMatrix->pixelArray[i], i, intToRgbStrength(100, 1));
            }
            else
            {
                setPixel(&pixelMatrix->pixelArray[i], i, intToRgbStrength(200, 0));
            }
        }

        for (int i = 0; i < pixelMatrix->pixelAmount; i++)
        {
            // pixels.setPixelColor(snakeToMatrix(i), pixels.Color(sea[i].color.r, sea[i].color.g, sea[i].color.b));
            pixelMatrix->pixelsAdafruit->setPixelColor(snakeToMatrix(i), pixelMatrix->pixelsAdafruit->Color(pixelMatrix->pixelArray[i].color.r, pixelMatrix->pixelArray[i].color.g, pixelMatrix->pixelArray[i].color.b));
            pixelMatrix->pixelsAdafruit->show(); // Send the updated pixel colors to the hardware.
        }

        (dir) ? row++ : row--; 
        
        (row > 6 || row < 1) ? dir = !dir : 0;

    }

    return 1;
}
