#include "header/Cat.h"
#include "header/Mouse.h"

Cat::Cat(){};

Cat::Cat(int r, int c, int maxRow, int maxCol):Agent::Agent(CAT_ID, r,c,maxRow,maxCol){
  steps = 0;
} 
Cat::~Cat(){
  deleteStates();
};


State* Cat::getInternalState(){
  return Agent::getInternalState(mouse->getR(),mouse->getC());
}

char Cat::getBestMove(int mode, double eps){
  return Agent::getBestMove(mouse->getR(),mouse->getC(),mode,eps);
}

void Cat::setMouse(Mouse* mouse){
  this->mouse = mouse;
}

