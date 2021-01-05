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

  double unif = rand()/ RAND_MAX;
  double value;
  int choice;
  State curState = states[r*maxCol*maxCol*maxRow + c *maxCol*maxRow +cR* maxCol + cC ];

  if (unif < eps)
  {
    bestMove = curState.getBestMove();
  }else
  {
    do
    {
      choice = rand() % 4;
      switch (choice)
      {
      case 1:
        value = curState.getDirectionValue('l');
        bestMove = 'l';
        break;
      case 2:
        value = curState.getDirectionValue('r');
        bestMove = 'r';
        break;
      case 3:
        value = curState.getDirectionValue('t');
        bestMove = 't';
        break;
      case 4:
        value = curState.getDirectionValue('d');
        bestMove = 'd';
        break;

      }    
    } while (value == -DBL_MAX);

  }
  
  


  states[r*maxCol*maxCol*maxRow + c *maxCol*maxRow +cR* maxCol + cC].printState();
  return bestMove;
}

State* Mouse::getInternalState(int cR, int cC){
  return(&states[r*maxCol*maxCol*maxRow + c *maxCol*maxRow +cR* maxCol + cC]);
}


Mouse::~Mouse(){}

