#ifndef ROWCOL_H
#define ROWCOL_H

class RowCol
{
private:
  int row;
  int col;
public:
  RowCol(/* args */);
  RowCol(int row, int col);
  ~RowCol();
  bool samePos(RowCol other);
  int getRow();
  int getCol();
 
};

#endif
