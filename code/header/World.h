#ifndef WORLD_H
#define WORLD_H

#include "Location.h"

class World
{
private:
  /* data */
  int rows;
  int columns;
  Location **locations;
  Location goal;

  /*  functions */
  void setGoal(int row, int coloumn);



public:
  World(/* args */);
  World(int rows, int coloumns);
  ~World();
  //////////////////
  void printAllPossDirect();
  Location * getLocation(int row, int coloumn);
};


#endif
