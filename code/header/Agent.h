#ifndef AGENT_H
#define AGENT_H

#include <ostream>
#include <iostream>
#include "Location.h"
#include "World.h"


class Agent
{
private:
  int r;
  int c;

public:

  Agent();
  Agent(int r, int c);
  ~Agent();
  void printCoordinates();
  void setCoordinates(int r, int c);
  void move(char direction, Location* curLoc);
  int getR();
  int getC();

  // World getWorld();
  // void setWorld(World world);
};


#endif