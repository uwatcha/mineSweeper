const int CLOSE  = 0;
const int OPEN   = 1;
const int MINE   = 2;
const int FLAG_F = 3;
const int FLAG_M = 4;
const int SELECT = 5; 

const int NUM_MINE = 6;
const int NUM_DOT = 35;

void initField (int (*arrays)[7]) {
  //最初に選択しているを乱数テーブルから除く
  int table[NUM_DOT-1];
  int selectedDot = coordinateToNum(getSelectedDot(arrays));
  for (int i=0, j=0; i<NUM_DOT; i++, j++) {
    if (i!=j || selectedDot!=j) {
      table[i] = numToCoordinate(j);
    }
    else {
      i--;
    }
  }
  //----------------------------------------
  //地雷を埋めるドットを決定
  int *mines = selectValues(table, NUM_MINE);
  //----------------------------------------
  for (int i=0; i<NUM_MINE; i++) {
    arrays[mines[i]/10][mines[i]%10] = MINE;
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
  srand(static_cast<unsigned>(millis()));
  int *result;
  result = new int[num];
  bool isDuplicate = false;
  for (int i=0; i<num; i++) {
    int candidate = array[random(34)];
    for (int j=0; j<i; j++) {
      if (candidate==result[j]) {
        isDuplicate = true;
        break;
      }
    }
    if (!isDuplicate) {
      result[i] = candidate;
    }
    else {
      i--;
      isDuplicate = false;
    }
  }
  return result;
}

int coordinateToNum (int coo) {
  int ten = coo/10;
  int one = coo%10;
  return 7*ten+one;
}
int numToCoordinate (int num) {
  int ten = num/7;
  int one = num%7;
  return 10*ten+one;
}