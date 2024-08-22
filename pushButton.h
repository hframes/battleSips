#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#define BUTTON_PRESSED	1
#define BUTTON_RELEASED	0

#include <Arduino.h>

typedef struct pushButton{
    int pin;
    int nbrPresses;
    int lastPress;
} pushButton;

pushButton* newPushButton(int pin);
int updateButton(pushButton* button);
int getButtonPress(pushButton* button);
#endif