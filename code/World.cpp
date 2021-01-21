#include "header/World.h"
World::World(/* args */)
{
  *this = World(3,3); // 3,3
}

World::World(int rows, int columns){
  this->rows = rows;
  this->columns = columns;


  // Initialisation of the 2d Array. These are empty "Location" which still need to be filled with information
  locations = new Location*[rows];
  for (size_t i = 0; i < rows; ++i)
  {
    locations[i] = new Location[columns];
  }
  //Making the borders of the world, no walls (for now)


  int counter = 0;

  for (size_t r = 0; r < rows; r++)
  {
    for (size_t c = 0; c < columns; c++)
    {
      locations[r][c].id = counter;
      std::cout << counter << ": " << r << c  << " and rows and colums are " << rows << ", "  << columns <<std::endl;
      counter ++;

      if (r == 0) // top row 
      {
        if (c == 0) // top left corner 
        {
          locations[r][c].setPossDirect(0,1,0,1);
        }else if(c == columns-1){ // top right corner
          locations[r][c].setPossDirect(1,0,0,1);
        }else // top row w/o corners 
        {
          locations[r][c].setPossDirect(1,1,0,1);
        }
      } else if(r == rows-1) // bottom row
      {
        if (c == 0) // bottom left corner 
        {
          locations[r][c].setPossDirect(0,1,1,0);
        }else if(c == columns-1){ // bottom right corner
          locations[r][c].setPossDirect(1,0,1,0);
        }else // bottom row w/o corners 
        {
          locations[r][c].setPossDirect(1,1,1,0);
        }
      }else
      {
        if (c == 0) // left row 
        {
          locations[r][c].setPossDirect(0,1,1,1);
        }else if(c == columns-1){ // right row
          locations[r][c].setPossDirect(1,0,1,1);
        }else // center 
        {
          locations[r][c].setPossDirect(1,1,1,1);
        }
      }
    }
    
  }
  // add the goal state.
  setGoal(rows-1, columns-1);
}


void World::printAllPossDirect(){

  // std::cout << "sizes " << sizeX << sizeY << std::endl;
  for (size_t x = 0; x < rows; x++)
  {
    for (size_t y = 0; y < columns; y++)
    {
      std::cout << "(" << x << "," << y << "): " ;
      locations[x][y].printPossDirect();
    }
    
  }
}


World::~World()
{ 
  //TODO: delete the multidimensional array!
}

void World::setGoal(int x, int y){
  locations[x][y].setGoal(true); 
  goal = locations[x][y];
}

Location* World::getLocation(int row, int coloum ){
  return &locations[row][coloum];
}


int World::getMaxRows(){
  return rows;
}

int World::getMaxColumns(){
  return columns;
}

int World::getId(){
  return id;
}

void World::setId(int id){
  this->id = id;
}
