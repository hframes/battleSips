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

    unsigned long start = millis();
    int end = millis() + seconds * 1000;

    int length = 40;
    int rows[length];
    int delayMillis = 10;

    // Create wave
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
    }

    pixelMatrix->pixelsAdafruit->clear();

    int testAnim = 1;

    // Run through animation
        Serial.print("row: \t[0,\t 1,\t 2,\t 3]");
    for (int anim = 0; anim < length - 7; anim++)
    {

        Serial.print("\nanim: \t[");
        Serial.print(anim);
        Serial.print(",\t ");
        Serial.print(anim+1);
        Serial.print(",\t ");
        Serial.print(anim+2);
        Serial.print(",\t ");
        Serial.print(anim+3);
        Serial.print("]");

        if (anim > 12 && anim < 28)
        {
            Serial.print(" -> ");
            Serial.print(anim - anim / 5);
            testAnim++;

            // setPixel(&pixelMatrix->pixelArray[i], i, intToRgbLight(100, rows[anim - i + (i / 5)]));
        }

        for (int i = 0; i < pixelMatrix->pixelAmount; i++)
        {
            int rowOffset = (i / 5);
            setPixel(&pixelMatrix->pixelArray[i], i, intToRgbLight(200, rows[anim + rowOffset]));

        }
        delay(delayMillis);
        for (int i = 0; i < pixelMatrix->pixelAmount; i++)
        {
            // pixels.setPixelColor(snakeToMatrix(i), pixels.Color(sea[i].color.r, sea[i].color.g, sea[i].color.b));
            pixelMatrix->pixelsAdafruit->setPixelColor(snakeToMatrix(i), pixelMatrix->pixelsAdafruit->Color(pixelMatrix->pixelArray[i].color.r, pixelMatrix->pixelArray[i].color.g, pixelMatrix->pixelArray[i].color.b));
            pixelMatrix->pixelsAdafruit->show(); // Send the updated pixel colors to the hardware.
        }
    }
    while (millis() - start < seconds * 1000)
    {
        // Serial.print("\n time remaning: ");
        // Serial.print((seconds * 1000) - (millis()-start));
    }

    return 1;
}
