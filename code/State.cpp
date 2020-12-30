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
            <<" and Q:" << Q <<std::endl;
}

void State::setValues(int mouseR, int mouseC, int catR, int catC, int Q){
  mouseRowCal = new RowCol(mouseR,mouseC);
  catRowCal = new RowCol(catR, catC);
  this->Q = Q;
}