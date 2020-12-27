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
  bool goal;
  int x;
  int y;


public:
  int id; // for debugging mostly
  Location(/* args */);
  Location(bool toLeft, bool toRight, bool toTop, bool toBottom);
  ~Location();

  void setPossDirect(bool toLeft, bool toRight, bool toTop, bool toBottom);
  void setCoordinates(int x, int y);
  void printPossDirect();
  void setGoal(bool goal);
  bool isGoal();

  bool isDirecPoss(char direction);




};


#endif