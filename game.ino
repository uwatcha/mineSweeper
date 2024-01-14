const int CLOSE  = 0;
const int OPEN   = 1;
const int MINE   = 2;
const int FLAG_F = 3;
const int FLAG_M = 4;
const int SELECT = 5; 
const int TABLE[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

void initField (int (*arrays)[7]) {
  //最初に選択しているを乱数テーブルから除く
  int table[34];
  int selectedDot = getSelectedDot(arrays);
  for (int i=0, j=0; i<35; i++, j++) {
    if (i!=j || j!=selectedDot) {
      table[i] = j;
    }
    else {
      j++;
      Serial.println(i);
    }
  }
  //----------------------------------------
  for (int i=0; i<34; i++) {
    //Serial.println(table[i]);
  }
}

int getSelectedDot (int (*arrays)[7]) {
  for (int i=0; i<7; i++) {
    for (int j=0; j<7; j++) {
      if (arrays[i][j]==SELECT) {
        return i*10+j;
      }
    }
  }
  return -1;
}

int *selectValues (int *array, int num) {
  int result[num];
  int pointResult = 0;
  for (int i=0; i<num; i++) {
  }
}

int coordinateToNum (int coo) {
  int ten = coo/10;
  int one = coo%10;
  return 7*ten+one;
}