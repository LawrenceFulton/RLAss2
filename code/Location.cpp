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
void Location::printPossDirect(){
  std::cout << "L" << toLeft << " R" << toRight << " T"<< toTop << " B" << toBottom << std::endl;
}

void Location::setGoal(bool isGoal ){
  this->isGoal = isGoal;
}
