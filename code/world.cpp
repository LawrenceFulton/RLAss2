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
  //Making the boarders of the world, no walls (for now)
  
  // top and bottom boarder of the world 
  for (size_t x = 0; x < sizeX; x++)
  { 
    locations[x][0].setPossDirect(true, true, true, false);
    locations[x][sizeY-1].setPossDirect(true,true, false, true);
  }

  // left and right boarder of the world 
  for (size_t y = 0; y < sizeY; y++)
  {
    locations[0][y].setPossDirect(false, true, true, true);
    locations[sizeX-1][y].setPossDirect(true,false,true,true);
  }

  //corner points

  locations[0][0].setPossDirect(0,1,1,0);
  locations[0][sizeY-1].setPossDirect(0,1,0,1);
  locations[sizeX-1][sizeY-1].setPossDirect(1,0,0,1);
  locations[sizeX-1][0].setPossDirect(1,0,1,0);
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
