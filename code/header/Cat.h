#ifndef CAT_H
#define CAT_H

#include "Agent.h"
#include "Location.h"
#include "World.h"


#include <random>
#define CAT_ID 1 


class Mouse;

class Cat: public Agent
{
private:
  Mouse* mouse;
  int steps;

public:
  Cat();
  Cat(int r, int c, int maxRow, int maxCol, World* world);
  ~Cat();

  char getBestMove(int mode, double eps);
  State* getInternalState();
  void setMouse(Mouse* mouse);
};

#endif