#ifndef MOUSE_H
#define MOUSE_H

#include "Agent.h"
#include "Location.h"
#include "World.h"

class Mouse: public Agent
{
private:
  int steps;
  int x;
  int y;
public:
  Mouse(/* args */);
  Mouse(int x, int y);
  ~Mouse();
};



#endif