#include "ae7seg.h"
uint8_t SPEAKER   =  2;
uint8_t VOLUME    = A2;
uint8_t BUTTON_A  = A3;
uint8_t BUTTON_B  = A4;
uint8_t BUTTON_C  = A5;
uint8_t SEG_LATCH = A1;
uint8_t SEG_SDI   =  3;
uint8_t SEG_SCK   =  4;
uint8_t REG_SER   = 13;
uint8_t REG_LATCH = 12;
uint8_t REG_CLK   = 11;
uint8_t MAT[] = {-1, 5, 6, 7, 8, 9, 10};
const int LED[5][7] = {
  {1,0,1,0,1,0,1},
  {0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1},
  {0,1,0,1,0,1,0},
  {1,0,1,0,1,0,1}
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
  dotMatrix(LED, count);
  delay(0);
  noTone(SPEAKER); 
  delayMicroseconds(50);
  count = (++count)%5;
}