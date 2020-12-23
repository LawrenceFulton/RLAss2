#include "header/Cat.h"

Cat::Cat(){};

Cat::Cat(int x, int y, int z){
  Agent(x,y);
  this->z = z;
} 
Cat::~Cat(){};


void Cat::printCoordinates(){
  std::cout << z << std::endl;

}
