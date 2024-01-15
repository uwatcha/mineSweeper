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

void dotMatrix (Dot (*arrays)[COL], int count) {
  int b = BASE_BIT;
  b ^= writeAnode(ANODE[count]);
  // Serial.println("set anode");
  for (int j=0; j<COL; j++) {
    //if (count==0 && j==3) Serial.println(arrays[count][j].getIsSelected());
    b ^= writeCathode(CATHODE[j], arrays[count][j]);
    if (count==0 && j==3) Serial.println(b, BIN);
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
    //result ^= (1 << pin-REGISTER_PIN_HEAD); 
    return result;
  }
}

int writeCathode (int pin, Dot dot) {
  if (isValue(DIRECT, pin)) {
    //Serial.println("DIRECT");
    // if (dot.getRow()==2 && dot.getCol()==3) {
    //   Serial.println(dot.getRow());
    //   Serial.println(dot.getCol());
    // }
    if (dot.getIsSelected()) {
      if (millis()%1000 <= 499) digitalWrite(MAT[pin], 0);
      else                      digitalWrite(MAT[pin], 1);
      //if (dot.getRow()==1 && dot.getCol()==3)Serial.println("isSelected_DIR");
    }
    else if (dot.getIsFlag()) {
      if (millis()%1000 <= 699) digitalWrite(MAT[pin], 0);
      else                      digitalWrite(MAT[pin], 1);
      //if (dot.getRow()==1 && dot.getCol()==3)Serial.println("isFlag");
    }
    else if (dot.getState()==OPEN) {
      digitalWrite(MAT[pin], 0);
      //if (dot.getRow()==1 && dot.getCol()==3)Serial.println("isOpen");
    }
    else {
      digitalWrite(MAT[pin], 1);
      //if (dot.getRow()==1 && dot.getCol()==3)Serial.println("else");
    }
    return 0;
  }
  else if (isValue(REGISTER, pin)) {
    int result;
    if (dot.getRow()==2 && dot.getCol()==3) {
      //if (dot.getRow()==1 && dot.getCol()==3) Serial.println(dot.getIsSelected());
    }
    if (dot.getIsSelected()) {
      if (millis()%1000 <= 499) result = B100000;
      else                      result = B000000;
      //if (dot.getRow()==1 && dot.getCol()==3) Serial.println("isSelected_REG");
    }
    else if (dot.getIsFlag()) {
      if (millis()%1000 <= 699) result = B100000;
      else                      result = B000000;
      //if (dot.getRow()==1 && dot.getCol()==3) Serial.println("isFlag_REG");
    }
    else if (dot.getState()==OPEN) {
      result = B100000;
      //if (dot.getRow()==1 && dot.getCol()==3) Serial.println("isOpen_REG");
    }
    else {
      result = B000000;
      //if (dot.getRow()==1 && dot.getCol()==3) Serial.println("else_REG");
    }    
    result >>= (pin-REGISTER_PIN_HEAD);
    //if (!(pin==1 || pin==3 || pin==10 || pin==7 || pin==8)) Serial.println(result, BIN);
    // if (dot.getRow()==2 && dot.getCol()==3) {
    //   Serial.println(result, BIN);
    // }
    //if (dot.getRow()==1 && dot.getCol()==3) Serial.println(result, BIN);
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

// void initDotMatrix () {
//   for (int i=1; i<NUM_PIN_ONESIDE+1; i++) pinMode(MAT[i], OUTPUT);
//   pinMode(REG_SER, OUTPUT);
//   pinMode(REG_LATCH, OUTPUT);
//   pinMode(REG_CLK, OUTPUT);
//   digitalWrite(MAT[1], LOW);
//   digitalWrite(MAT[3], LOW);
//   digitalWrite(MAT[2], HIGH);
//   digitalWrite(MAT[4], HIGH);
//   digitalWrite(MAT[5], HIGH);
//   digitalWrite(MAT[6], HIGH);
//   reg(B00110100);
// }

void printField (Dot (*arrays)[COL]) {
  Serial.println("");
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