#ifndef WORLD_H
#define WORLD_H

#include "Location.h"
#include <iostream>
#include <ostream> 


class World
{
private:
  /* data */
  int rows;
  int columns;
  Location **locations;
  Location goal;
  int id; // for debug mostly ( ͡ᵔ ͜ʖ ͡ᵔ )



  /*  functions */
  void setGoal(int row, int column);



public:
  World(/* args */);
  World(int rows, int columns);
  ~World();
  //////////////////
  void printAllPossDirect();
  Location * getLocation(int row, int column);
  int getMaxRows();
  int getMaxColumns();
  int getId();
  void setId(int id);

};


#endif
