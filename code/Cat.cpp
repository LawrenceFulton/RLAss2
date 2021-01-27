#include "header/Cat.h"
#include "header/Mouse.h"

Cat::Cat(){};

Cat::Cat(int r, int c, int maxRow, int maxCol):Agent::Agent(CAT_ID, r,c,maxRow,maxCol){
  steps = 0;
} 
Cat::~Cat(){};


State* Cat::getInternalState(){
  return Agent::getInternalState(CAT_ID,mouse->getR(),mouse->getC());
}

char Cat::getBestMove(int mode, double eps){
  return Agent::getBestMove(CAT_ID,mouse->getR(),mouse->getC(),mode,eps);
}

void Cat::learnTransitions(World *world){
  Agent::learnTransitions(CAT_ID, world);
}

void Cat::setMouse(Mouse* mouse){
  this->mouse = mouse;
}

