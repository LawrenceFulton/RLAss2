#ifndef LOCATION_H
#define LOCATION_H

#include<iostream> 
#include<ostream>
class Location
{
private:
  bool toLeft;
  bool toRight;
  bool toTop; 
  bool toBottom;
  bool isGoal;
  int x;
  int y;

  Location *leftNeighbour;
  Location *rightNeighbour;
  Location *topNeighbour;
  Location *bottomNeighbour;


public:
  Location(/* args */);
  Location(bool toLeft, bool toRight, bool toTop, bool toBottom);
  ~Location();

  void setPossDirect(bool toLeft, bool toRight, bool toTop, bool toBottom);
  void setNeighbours(Location *leftNeighbour, Location *rightNeighbour, Location *topNeighbour, Location *bottomNeighbour);
  void setCoordinates(int x, int y);
  void printPossDirect();
  void setGoal(bool isGoal);
  Location * getNeighbour(char direction);
};


#endif