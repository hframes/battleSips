#include "pushButton.h"

#define DEBOUNCE 250

// Returns a pointer to a new push button on pin
pushButton* newPushButton(int pin){
    pushButton but= {pin, 0, millis()};
    return &but;
}


int readButton(pushButton* button){
    // Pull-up -> 1 = released, 0 = pressed 
    if(digitalRead(button->pin)){
        return BUTTON_RELEASED;
    }
    return BUTTON_PRESSED;
}

int updateButton(pushButton* button){
    int now;
    if(readButton(button) == BUTTON_PRESSED){
        now = millis();
        if(now > DEBOUNCE + button->lastPress){
            button->nbrPresses++;
            button->lastPress = now;
        }
    }
    return 0;
}

int getButtonPresses(pushButton* button){
    int nbrPresses = button->nbrPresses;
    if (nbrPresses > 0){
        button->nbrPresses--;
    }
    return nbrPresses;
}