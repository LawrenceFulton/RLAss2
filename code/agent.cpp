#include "header/Agent.h"

Agent::Agent(){};

Agent::Agent(int r, int c ){
  this->r = r;
  this->c = c;
  // world = world1;
}

void Agent::printCoordinates(){
  std::cout << "(" << r << "," << c << ")" <<std::endl;
}

void Agent::setCoordinates(int r, int c){
  this->r = r;
  this->c = c;
}

// World Agent::getWorld(){
//   return world;
// }

// void Agent::setWorld(World world){
//   this->world = world;
// }


// moves the agent into any of the four directions
// chars to use for direction 'l , r, t, d'
void Agent::move(char direction, Location* curLoc){
  if ((curLoc->isDirecPoss(direction)))
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
  }
}

// gets the row
int Agent::getR(){
  return r;
}

// gets the coloum 
int Agent::getC(){
  return c;
}




Agent::~Agent(){};
