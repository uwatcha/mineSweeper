#include "Arduino.h"
#include "Dot.h"


Dot::Dot() {}
Dot::Dot(int _row, int _col, int _state) {
  state = _state;
  isSelected = false;
  isFlag = false;
  row = _row;
  col = _col;
}

int Dot::getNumMinesAround() {
  return numMinesAround;
}

int Dot::getState() {
  return state;
}

bool Dot::getIsSelected() {
  return isSelected;
}

bool Dot::getIsFlag() {
  return isFlag;
}

int Dot::getRow() {
  return row;
}

int Dot::getCol() {
  return col;
}

void Dot::setNumMinesAround(Dot (*arrays)[COL]) {
  if (getState()!=MINE) {
    int result = 0;
    for (int i=-1; i<=1; i++) {
      for (int j=-1; j<=1; j++) {
        if (arrays[row+i][col+j].getState() == MINE) {
          result++;
        }
      }
    }
    numMinesAround = result;
  }
  else {
    numMinesAround = -1;
  }
}

void Dot::setMine() {
  state = MINE;
}

void Dot::setSelect() {
  isSelected = !isSelected;
}

void Dot::setFlag() {
  if (getIsSelected()) {
    isFlag = !isFlag;
  }
}

void Dot::dig() {
  if (getIsSelected()) {
    if (state==MINE) {
      //return 1;
    }
    else if (state==CLOSE) {
      state=OPEN;
      //return 0;
    }
  }  
}

int findSelectedCoordinate(Dot (*arrays)[COL], int hilo) {
  for (int i=0; i<ROW; i++) {
    for (int j=0; j<COL; j++) {
      if (arrays[i][j].getIsSelected()) {
        if (hilo==ROW) return i;
        else if (hilo==COL) return j;
      }
    }
  }
  return -1;
}