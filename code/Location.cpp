#include "header/Location.h"



Location::Location(/* args */)
{
  this->toLeft = true;
  this->toRight = true;
  this->toTop = true;
  this->toBottom = true;
}

Location::Location(bool toLeft, bool toRight, bool toTop, bool toBottom)
{
  this->toLeft = toLeft;
  this->toRight = toRight;
  this->toTop = toTop;
  this->toBottom = toBottom;
  this->isGoal = false;
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

void Location::setNeighbours(Location *leftNeighbour, Location *rightNeighbour, Location *topNeighbour, Location *bottomNeighbour){
  this->leftNeighbour = leftNeighbour;
  this->rightNeighbour = rightNeighbour;
  this->topNeighbour = topNeighbour;
  this->bottomNeighbour = bottomNeighbour;
}


void Location::printPossDirect(){
  std::cout << "L" << toLeft << " R" << toRight << " T"<< toTop << " B" << toBottom << std::endl;
}

void Location::setGoal(bool isGoal ){
  this->isGoal = isGoal;
}

Location * Location::getNeighbour(char direction){
  Location *newLoc;
  switch (direction)
    {
    case 'l':
      toLeft = toLeft ? leftNeighbour: NULL;
      break;
    case 'r':
      newLoc = toRight ? rightNeighbour: NULL;
      break;

    case 't':
      newLoc = toTop ? topNeighbour: NULL;
      break;

    case 'b':
      newLoc = toBottom ? bottomNeighbour: NULL;
      break;
    
    default:
      std::cout << "Default in Location and the char was " << direction << std::endl;
    }
  return newLoc; 
}
