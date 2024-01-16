#include "Dot.h"
const int OFFSET = 55;
AE7SEGGPIO ae7seg(SEG_LATCH, SEG_SDI, SEG_SCK);
void seg(int n) {
  ae7seg.beginWrite();
  ae7seg.writeNumber(n);
  ae7seg.endWrite();
}

int ctoi(char c) {
  return c-OFFSET;
}