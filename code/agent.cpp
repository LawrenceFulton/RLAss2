#include "header/Agent.h"

Agent::Agent(){};

Agent::Agent(int r, int c, int maxRow, int maxCol ){
  this->r = r;
  this->c = c;
  this->maxRow = maxRow;
  this->maxCol = maxCol;
  // world = world1;

  // can only be used if there are only two agents (1 cat and 1 mouse)!
  // not using multidimensional array since it would get really messy imo 
  states = (State*) calloc(pow(maxRow*maxCol,2.0), sizeof(State));

  int mc2mr = maxCol*maxRow*maxCol;
  int mcmr = maxCol*maxRow;


  int counter = 0;

  for (size_t mR = 0; mR < maxRow; mR++)
    for (size_t mC = 0; mC < maxCol; mC++)
      for (size_t cR = 0; cR < maxRow; cR++)
        for (size_t cC = 0; cC < maxCol; cC++)
        {
          states[mR*mc2mr   +mC*mcmr + cR*maxCol + cC].setValues(mR,mC,cR, cC, 0);
        }

  printInteralStates();
}

void Agent::printCoordinates(){
  std::cout << "(" << r << "," << c << ")" <<std::endl;
}

void Agent::setCoordinates(int r, int c){ 
  this->r = r;
  this->c = c;
}




// moves the agent into any of the four directions
// chars to use for direction 'l , r, t, d'
void Agent::move(char direction, Location* curLoc){
  if ((curLoc->isDirecPoss(direction)))
  {
    switch (direction)
    {
    case 'l': // left
      c--;
      break;
    case 'r': // right
      c++;
      break;
    case 't': // up
      r--;
      break;
    case 'd': // down
      r++;
      break;
    }
  }
}

// gets the row
int Agent::getR(){
  return r;
}

// gets the coloum 
int Agent::getC(){
  return c;
}

void Agent::printInteralStates(){

  int mc2mr = maxCol*maxRow*maxCol;
  int mcmr = maxCol*maxRow;

  // decomment for checking of all states 
  for (size_t mR = 0; mR < maxRow; mR++)
    for (size_t mC = 0; mC < maxCol; mC++)
      for (size_t cR = 0; cR < maxRow; cR++)
        for (size_t cC = 0; cC < maxCol; cC++)    
          states[mR*mc2mr   +mC*mcmr + cR*maxCol + cC].printState(); 
}


Agent::~Agent(){};
