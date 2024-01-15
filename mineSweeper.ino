#include "ae7seg.h"
#include "Dot.h"
const uint8_t SPEAKER   =  2;
const uint8_t VOLUME    = A2;
const uint8_t BUTTON_A  = A3;
const uint8_t BUTTON_B  = A4;
const uint8_t BUTTON_C  = A5;
const uint8_t SEG_LATCH = A1;
const uint8_t SEG_SDI   =  3;
const uint8_t SEG_SCK   =  4;
const uint8_t REG_SER   = 13;
const uint8_t REG_LATCH = 12;
const uint8_t REG_CLK   = 11;
const uint8_t MAT[] = {-1, 5, 6, 7, 8, 9, 10};
const int ROW = 5;
const int COL = 7;
Dot field[ROW][COL];
Dot high = Dot(0, 0);
Dot low  = Dot(0, 0);
int count = 0;
void initField (Dot (*arrays)[COL]);
void dotMatrix (Dot (*arrays)[COL], int count);
int getSelectedDot (Dot (*arrays)[COL]);

void setup() {
  Serial.begin(9600);
  pinMode(SPEAKER, OUTPUT);
  pinMode(BUTTON_A, INPUT);
  pinMode(BUTTON_B, INPUT);
  pinMode(BUTTON_C, INPUT);
  pinMode(VOLUME, INPUT);
  pinMode(SEG_LATCH, OUTPUT);
  pinMode(SEG_SDI, OUTPUT);
  pinMode(SEG_SCK, OUTPUT);
  initDotMatrix();

  for (int i=0; i<ROW; i++) {
    for (int j=0; j<COL; j++) {
     field[i][j] = Dot(i, j);
    }
  }
  high.setOpen();
  low.setOpen();
  initField(field);
}

void loop() {
  volume();
  buttonA();
  buttonB();
  buttonC();
  seg(ctoi('F'));
  dotMatrix(field, count);
  noTone(SPEAKER); 
  delayMicroseconds(50);
  count = (++count)%5;
}