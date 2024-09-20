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

int lightrider(int seconds, pixelMatrix *pixelMatrix)
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
                setPixel(&pixelMatrix->pixelArray[i], i, intToRgbLight(180, 1));
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

int animationWave(int seconds, pixelMatrix *pixelMatrix)
{

    int end = millis() + seconds * 1000;

    int length = 40;
    int rows[length];

    Serial.print("\nrows[i]: ");
    for (int i = 0; i < length; i++)
    {
        if (i < 8)
        {
            rows[i] = 0;
        }
        else if (i < 32)
        {
            rows[i] = 20 - ((i - 8) * 20 / ((double)25));
        }
        else
        {
            rows[i] = 1;
        }
        Serial.print(rows[i]);
    }

    pixelMatrix->pixelsAdafruit->clear();

    for (int anim = 0; anim < length - 7; anim++)
    {
                    Serial.print("\n anim: ");
                    Serial.print(anim);

        for (int i = 0; i < pixelMatrix->pixelAmount; i++)
        {
            setPixel(&pixelMatrix->pixelArray[i], i, intToRgbLight(200, rows[anim + (i / 5)]));

        }
        delay(50);
        for (int i = 0; i < pixelMatrix->pixelAmount; i++)
        {
            // pixels.setPixelColor(snakeToMatrix(i), pixels.Color(sea[i].color.r, sea[i].color.g, sea[i].color.b));
            pixelMatrix->pixelsAdafruit->setPixelColor(snakeToMatrix(i), pixelMatrix->pixelsAdafruit->Color(pixelMatrix->pixelArray[i].color.r, pixelMatrix->pixelArray[i].color.g, pixelMatrix->pixelArray[i].color.b));
            pixelMatrix->pixelsAdafruit->show(); // Send the updated pixel colors to the hardware.
        }
    }
    while (millis() < end)
    {
    }

    return 1;
}
