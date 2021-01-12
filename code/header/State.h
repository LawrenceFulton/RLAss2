#ifndef STATE_H
#define STATE_H

#include "RowCol.h"
#include "Location.h"
#include <iostream>
#include <ostream>
#include <float.h>
#include <stdlib.h>     /* srand, rand */

class State
{
private:
  /* data */
  RowCol *mouseRowCal;

  // For the beginning just working with one cat, would have to make an array of catX and catY if having
  // more that one cat 
  // int nCat; 
  RowCol *catRowCal;

  double toTop;
  double toBottom;
  double toLeft;
  double toRight;
  double r;

public:
  int id;
  State(/* args */);
  State(int mouseX, int mouseY, int catX, int catY);
  void printState();
  void setValues(int mouseX, int mouseY, int catX, int catY, double r);
  void setTransition(int specialCase, Location* loc);
  char getBestMove();
  double getR();
  double maxValue();

  void setDirectionValue(char direction, double newVal);
  double getDirectionValue(char direction);
  ~State();
};



#endif