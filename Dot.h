#pragma once
//const int COL = 7;
class Dot
{
public:
  Dot();
  Dot(int _row, int _col, int _state);
  int getState();
  bool getIsSelected();
  bool getIsFlag();
  int getRow();
  int getCol();
  int getNumMinesAround();
  void printField (Dot (*arrays)[7]);
  
  void setSelect();
  void setFlag();
  void setNumMinesAround(Dot (*arrays)[7]);
  void setMine();
  void dig();
  //プロトタイプ宣言
  void initField(Dot (*arrays)[7]);
  int getSelectedDot (Dot (*arrays)[7]);
  int *selectValues (int *array, int num);
  int coordinateToNum (int coo);
  int numToCoordinate (int num);
  void dotMatrix (Dot (*arrays)[7], int count);
  int write (int pin, Dot dot, bool isAnode);
  void reg (int b);
  void buttonA (Dot *_selected);
  void buttonB (Dot *_selected);
  void buttonC (Dot *_selected);
  bool buttonIsON (uint8_t button);
  //--------------------------------------------

private:
  int state;
  bool isSelected;
  bool isFlag;
  int row;
  int col;
  int numMinesAround;
};