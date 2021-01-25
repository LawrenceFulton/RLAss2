#ifndef STATE_H
#define STATE_H

#include "Location.h"
#include <iostream>
#include <ostream>
#include <float.h>
#include <stdlib.h>     /* srand, rand */


#define SINGLE 0
#define DOUBLE 1

#define EPS 0
#define UCB 1


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

  double toTop0;
  double toBottom0;
  double toLeft0;
  double toRight0;
  double toStay0;

  // Used in double q learning
  double toTop1;
  double toBottom1;
  double toLeft1;
  double toRight1;
  double toStay1;





  double r;

public:
  int id;
  State(/* args */);
  State(int mouseX, int mouseY, int catX, int catY);
  void printState();
  void setValues(int mouseX, int mouseY, int catX, int catY, double r);
  void setTransition(int specialCase, Location* loc);
  char argMaxMove(int mode);
  double getR();
  double maxValue();

  void setDirectionValue(int set, char direction, double newVal);
  double getDirectionValue(int set, char direction);
  ~State();
};



#endif