#include "Dot.h"
const int NUM_MINE = 6;
const int NUM_DOT = 35;

void initField (Dot (*arrays)[COL]) {
  int _count=0;
  int i;
  int j;
  while(_count<NUM_MINE) {
    i = random(ROW);
    j = random(COL);
    if ((arrays[i][j].getState()!=MINE) && !arrays[i][j].getIsSelected()) {
      arrays[i][j].setMine();
      _count++;
    }
  }
  isInitedField = true;
}