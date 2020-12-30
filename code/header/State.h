#ifndef STATE_H
#define STATE_H

#include "RowCol.h"
#include <iostream>
#include <ostream>

class State
{
private:
  /* data */
  RowCol *mouseRowCal;

  // For the beginning just working with one cat, would have to make an array of catX and catY if having
  // more that one cat 
  // int nCat; 
  RowCol *catRowCal;

  double Q;

public:
  State(/* args */);
  State(int mouseX, int mouseY, int catX, int catY);
  void printState();
  void setValues(int mouseX, int mouseY, int catX, int catY, int Q);

  ~State();
};



#endif