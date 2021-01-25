#ifndef AGENT_H
#define AGENT_H

#include <ostream>
#include <iostream>
#include "Location.h"
#include "World.h"
#include "State.h"
#include <math.h>       /* pow *//* bow chika wowawow! */ /* groovy funky baby! */


class Agent
{
private:


//so one can access the data in Mouse since it inherates from Agent 007 
protected:
  int r;
  int c;
  State* states;
  World* world;
  int maxRow;
  int maxCol;

  
  int agent; // 0 for mouse, 1 for cat


public:
  Agent();
  Agent(int agent, int r, int c, int maxRows, int maxColumns, World* world);
  ~Agent();
  /////////////
  void init();
  void printCoordinates();
  void setCoordinates(int r, int c);
  void move(char direction);
  void move(char direction, Location* curLoc);
  int getR();
  int getC();
  void printInteralStates();
  int getStateNumber(int otherR, int otherC);
  void learnTransitions( World* world);
  State* getInternalState(int otherR, int otherC);
  char getBestMove(int otherR, int otherC, int mode, double eps);
  void deleteStates();
};


#endif