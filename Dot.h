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
  bool dig();
  void setOpen();
  //プロトタイプ宣言
  void initField(Dot (*arrays)[7]);
  void dotMatrix (Dot (*arrays)[7], int count);
  int write (int pin, Dot dot, bool isAnode);
  void reg (int b);
  void buttonA (Dot (*arrays)[7]);
  void buttonB (Dot (*arrays)[7]);
  void buttonC (Dot (*arrays)[7]);
  bool buttonIsON (uint8_t button);
  int  findSelectedCoordinate(Dot (*arrays)[7], int hilo);
  void seg(Dot (*arrays)[7]);
  bool isFinish (Dot (*arrays)[7]);
  void makeDisplay(Dot (*_clear)[7], Dot (*_failure)[7]);
  //--------------------------------------------

private:
  int state;
  bool isSelected;
  bool isFlag;
  int row;
  int col;
  int numMinesAround;
};