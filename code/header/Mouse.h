#ifndef MOUSE_H
#define MOUSE_H

#include "Agent.h"
#include "Location.h"
#include "World.h"

class Mouse: public Agent
{
private:
  int steps;

public:
  Mouse(/* args */);
  Mouse(int x, int y);
  Mouse(int x, int y, int maxRow, int maxCOl);
  char getBestMove(int cR, int cC, double eps);
  ~Mouse();
};



#endif