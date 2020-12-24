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

public:
  Location(/* args */);
  Location(bool toLeft, bool toRight, bool toTop, bool toBottom);
  ~Location();

  void setPossDirect(bool toLeft, bool toRight, bool toTop, bool toBottom);
  void printPossDirect();
  void setGoal(bool isGoal);
};


#endif