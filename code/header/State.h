#ifndef STATE_H
#define STATE_H

#include "Location.h"
#include <iostream>
#include <ostream>
#include <float.h>
#include <stdlib.h>     /* srand, rand */

class State
{
private:
  /* data */


  int ownR;
  int ownC;

  int otherR;
  int otherC;

  // RowCol *ownRowCol;
  // RowCol *otherRowCol;

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