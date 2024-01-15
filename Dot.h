#pragma once
//const int COL = 7;
class Dot
{
public:
  Dot();
  Dot(int row, int col);
  int getState();
  bool getIsSelected();
  bool getIsFlag();
  int getRow();
  int getCol();
  int getNumMinesAround();
  
  void setSelect();
  void setFlag();
  void setNumMinesAround(Dot (*arrays)[7]);
  void setOpen();
  void setMine();
  int dig();
  void initField(Dot (*arrays)[7]);
  int getSelectedDot (Dot (*arrays)[7]);
  int *selectValues (int *array, int num);
  int coordinateToNum (int coo);
  int numToCoordinate (int num);

private:
  int state;
  bool isSelected;
  bool isFlag;
  int row;
  int col;
  int numMinesAround;
};