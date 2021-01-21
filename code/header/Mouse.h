#ifndef MOUSE_H
#define MOUSE_H

#include "Agent.h"
#include "Location.h"
#include "World.h"
class Cat;

#include <random>
#define MOUSE_ID 0



class Mouse: public Agent
{
private:
  int steps;
  Cat* cat;
  Agent as;

public:
  Mouse(/* args */);
  Mouse(int x, int y);
  Mouse(int x, int y, int maxRow, int maxCOl);
  ~Mouse();


  char getBestMove(int mode, double eps);
  State* getInternalState();
  void learnTransitions(World* world);
  void setCat(Cat* cat);
};



#endif