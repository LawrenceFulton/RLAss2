#include "header/Cat.h"

Cat::Cat(){};

Cat::Cat(int r, int c, int maxRow, int maxCol):Agent::Agent(r,c,maxRow,maxCol){
  steps = 0;
} 
Cat::~Cat(){};




State* Cat::getInternalState(int mR, int mC){
  return(Agent::getInternalState(1,mR,mC));
}


void Cat::printCoordinates(){
  Agent::printCoordinates();
}
