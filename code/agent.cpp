#include "header/Agent.h"

Agent::Agent(){};

Agent::Agent(int r, int c){
  this->r = r;
  this->c = c;
}
Agent::~Agent(){};

void Agent::printCoordinates(){
  std::cout << "(" << r << "," << c << ")" <<std::endl;
}

void Agent::setCoordinates(int r, int c){
  this->r = r;
  this->c = c;
}

void Agent::setCurrentLoc(Location *curLoc){
  this->curLoc = curLoc;
}

Location * Agent::getCurrentLoc(){
  return curLoc;
}

void Agent::move(char direction){
  // curLoc = curLoc->getNeighbour(direction);

  Location *interLoc = curLoc->getNeighbour(direction); // intermediate Location, has to still be checked if thats a possible move
  curLoc->printPossDirect();
  if (interLoc != NULL)
  {
  switch (direction)
    {
    case 'l': // left
      c--;
      break;
    case 'r': // right
      c++;
      break;
    case 't': // up
      r--;
      break;
    case 'd': // down
      r++;
      break;
    }
    curLoc = interLoc;
  }else
  {
    std::cout << "illegal move 8)" << std::endl;
  }
}


