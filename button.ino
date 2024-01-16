#include "Dot.h"
bool buttonFlag = false;
void buttonA (Dot (*arrays)[COL]) {
  if (buttonIsON(BUTTON_A)) {
    Serial.println("a");
    int selectedRow = findSelectedCoordinate(arrays, ROW);
    int selectedCol = findSelectedCoordinate(arrays, COL);
    int movedRow = selectedRow;
    int movedCol = selectedCol;
    switch (getMode()) {
      case 1://上
        if (selectedRow!=0) movedRow--;
        arrays[selectedRow][selectedCol].setSelect();
        arrays[movedRow][selectedCol].setSelect();
        break;
      case 2://下
        if (selectedRow!=ROW-1) movedRow++;
        arrays[selectedRow][selectedCol].setSelect();
        arrays[movedRow][selectedCol].setSelect();
        break;
      case 3://左
        if (selectedCol!=COL-1) movedCol++;
        arrays[selectedRow][selectedCol].setSelect();
        arrays[selectedRow][movedCol].setSelect();
        break;
      case 4://右
        if (selectedCol!=0) movedCol--;
        arrays[selectedRow][selectedCol].setSelect();
        arrays[selectedRow][movedCol].setSelect();
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
    if(!isInitedField) initField(arrays);
    int selectedRow = findSelectedCoordinate(arrays, ROW);
    int selectedCol = findSelectedCoordinate(arrays, COL);
    arrays[selectedRow][selectedCol].dig();
    delay(70);
    printField(field);
  }
}

void buttonC (Dot (*arrays)[COL]) {
  if (buttonIsON(BUTTON_C)) {
    Serial.println("c");
    int selectedRow = findSelectedCoordinate(arrays, ROW);
    int selectedCol = findSelectedCoordinate(arrays, COL);
    arrays[selectedRow][selectedCol].setFlag();
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