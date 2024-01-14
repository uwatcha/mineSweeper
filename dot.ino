#include "Arduino.h"
#include "Dot.h"
const int CLOSE  = 0;
const int MINE   = 1;
const int OPEN   = 2;

Dot::Dot(int _row, int _col) {
  state = CLOSE;
  isSelected = false;
  isFlag = false;
  row = _row;
  col = _col;
}

int Dot::getNumMinesAround() {
  return this->numMinesAround;
}

int Dot::getState() {
  return this->state;
}

bool Dot::getIsSelected() {
  return this->isSelected;
}

bool Dot::getIsFlag() {
  return this->isFlag;
}

void Dot::setNumMinesAround(Dot (*arrays)[COL]) {
  if (this->getState()!=MINE) {
    int result = 0;
    for (int i=-1; i<=1; i++) {
      for (int j=-1; j<=1; j++) {
        if (arrays[row+i][col+j].getState() == MINE) {
          result++;
        }
      }
    }
    this->numMinesAround = result;
  }
  else {
    this->numMinesAround = -1;
  }
}

void Dot::setSelect() {
  this->isSelected = !this->isSelected;
}

void Dot::setFlag() {
  this->isFlag = !this->isFlag;
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