#ifndef CAT_H
#define CAT_H

#include "Agent.h"
#include "Location.h"
#include "World.h"
#include "Mouse.h"


#include <random>
#define CAT_ID 1 



class Cat: public Agent
{
private:
  Mouse* mouse;
  int steps;

public:
  Cat();
  Cat(int r, int c, int maxRow, int maxCol);
  ~Cat();

  char getBestMove(double eps);
  State* getInternalState();
  void learnTransitions(World* world);
  void setMouse(Mouse* mouse);
};

#endif