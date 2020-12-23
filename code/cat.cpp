#include "header/Cat.h"

Cat::Cat(){};

Cat::Cat(int x, int y, int z){
  Agent::setCoordinates(x,y);
  this->z = z;
} 
Cat::~Cat(){};


void Cat::printCoordinates(){
  std::cout << z << std::endl;
  Agent::printCoordinates();
}
