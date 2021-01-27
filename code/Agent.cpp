#include "header/Agent.h"

Agent::Agent(){};

Agent::Agent(int agent, int r, int c, int maxRow, int maxCol, World* world ){
  this->r = r;
  this->c = c;
  this->maxRow = maxRow;
  this->maxCol = maxCol;
  this->agent = agent;
  this->world = world;
  // world = world1;
  init();
}

Agent::~Agent(){

};

//////////////////////////////

void Agent::init(){
  // can only be used if there are only two agents (1 cat and 1 mouse)!
  // not using multidimensional array since it would get really messy imo 

  int nStates = pow(maxRow*maxCol,2.0);
  states = new State[nStates];

  int mc2mr = maxCol*maxRow*maxCol;
  int mcmr = maxCol*maxRow;


  int counter = 0;

  for (size_t mR = 0; mR < maxRow; mR++)
    for (size_t mC = 0; mC < maxCol; mC++)
      for (size_t cR = 0; cR < maxRow; cR++)
        for (size_t cC = 0; cC < maxCol; cC++)
        {

          r = 0;
          if (agent) // agent is a cat 
          {
            // if the mouse is caught, thats a reward of 1 (for the cat)
            if (mR == cR && mC == cC)
              r = 1;
            else if(cR == maxRow-1 && cC == maxCol-1 ) // if the mouse finds the way out the reward is -1
              r = -1;
          }else// agent is a mouse
          {
            // if the mouse is caught, thats a reward of -1 (for the mouse)
            if (mR == cR && mC == cC)
              r = -1;
            else if(mR == maxRow-1 && mC == maxCol-1 ) // if the mouse finds the way out the reward is 1
              r = 1;
          }
          

          states[mR*mc2mr + mC*mcmr + cR*maxCol + cC].setValues(mR,mC,cR, cC, r);
          // for debug there is an counter / id
          states[mR*mc2mr   +mC*mcmr + cR*maxCol + cC].id = counter;
          counter++;
        }

  learnTransitions(world);
}


// for debug, can be deleted later 
void Agent::printCoordinates(){
  std::cout << "(" << r << "," << c << ")" <<std::endl;
}

void Agent::setCoordinates(int r, int c){ 
  this->r = r;
  this->c = c;
}

// doesn't check if the direction is possible and thus can lead to segmentation fault
// if in doubt one can use move(direction, curPos)
void Agent::move(char direction){
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
  case 's': // stay
    break;
  }
}

// moves the agent into any of the four directions
// chars to use for direction 'l , r, t, d'
void Agent::move(char direction, Location* curLoc){
  if ((curLoc->isDirecPoss(direction)))
  {
    move(direction);
  }
}

// gets the row
int Agent::getR(){
  return r;
}

// gets the column 
int Agent::getC(){
  return c;
}


void Agent::printInteralStates(){
  int mc2mr = maxCol*maxRow*maxCol;
  int mcmr = maxCol*maxRow;
  for (size_t mR = 0; mR < maxRow; mR++)
    for (size_t mC = 0; mC < maxCol; mC++)
      for (size_t cR = 0; cR < maxRow; cR++)
        for (size_t cC = 0; cC < maxCol; cC++)    
          states[mR*mc2mr   +mC*mcmr + cR*maxCol + cC].printState(); 
}


// overtakes the transition from the world created in the main file 
void Agent::learnTransitions(World* world){
  Location* loc;
  int specialCase;
  int stateId;

  int mc2mr = maxCol*maxCol*maxRow;
  int mcmr = maxCol * maxRow;

  bool left;
  bool right;
  bool top;
  bool bottom;

  for (size_t r = 0; r < maxRow; r++) // rows
  {
    for (size_t c = 0; c < maxCol; c++) // columns
    {
      loc = world->getLocation(r,c);
      for (size_t d = 0; d < mcmr; d++) // depth
      {
        stateId = r*mc2mr + c*mcmr + d;

        // The following if statements are for the cat not to camp the exit
        if (r == maxRow-1 && c == maxCol-2 && agent == 1) // on the right of the goal state
          states[stateId].setTransition(1,loc); 
        else if (r == maxRow-2 && c == maxCol-1 && agent == 1) // above the goal state
          states[stateId].setTransition(2,loc); 
        else
          states[stateId].setTransition(0,loc); 
      }
    }
  }
}


// int agent = 0 for mouse and = 1 for cat
// otherR/otherC are the rows and columns of the other agent 
int Agent::getStateNumber(int otherR, int otherC){
  return (r*maxCol*maxCol*maxRow + c *maxCol*maxRow +otherR* maxCol + otherC);
}

State* Agent::getInternalState(int otherR, int otherC){
  int stateNumber = getStateNumber(otherR,otherC);
  return(&states[stateNumber]);
}

char Agent::epsGreedy(int otherR, int otherC,int mode, double eps){
  char bestMove;

  double unif = double(rand())/ RAND_MAX;
  double value;
  int choice;
  State* curState = getInternalState(otherR, otherC);

  // if the value taken from the uniform distribution is smaller than
  // the epsilon value (eps) we take the best move, else we find a random possible 
  // move


  if (unif > eps)
  {
    bestMove = curState->argMaxMove(mode);
  }else
  {

    do
    {
      choice = rand() % 5; 
      bestMove = choices[choice];
      value = curState->getDirectionValue(0,bestMove);
          
    } while (value == -DBL_MAX);
  }
  return bestMove;
}

char Agent::ucb(int otherR, int otherC, double var){
  State* curState = getInternalState(otherR, otherC);
  char bestChoice, curMove;
  double maxValue = -DBL_MAX;
  double curValue;




  for (size_t i = 0; i < 4; i++)
  {
    curMove = choices[i];
    curValue = curState->getDirectionValue(0,curMove) + var *  std::sqrt( double(curState->getNState()) / curState->getNAction(curMove)) ;

    if (curValue > maxValue)
    {
      maxValue = curValue;
      bestChoice = curMove;
    }
  }
  curState->incrementAction(bestChoice);
  curState->incrementState();
  std::cout << bestChoice << std::endl;

  
  return bestChoice;
}


void Agent::deleteStates(){
  delete [] states;
}
