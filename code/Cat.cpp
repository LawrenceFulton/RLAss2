#include "header/Cat.h"

Cat::Cat(){};

Cat::Cat(int r, int c, int maxRow, int maxCol):Agent::Agent(r,c,maxRow,maxCol){
  steps = 0;
} 
Cat::~Cat(){};


State* Cat::getInternalState(){
  return Agent::getInternalState(CAT_ID,mouse->getR(),mouse->getC());
}

char Cat::getBestMove(double eps){
  return Agent::getBestMove(CAT_ID,mouse->getR(),mouse->getC(),eps);
}

void Cat::learnTransitions(World *world){
  Agent::learnTransitions(CAT_ID, world);
}

void Cat::setMouse(Mouse* mouse){
  this->mouse = mouse;
}

