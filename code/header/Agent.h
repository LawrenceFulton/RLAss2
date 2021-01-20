#ifndef AGENT_H
#define AGENT_H

#include <ostream>
#include <iostream>
#include "Location.h"
#include "World.h"
#include "State.h"
#include <math.h>       /* pow */


class Agent
{
private:


//so one can access the data in Mouse since it inherates from Agent 007 
protected:
  int r;
  int c;
  State* states;
  int maxRow;
  int maxCol;  


public:
  Agent();
  Agent(int agent, int r, int c, int maxRows, int maxColumns);
  ~Agent();
  void printCoordinates();
  void setCoordinates(int r, int c);
  void move(char direction);
  void move(char direction, Location* curLoc);
  int getR();
  int getC();
  void printInteralStates();
  int getStateNumber(int agent, int otherR, int otherC);
  void learnTransitions(int agent, World* world);
  State* getInternalState(int agent, int otherR, int otherC);
  char getBestMove(int agent, int otherR, int otherC, double eps);
};


#endif