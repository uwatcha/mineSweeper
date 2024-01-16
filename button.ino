#include "Dot.h"
bool buttonFlag = false;
void buttonA (Dot (*arrays)[COL]) {
  if (buttonIsON(BUTTON_A)) {
    Serial.println("a");
    Dot _selected = *findSelectedDot(arrays);
    int selectedRow = _selected.getRow();
    int selectedCol = _selected.getCol();
    int movedRow = selectedRow;
    int movedCol = selectedCol;
    switch (getMode()) {
      case 1://上
        if (selectedRow!=0) movedRow--;
        field[selectedRow][selectedCol].setSelect();
        field[movedRow][selectedCol].setSelect();
        break;
      case 2://下
        if (selectedRow!=ROW-1) movedRow++;
        field[selectedRow][selectedCol].setSelect();
        field[movedRow][selectedCol].setSelect();
        break;
      case 3://左
        if (selectedCol!=COL-1) movedCol++;
        field[selectedRow][selectedCol].setSelect();
        field[selectedRow][movedCol].setSelect();
        break;
      case 4://右
        if (selectedCol!=0) movedCol--;
        field[selectedRow][selectedCol].setSelect();
        field[selectedRow][movedCol].setSelect();
        break;
    }
    delay(40);
    // for (int i=0; i<ROW; i++) {
    //   for (int j=0; j<COL; j++) {
    //     if (field[i][j].getIsSelected()){
    //       Serial.print(field[i][j].getRow());
    //       Serial.print(" ");
    //       Serial.println(field[i][j].getCol());
    //     }
    //   }
    // }
    printField(field);
  }
}


void buttonB (Dot (*arrays)[COL]) {
  if (buttonIsON(BUTTON_B)) {
    Serial.println("b");
    delay(70);
    printField(field);
  }
}

void buttonC (Dot (*arrays)[COL]) {
  if (buttonIsON(BUTTON_C)) {
    Serial.println("c");
    Dot _selected = *findSelectedDot(arrays);
    _selected.setFlag();
    delay(30);
    printField(field);
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