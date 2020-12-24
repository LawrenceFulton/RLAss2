#include "header/World.h"
World::World(/* args */)
{
}

World::World(int sizeX, int sizeY){
  this->sizeX = sizeX;
  this->sizeY = sizeY;

  locations = new Location*[sizeX];
  for (size_t i = 0; i < sizeX; i++)
  {
    locations[i] = new Location[sizeY];
  }
}
void World::printAllPossDirect(){
  for (size_t x = 0; x < sizeX; x++)
  {
    for (size_t y = 0; y < sizeY; y++)
    {
      std::cout << "(" << x << "," << y << "): " ;
      locations[x][y].printPossDirect();
    }
    
  }
}


World::~World()
{ 
}
