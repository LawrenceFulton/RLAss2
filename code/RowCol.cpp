#include "header/RowCol.h"
RowCol::RowCol(/* args */)
{
}

RowCol::RowCol(int row, int col){
  this->row = row;
  this->col = col;
}

RowCol::~RowCol()
{
}

int RowCol::getRow(){
  return row;
}

int RowCol::getCol(){
  return col;
}



bool RowCol::samePos(RowCol other){
  if (this->getRow() == other.getRow() && this->getCol() == other.getCol());
  {
    return true;
  }
  return false;
}
