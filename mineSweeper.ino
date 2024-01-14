#include "ae7seg.h"
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
const int field[ROW][COL] = {
  {0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0},
  {0,0,0,5,0,0,0},
  {0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0}
};
int count = 0;

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
  initField(field);
}

void loop() {
  volume();
  delay(0);
  buttonA();
  delay(0);
  buttonB();
  delay(0);
  buttonC();
  delay(0);
  seg(ctoi('F'));
  delay(0);
  dotMatrix(field, count);
  delay(0);
  noTone(SPEAKER); 
  delayMicroseconds(50);
  count = (++count)%5;
}