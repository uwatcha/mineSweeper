#include "Dot.h"
const int OFFSET = 55;
void seg(Dot (*arrays)[COL]) {
  int selectedRow = findSelectedCoordinate(arrays, ROW);
  int selectedCol = findSelectedCoordinate(arrays, COL);
  int n = 0;
  if (arrays[selectedRow][selectedCol].getIsFlag()) n=ctoi('F');
  else if (arrays[selectedRow][selectedCol].getState()==OPEN) n=arrays[selectedRow][selectedCol].getNumMinesAround();
  else if (arrays[selectedRow][selectedCol].getState()!=OPEN) n=ctoi('C');
  ae7seg.beginWrite();
  ae7seg.writeNumber(n);
  ae7seg.endWrite();
}

int ctoi(char c) {
  return c-OFFSET;
}