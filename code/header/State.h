#ifndef STATE_H
#define STATE_H

#include "Location.h"
#include <iostream>
#include <ostream>
#include <float.h>
#include <stdlib.h>     /* srand, rand */


// Each agent has an array of states of all possible combinations of the agent himselves
// and the other agent. The state incoopeates the possible moves and if there is a reward
// at that state.

class State
{
private:
  /* data */

  int ownR;
  int ownC;

  int otherR;
  int otherC;

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