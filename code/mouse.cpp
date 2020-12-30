#include "header/Mouse.h"


Mouse::Mouse(){
  *this = Mouse(0,0);
};


Mouse::Mouse(int x, int y){
  setCoordinates(x,y);
  Agent:
  steps = 0;
}
Mouse::Mouse(int x,int y, int maxRow, int maxCol):Agent(x, y, maxRow,maxCol){
  steps = 0;
}


Mouse::~Mouse(){}

