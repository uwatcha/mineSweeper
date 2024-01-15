#include "Arduino.h"
#include "Dot.h"
const int CLOSE  = 0;
const int MINE   = 1;
const int OPEN   = 2;

Dot::Dot() {}
Dot::Dot(int _row, int _col) {
  state = CLOSE;
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

void Dot::setOpen() {
  state = OPEN;
}

void Dot::setSelect() {
  isSelected = !isSelected;
}

void Dot::setFlag() {
  isFlag = !isFlag;
}

int Dot::dig() {
  if (state==MINE) {
    return 1;
  }
  else {
    state=OPEN;
    return 0;
  }
}