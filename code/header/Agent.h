#ifndef AGENT_H
#define AGENT_H

#include <ostream>
#include <iostream>
#include "Location.h"
#include "World.h"
#include "State.h"
#include <math.h>       /* pow */
#include "World.h"


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
  Agent(int r, int c, int maxRows, int maxColumns);
  ~Agent();
  void printCoordinates();
  void setCoordinates(int r, int c);
  void move(char direction, Location* curLoc);
  int getR();
  int getC();
  void printInteralStates();
  void learnTransitions(World* world);

};


#endif