const int DIRECT[] = {1, 2, 3, 4, 5, 6};
const int REGISTER[] = {7, 8, 9, 10, 11, 12}; //bに登録する
const int ANODE[] = {1, 3, 10, 7, 8};
const int CATHODE[] = {12, 11, 2, 9, 4, 5, 6}; //0で通電
const int BASE_BIT = B00000000;
const int REGISTER_PIN_HEAD = 7;
const int NUM_PIN_ONESIDE = 6;

void resetDotMatrix () {
  int b = BASE_BIT;
  for (int i=0; i<ROW; i++) {
    b |= write(ANODE[i], LOW);
    for (int j=0; j<COL; j++) {
      b |= write(CATHODE[j], HIGH);
    }
  }
  reg(b);
}
void dotMatrix (int (*arrays)[COL], int count) {
  resetDotMatrix();
  int b = BASE_BIT;
  b |= write(ANODE[count], 1);
  for (int j=0; j<COL; j++) {
    b |= write(CATHODE[j], !arrays[count][j]);
  }
  reg(b); 
}

int write (int n, bool isHigh) {
  int result;
  if (isValue(DIRECT, n)) {
    digitalWrite(MAT[n], isHigh);
    return 0;
  }
  else if (isValue(REGISTER, n)) {
    if (isHigh) result = B00100000;
    else      result = B00000000;
    result = result >> (n-REGISTER_PIN_HEAD);
    return result;
  }
}

void reg (int b) {
  digitalWrite(REG_LATCH, LOW);
  shiftOut(REG_SER, REG_CLK, LSBFIRST, b);
  digitalWrite(REG_LATCH, HIGH);
}

bool isValue (int *array, int value) {
  int size;
  if (array==DIRECT || array==REGISTER) size = NUM_PIN_ONESIDE;
  else if (array==ANODE) size = ROW;
  else if (array==CATHODE) size = COL;
  for (int i=0; i<size; i++) {
    if (array[i]==value) {
      return true;
    }
  }
  return false;
}

void initDotMatrix () {
  for (int i=1; i<NUM_PIN_ONESIDE+1; i++) pinMode(MAT[i], OUTPUT);
  pinMode(REG_SER, OUTPUT);
  pinMode(REG_LATCH, OUTPUT);
  pinMode(REG_CLK, OUTPUT);
  digitalWrite(MAT[1], LOW);
  digitalWrite(MAT[3], LOW);
  digitalWrite(MAT[2], HIGH);
  digitalWrite(MAT[4], HIGH);
  digitalWrite(MAT[5], HIGH);
  digitalWrite(MAT[6], HIGH);
  reg(B00110100);
}