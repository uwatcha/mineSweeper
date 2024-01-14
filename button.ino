bool buttonFlag = false;
void buttonA () {
  if (buttonIsON(BUTTON_A)) {
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
  }
}


void buttonB () {
  if (buttonIsON(BUTTON_B)) {

  }
}

void buttonC () {
  if (buttonIsON(BUTTON_C)) {

  }
}


bool buttonIsON (uint8_t button) {
  //delay(50);
  if (digitalRead(button)==LOW && !buttonFlag) {
    buttonFlag = true;
    sound(button);
    return 1;
  }
  else if (digitalRead(button)==LOW && buttonFlag) {
    return 0;
  }
  else {
    buttonFlag = false;
    return 0;
  }
}