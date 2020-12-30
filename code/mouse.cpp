#include "header/Mouse.h"


Mouse::Mouse(){
  *this = Mouse(0,0);
};


Mouse::Mouse(int x, int y){
  setCoordinates(x,y);
  steps = 0;
}

Mouse::Mouse(int x,int y, int maxRow, int maxCol):Agent(x, y, maxRow,maxCol){
  steps = 0;
}

char Mouse::getBestMove(int cR, int cC, double eps){
  char bestMove;
  bestMove = states[r*maxCol*maxCol*maxRow + c *maxCol*maxRow +cR* maxCol + cC ].getBestMove();

  std::cout << "PRINT STATE :: ";
  states[r*maxCol*maxCol*maxRow + c *maxCol*maxRow +cR* maxCol + cC].printState();
  return bestMove;
}


Mouse::~Mouse(){}

