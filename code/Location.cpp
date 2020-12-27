#include "header/Location.h"



Location::Location(/* args */)
{
  this->toLeft = false;
  this->toRight = false;
  this->toTop = false;
  this->toBottom = false;

  std::cout << "SHOULD NEVER PRINT THIS" << std::endl;
}

Location::Location(bool toLeft, bool toRight, bool toTop, bool toBottom)
{
  this->toLeft = toLeft;
  this->toRight = toRight;
  this->toTop = toTop;
  this->toBottom = toBottom;
  this->goal = false;
}

Location::~Location()
{
}

void Location::setPossDirect(bool toLeft, bool toRight, bool toTop, bool toBottom){
  this->toLeft = toLeft;
  this->toRight = toRight;
  this->toTop = toTop;
  this->toBottom = toBottom;
}


void Location::printPossDirect(){
  std::cout << "L" << toLeft << " R" << toRight << " T"<< toTop << " B" << toBottom << std::endl;
}

void Location::setGoal(bool goal){
  this->goal = goal;
}

bool Location::isGoal(){
  return goal;
}


// is the direction possible, 
// chars to use 'l , r, t, d'
bool Location::isDirecPoss(char direction){
  bool isPoss;
  
  std::cout << "bla bla " << std::endl;

  switch (direction)
  {
  case 'l': // left
    isPoss = toLeft;
    break;
  case 'r': // right
    isPoss = toRight;
    break;
  case 't': // up
    isPoss = toTop;
    break;
  case 'd': // down
    isPoss = toBottom;
    break;
  default:
    std::cout << "Wrong char please enter 'l , r, t, d'. Enterd char was " << direction << std::endl; 
  }
  return isPoss;
}
