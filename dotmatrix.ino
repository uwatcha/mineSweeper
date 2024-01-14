const int DIRECT[] = {1, 2, 3, 4, 5, 6};
const int REGISTER[] = {7, 8, 9, 10, 11, 12}; //bに登録する
const int ANODE[] = {1, 3, 10, 7, 8};
const int CATHODE[] = {12, 11, 2, 9, 4, 5, 6}; //0で通電

void resetDotMatrix () {
  int b = B00000000;
  for (int i=0; i<5; i++) {
    b |= write(ANODE[i], 0);
    for (int j=0; j<7; j++) {
      b |= write(CATHODE[j], 1);
    }
  }
  reg(b);
}
void dotMatrix (int (*arrays)[7], int count) {
  resetDotMatrix();
  int b = B00000000;
  b |= write(ANODE[count], 1);
  for (int j=0; j<7; j++) {
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
    result = result >> (n-7);
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
  if (array==DIRECT || array==REGISTER) size = 6;
  else if (array==ANODE) size = 5;
  else if (array==CATHODE) size = 7;
  for (int i=0; i<size; i++) {
    if (array[i]==value) {
      return true;
    }
  }
  return false;
}

void initDotMatrix () {
  for (int i=1; i<7; i++) pinMode(MAT[i], OUTPUT);
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