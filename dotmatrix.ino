#include "Dot.h"
const int DIRECT[] = {1, 2, 3, 4, 5, 6};
const int REGISTER[] = {7, 8, 9, 10, 11, 12}; //bに登録する
const int ANODE[] = {1, 3, 10, 7, 8};
const int CATHODE[] = {12, 11, 2, 9, 4, 5, 6}; //0で通電
const int BASE_BIT = B00000000;
const int REGISTER_PIN_HEAD = 7;
const int NUM_PIN_ONESIDE = 6;
const int SELECT = 4;
const int FLAG = 5;

void resetDotMatrix () {
  int b = BASE_BIT;
  for (int i=0; i<ROW; i++) {
    b |= write(ANODE[i], low);
    for (int j=0; j<COL; j++) {
      b |= write(CATHODE[j], high);
    }
  }
  reg(b);
}
void dotMatrix (Dot (*arrays)[COL], int count) {
  resetDotMatrix();
  int b = BASE_BIT;
  b |= write(ANODE[count], high);
  for (int j=0; j<COL; j++) {
    b |= write(CATHODE[j], arrays[count][j]);
  }
  reg(b);
}

int write (int pin, Dot dot) {
  int result;
  if (isValue(DIRECT, pin)) {
    if (dot.getIsSelected()) {
      light(MAT[pin], SELECT);
    }
    else if (dot.getIsFlag()) {
      light(MAT[pin], FLAG);
    }
    else if (dot.getState()==OPEN) {
      light(MAT[pin], OPEN);
    }
    return 0;
  }
  else if (isValue(REGISTER, pin)) {
    if (dot.getIsSelected()) {
      if (millis()%1000 <= 499) result = B10000000;
      else                      result = B00000000;
    }
    else if (dot.getIsFlag()) {
      if (millis()%1000 <= 699) result = B10000000;
      else                      result = B00000000;
    }
    else if (dot.getState()==OPEN) {
      result = B00100000;
    }
    else {
      result = B00000000;
    }
    result = result >> (pin-REGISTER_PIN_HEAD);
    return result;
  }
}

void light(uint8_t pin, int mode) {
  if (mode==SELECT) {

  }
  else if (mode==FLAG) {

  }
  else if (mode==OPEN) {
    digitalWrite(pin, 0);
  }
}

void reg (int b) {
  digitalWrite(REG_LATCH, LOW);
  shiftOut(REG_SER, REG_CLK, LSBFIRST, b);
  digitalWrite(REG_LATCH, HIGH);
}

bool isValue (int *array, int value) {
  int size;
  if (array==DIRECT || array==REGISTER) size = NUM_PIN_ONESIDE;
  else if (array==ANODE) size = ROW;
  else if (array==CATHODE) size = COL;
  for (int i=0; i<size; i++) {
    if (array[i]==value) {
      return true;
    }
  }
  return false;
}

void initDotMatrix () {
  for (int i=1; i<NUM_PIN_ONESIDE+1; i++) pinMode(MAT[i], OUTPUT);
  pinMode(REG_SER, OUTPUT);
  pinMode(REG_LATCH, OUTPUT);
  pinMode(REG_CLK, OUTPUT);
  digitalWrite(MAT[1], LOW);
  digitalWrite(MAT[3], LOW);
  digitalWrite(MAT[2], HIGH);
  digitalWrite(MAT[4], HIGH);
  digitalWrite(MAT[5], HIGH);
  digitalWrite(MAT[6], HIGH);
  reg(B00110100);
}

void printField (Dot (*arrays)[COL]) {
  for (int i=0; i<ROW; i++) {
    for (int j=0; j<COL; j++) {
      if (arrays[i][j].getIsSelected()) {
        Serial.print("SE");
      }
      else if (arrays[i][j].getIsFlag()) {
        Serial.print("FL");
      }
      else if (arrays[i][j].getState()==OPEN) {
        Serial.print("OP");
      }
      else if (arrays[i][j].getState()==CLOSE) {
        Serial.print("CL");
      }
      else if (arrays[i][j].getState()==MINE) {
        Serial.print("MI");
      }
      Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.println("============================");
}