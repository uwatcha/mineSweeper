class Dot
{
public:
  Dot(int row, int col);
  int getState();
  bool getIsSelected();
  bool getIsFlag();
  int getRow();
  int getCol();
  int getNumMinesAround();
  
  void setSelect();
  void setFlag();
  void setNumMinesAround(Dot (*arrays)[COL]);
  int dig();

private:
  int state;
  bool isSelected;
  bool isFlag;
  int row;
  int col;
  int numMinesAround;
};