#include "header/State.h"
State::State(/* args */)
{
}

State::State(int mouseR, int mouseC, int catR, int catC){
  setValues(mouseR, mouseC, catR, catC,0);
}


State::~State()
{
}

void State::printState(){
  std::cout << "Mouse:" << mouseRowCal->getRow() << ", " << mouseRowCal->getCol() 
            << "and Cat:"<< catRowCal->getRow() << ", " << catRowCal->getCol() 
            <<" and r:" << r << " and ID << " << id <<std::endl;
  std::cout << toLeft<< " " << toRight << " " << toTop << " " << toBottom << std::endl;
}

void State::setValues(int mouseR, int mouseC, int catR, int catC, int r){
  mouseRowCal = new RowCol(mouseR,mouseC);
  catRowCal = new RowCol(catR, catC);
  this->r = r;
}

void State::setTransition(Location* loc){


  // checks if the move is possible 
  bool left = loc->isDirecPoss('l');
  bool right = loc->isDirecPoss('r');
  bool top = loc->isDirecPoss('t');
  bool bottom = loc->isDirecPoss('d');

  // Creates, when possible a q value of between 0 and 1
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

  best = (toBottom > max) ? 'b' : best;
  max = (toBottom > max) ? toBottom : max;   

  std::cout << "Extra: " << toLeft<< " " << toRight << " " << toTop << " " << toBottom << " " << id << std::endl;
  

  return best;

}
