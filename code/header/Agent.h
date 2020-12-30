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
  int r;
  int c;

  int maxRow;
  int maxCol;
  State* states;



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

};


#endif