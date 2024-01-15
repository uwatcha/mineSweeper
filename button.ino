#include "Dot.h"
bool buttonFlag = false;
void buttonA () {
  if (buttonIsON(BUTTON_A)) {
    Serial.println("a");
    switch (getMode()) {
      case 1://上
      break;
      case 2://下
      break;
      case 3://左
      break;
      case 4://右
      break;
    }
    delay(200);
  }
}


void buttonB () {
  if (buttonIsON(BUTTON_B)) {
    Serial.println("b");
    delay(70);
  }
}

void buttonC () {
  if (buttonIsON(BUTTON_C)) {
    Serial.println("c");
    delay(30);
  }
}


bool buttonIsON (uint8_t button) {
  //delay(50);
  if (digitalRead(button)==LOW && !buttonFlag && millis()%50==0) {
    buttonFlag = true;
    sound(button);
    return 1;
  }
  else if (digitalRead(button)==LOW && buttonFlag && millis()%50==0) {
    return 0;
  }
  else {
    buttonFlag = false;
    return 0;
  }
}