#include "header/Mouse.h"


Mouse::Mouse(){
};


Mouse::Mouse(int x, int y){
  Agent::setCoordinates(x,y);
  steps = 0;
}

