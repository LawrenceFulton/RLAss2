#include "main.h"


int main(int argc, char const *argv[])
{
  Cat *cat = new Cat(1,2,3);
  World *world = new World(3,3);
  cat->printCoordinates();
  world->printAllPossDirect();
  return 0;
}



