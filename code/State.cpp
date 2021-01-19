#include "header/State.h"
State::State(/* args */)
{
}

State::State(int mouseR, int mouseC, int catR, int catC){
  setValues(mouseR, mouseC, catR, catC, 0);
}


State::~State()
{
}

void State::printState(){
  std::cout << "Own:" << ownRowCol->getRow() << ", " << ownRowCol->getCol() 
            << "and Other:"<< otherRowCol->getRow() << ", " << otherRowCol->getCol() 
            <<" and r:" << r << " and ID << " << id <<std::endl;
  std::cout << toLeft<< " " << toRight << " " << toTop << " " << toBottom << std::endl;
}

void State::setValues(int ownR, int ownC, int otherR, int otherC, double r){
  ownRowCol = new RowCol(ownR,ownC);
  otherRowCol = new RowCol(otherR, otherC);
  this->r = r;
}

void State::setTransition(int specialCase, Location* loc){


  // checks if the move is possible 
  bool left = loc->isDirecPoss('l');
  bool right = loc->isDirecPoss('r');
  bool top = loc->isDirecPoss('t');
  bool bottom = loc->isDirecPoss('d');


  // the special cases are happening so that the cat doesn't
  // camp the goal state
  if (specialCase == 1)
  {
    right = false;
  }else if (specialCase == 2)
  {
    bottom = false;
  }

  // Creates, when possible a q value of between 0 and 1 else -DBL_MAX
  toLeft = left ? double(rand())/RAND_MAX :  -DBL_MAX;
  toRight = right ? double(rand())/RAND_MAX : -DBL_MAX;
  toTop = top ? double(rand())/RAND_MAX : -DBL_MAX;
  toBottom = bottom ? double(rand())/RAND_MAX : -DBL_MAX; 
}

char State::getBestMove(){
  double max = toLeft;
  char best = 'l'; 
  
  best = (toRight > max) ? 'r' : best;
  max = (toRight > max) ? toRight : max;

  best = (toTop > max) ? 't' : best;
  max = (toTop > max) ? toTop : max;

  best = (toBottom > max) ? 'd' : best;
  max = (toBottom > max) ? toBottom : max;   

  return best;
}

double State::getR(){
  return r;
}

double State::maxValue(){
  double max = toLeft;
  
  max = (toRight > max) ? toRight : max;
  max = (toTop > max) ? toTop : max;
  max = (toBottom > max) ? toBottom : max; 
  return max; 
}



void State::setDirectionValue(char direction, double newVal){
  switch (direction)
  {
  case 'l': // left
    toLeft = newVal;
    break;
  case 'r': // right
    toRight = newVal;
    break;
  case 't': // up
    toTop = newVal;
    break;
  case 'd': // down
    toBottom = newVal;
    break;
  default:
    std::cout << "There has been an error, the direction cant be " << direction << std::endl;
  }     
}


double State::getDirectionValue(char direction){
  
  double returnValue;
  switch (direction)
  {
  case 'l': // left
    returnValue = toLeft;
    break;
  case 'r': // right
    returnValue = toRight;
    break;
  case 't': // up
    returnValue = toTop;
    break;
  case 'd': // down
    returnValue = toBottom;
    break;
  } 
  return returnValue;
}
