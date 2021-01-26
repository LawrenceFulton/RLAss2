#include "header/Mouse.h"
#include "header/Cat.h"


Mouse::Mouse(){
  *this = Mouse(0,0);
};


Mouse::Mouse(int x, int y){
  setCoordinates(x,y);
  steps = 0;
}

Mouse::Mouse(int x,int y, int maxRow, int maxCol):Agent(MOUSE_ID, x, y, maxRow,maxCol){
  steps = 0;
}

char Mouse::getBestMove(int mode, double eps){
  return Agent::getBestMove(MOUSE_ID,cat->getR(), cat->getC(),mode, eps);
}

State* Mouse::getInternalState(){
  return (Agent::getInternalState(MOUSE_ID,cat->getR(), cat->getC()));
}


void Mouse::learnTransitions(World* world){
  Agent::learnTransitions(MOUSE_ID, world);
}

void Mouse::setCat(Cat* cat){
  this->cat = cat;
}


Mouse::~Mouse(){}

