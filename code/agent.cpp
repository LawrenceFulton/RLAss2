#include "header/Agent.h"

Agent::Agent(){};

Agent::Agent(int x, int y){
  this->x = x;
  this->y = y;
}
Agent::~Agent(){};

void Agent::printCoordinates(){
  std::cout << "(" << x << "," << y << ")" <<std::endl;
}

void Agent::setCoordinates(int x, int y){
  this->x = x;
  this->y = y;
}
