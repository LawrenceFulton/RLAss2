#ifndef WORLD_H
#define WORLD_H

#include "Location.h"

class World
{
private:
  /* data */
  int sizeX;
  int sizeY;
  Location **locations;


public:
  World(/* args */);
  World(int sizeX, int sizeY);
  ~World();
  //////////////////
  void printAllPossDirect();
};


#endif
