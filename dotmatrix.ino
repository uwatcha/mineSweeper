#include "Dot.h"
const int DIRECT[] = {1, 2, 3, 4, 5, 6};
const int REGISTER[] = {7, 8, 9, 10, 11, 12}; //bに登録する
const int ANODE[] = {1, 3, 10, 7, 8};
const int CATHODE[] = {12, 11, 2, 9, 4, 5, 6}; //0で通電
const int BASE_BIT = B001011;
const int REGISTER_PIN_HEAD = 7;


void resetDotMatrix () {
  digitalWrite(MAT[1], 0);
  digitalWrite(MAT[2], 1);
  digitalWrite(MAT[3], 0);
  digitalWrite(MAT[4], 1);
  digitalWrite(MAT[5], 1);
  digitalWrite(MAT[6], 1);
  reg(BASE_BIT);
}

void makeClearDisplay(Dot (*arrays)[COL]) {
  int _row[] = {0, 1, 3, 4, 2, 0, 1, 3, 4, 0, 0, 1, 2, 3, 4, 0};
  int _col[] = {0, 0, 0, 0, 1, 2, 2, 2, 2, 4, 5, 5, 5, 5, 5, 6};
  for (int i=0; i<16; i++) {
    arrays[_row[i]][_col[i]].setOpen();
  }
}

void dotMatrix (Dot (*arrays)[COL], int count) {
  int b = BASE_BIT;
  b ^= writeAnode(ANODE[count]);
  for (int j=0; j<COL; j++) {
    b ^= writeCathode(CATHODE[j], arrays[count][j]);
  }
  reg(b);
}

int writeAnode (int pin) {
  if (isValue(DIRECT, pin)) {
    digitalWrite(MAT[pin], 1);
    return 0;
  }
  else if (isValue(REGISTER, pin)) {
    int result = B100000;
    result = result >> (pin-REGISTER_PIN_HEAD);
    return result;
  }
}

int writeCathode (int pin, Dot dot) {
  if (isValue(DIRECT, pin)) {
    if (dot.getIsSelected()) {
      if ((millis()%1500 <= 1399)) digitalWrite(MAT[pin], 0);
      else                      digitalWrite(MAT[pin], 1);
    }
    else if (dot.getIsFlag()) {
      if (millis()%500 <= 249)  digitalWrite(MAT[pin], 0);
      else                      digitalWrite(MAT[pin], 1);
    }
    else if (dot.getState()==OPEN) {
      digitalWrite(MAT[pin], 0);
    }
    else {
      digitalWrite(MAT[pin], 1);
    }
    return 0;
  }
  else if (isValue(REGISTER, pin)) {
    int result;
    if (dot.getIsSelected()) {
      if (millis()%1500 <= 1399) result = B100000;
      else                      result = B000000;
    }
    else if (dot.getIsFlag()) {
      if (millis()%500 <= 249) result = B100000;
      else                      result = B000000;
    }
    else if (dot.getState()==OPEN) {
      result = B100000;
    }
    else {
      result = B000000;
    }    
    result >>= (pin-REGISTER_PIN_HEAD);
    return result;
  }
}

void reg (int b) {
  digitalWrite(REG_LATCH, LOW);
  shiftOut(REG_SER, REG_CLK, LSBFIRST, b);
  digitalWrite(REG_LATCH, HIGH);
}

bool isValue (int *array, int value) {
  for (int i=0; i<NUM_PIN_ONESIDE; i++) {
    if (array[i]==value) {
      return true;
    }
  }
  return false;
}

void printField (Dot (*arrays)[COL]) {
  for (int i=0; i<ROW; i++) {
    for (int j=COL-1; j>=0; j--) {
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