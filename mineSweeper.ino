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
const int NUM_PIN_ONESIDE = 6;
const int CLOSE  = 0;
const int MINE   = 1;
const int OPEN   = 2;
const int SELECT = 3;
const int FLAG = 4;
bool isInitedField = false;
bool isGameOver = false;
AE7SEGGPIO ae7seg(SEG_LATCH, SEG_SDI, SEG_SCK);
Dot field[ROW][COL];
Dot clear[ROW][COL];
Dot failure[ROW][COL];
Dot high;
int count = 0;
void initField (Dot (*arrays)[COL]);
void dotMatrix (Dot (*arrays)[COL], int count);
void printField (Dot (*arrays)[COL]);
void buttonA (Dot (*arrays)[COL]);
void buttonB (Dot (*arrays)[COL]);
void buttonC (Dot (*arrays)[COL]);
int findSelectedCoordinate(Dot (*arrays)[COL], int hilo);
void seg(Dot (*arrays)[COL]);
bool isFinish (Dot (*arrays)[COL]);
void makeDisplay(Dot (*_clear)[COL], Dot (*_failure)[COL]);

void setup() {
  miss();
  Serial.begin(9600);
  pinMode(SPEAKER, OUTPUT);
  pinMode(BUTTON_A, INPUT);
  pinMode(BUTTON_B, INPUT);
  pinMode(BUTTON_C, INPUT);
  pinMode(VOLUME, INPUT);
  pinMode(SEG_LATCH, OUTPUT);
  pinMode(SEG_SDI, OUTPUT);
  pinMode(SEG_SCK, OUTPUT);
  for (int i=1; i<NUM_PIN_ONESIDE+1; i++) pinMode(MAT[i], OUTPUT);
  pinMode(REG_SER, OUTPUT);
  pinMode(REG_LATCH, OUTPUT);
  pinMode(REG_CLK, OUTPUT);
  for (int i=0; i<ROW; i++) {
    for (int j=0; j<COL; j++) {
     field[i][j] = Dot(i, j, CLOSE);
     clear[i][j] = Dot(i, j, CLOSE);
     failure[i][j] = Dot(i, j, CLOSE);
    }
  }
  makeDisplay(clear, failure);
  high = Dot(-1, -1, OPEN);
  field[2][3].setSelect();
  printField(field);
}

void loop() {
  if (isGameOver) {
    resetDotMatrix();
    dotMatrix(failure, count);
    ae7seg.beginWrite();
    ae7seg.writeNumber(8);
    ae7seg.endWrite();
  }
  else if (!isFinish(field)) {
    volume();
    buttonA(field);
    buttonB(field);
    buttonC(field);
    seg(field);
    resetDotMatrix();
    dotMatrix(field, count);
    noTone(SPEAKER); 
  }
  else if (isFinish(field)){
    resetDotMatrix();
    dotMatrix(clear, count);
    ae7seg.beginWrite();
    ae7seg.writeNumber(8);
    ae7seg.endWrite();
  }
  delayMicroseconds(50);
  count = (++count)%5;
}