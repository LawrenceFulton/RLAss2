#include "header/Mouse.h"
#include "header/Cat.h"


Mouse::Mouse(){
  *this = Mouse(0,0);
};


Mouse::Mouse(int x, int y){
  setCoordinates(x,y);
  steps = 0;
}

Mouse::Mouse(int x,int y, int maxRow, int maxCol, World* world):Agent(MOUSE_ID, x, y, maxRow,maxCol, world){
  steps = 0;
}

char Mouse::getBestMove(int mode, double eps){
  return Agent::getBestMove(cat->getR(), cat->getC(),mode, eps);
}

State* Mouse::getInternalState(){
  return (Agent::getInternalState(cat->getR(), cat->getC()));
}



void Mouse::setCat(Cat* cat){
  this->cat = cat;
}


Mouse::~Mouse(){
  deleteStates();
}

