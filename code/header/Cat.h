#ifndef CAT_H
#define CAT_H
#include "Agent.h"
#include <iostream>
#include <ostream> 

class Cat: public Agent
{

private:
  int z;
public:
  Cat();
  Cat(int x, int y, int z);
  ~Cat();
  void printCoordinates();
};



#endif