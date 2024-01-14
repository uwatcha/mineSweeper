class Dot
{
public:
  Dot(int row, int col);
  int getNumMinesAround(Dot (*arrays)[COL]);
  int getState();
  void setFlag();
  int dig();

private:
  int state;
  bool isSelected;
  bool isFlag;
  int row;
  int col;
  int numMinesAround;
};