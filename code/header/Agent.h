#ifndef AGENT_H
#define AGENT_H

#include <ostream>
#include <iostream>



class Agent
{
private:
  int x;
  int y;
public:
  Agent();
  Agent(int x, int y);
  ~Agent();
  void printCoordinates();
  void setCoordinates(int x, int y);

};


#endif