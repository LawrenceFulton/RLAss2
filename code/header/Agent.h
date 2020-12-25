#ifndef AGENT_H
#define AGENT_H

#include <ostream>
#include <iostream>
#include "Location.h"


class Agent
{
private:
  int r;
  int c;
  Location *curLoc;

public:
  Agent();
  Agent(int r, int c);
  ~Agent();
  void printCoordinates();
  void setCoordinates(int r, int c);
  void setCurrentLoc(Location *curLoc);
  Location * getCurrentLoc();
  void move(char direction);

};


#endif