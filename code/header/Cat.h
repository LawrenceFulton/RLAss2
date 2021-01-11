#ifndef CAT_H
#define CAT_H

#include "Agent.h"
#include "Location.h"
#include "World.h"

#include <iostream>
#include <ostream>
#include <random>

class Cat: public Agent
{
private:
  int steps;
public:
  Cat();
  Cat(int r, int c, int maxRow, int maxCol);
  ~Cat();

  char getBestMove(int mR, int mC, double eps);

  
  State* getInternalState(int mC, int mR);
  void printCoordinates();
};

#endif