#ifndef MOUSE_H
#define MOUSE_H

#include "Agent.h"
#include "Location.h"
#include "World.h"
#include <random>


class Mouse: public Agent
{
private:
  int steps;

public:
  Mouse(/* args */);
  Mouse(int x, int y);
  Mouse(int x, int y, int maxRow, int maxCOl);
  ~Mouse();


  char getBestMove(int cR, int cC, double eps);
  State* getInternalState(int cR, int cC);

};



#endif