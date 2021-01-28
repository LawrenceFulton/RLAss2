#include "header/State.h"
State::State(/* args */)
{
}

State::State(int mouseR, int mouseC, int catR, int catC){
  setValues(mouseR, mouseC, catR, catC, 0);
  //set the initial array for directions in each state
  for(int i = 0; i < 4; i++){
    this->directionVisitedCount[i] = 0;
  }
}


State::~State()
{
  free(directionVisitedCount);
}

void State::printState(){
  std::cout << "Own: " << ownR << ", " << ownC
            << " and Other: "<< otherR << ", " << otherC 
            <<" and r:" << r << " and ID << " << id <<std::endl;
  std::cout << toLeft0<< " " << toRight0 << " " << toTop0 << " " << toBottom0 << std::endl;
}

void State::setValues(int ownR, int ownC, int otherR, int otherC, double r){
  this->ownR = ownR;
  this->ownC = ownC;
  this->otherR = otherR;
  this->otherC = otherC;
  this->r = r;

}

void State::updateDirectionVisited(State* curState, char direction){
  //for the direction increment counter by 1

  int numDirection = -1;
  switch(direction){
    case('l'):  
      numDirection = 0;
      break;
    case('r'):
      numDirection = 1;
      break;
    case('t'):
      numDirection = 2;
      break;
    case('d'):
      numDirection = 3;
      break;
  }
  if(numDirection > -1){
    curState->directionVisitedCount[numDirection]++;
  }
  /*  if(direction > -1){
    curState->directionVisitedCount[direction]++;
  }
  */

}

void State::setTransition(int specialCase, Location* loc){

  // checks if the move is possible 
  bool left = loc->isDirecPoss('l');
  bool right = loc->isDirecPoss('r');
  bool top = loc->isDirecPoss('t');
  bool bottom = loc->isDirecPoss('d');


  // the special cases are happening so that the cat doesn't
  // camp the goal state like a fucking noob

  right = (specialCase == 1)? false: right;
  bottom = (specialCase == 2) ? false: bottom;

  // Creates, when possible a q value of between 0 and 1 else -DBL_MAX
  toLeft0 = left ? double(rand())/RAND_MAX :  -DBL_MAX;
  toRight0 = right ? double(rand())/RAND_MAX : -DBL_MAX;
  toTop0 = top ? double(rand())/RAND_MAX : -DBL_MAX;
  toBottom0 = bottom ? double(rand())/RAND_MAX : -DBL_MAX; 


  // used in double q learning 
  toLeft1 = left ? double(rand())/RAND_MAX :  -DBL_MAX;
  toRight1 = right ? double(rand())/RAND_MAX : -DBL_MAX;
  toTop1 = top ? double(rand())/RAND_MAX : -DBL_MAX;
  toBottom1 = bottom ? double(rand())/RAND_MAX : -DBL_MAX; 

}


// returns the best move with the highest Q value, can also return the move regarding both Q values per action 
char State::argMaxMove(int mode){
  double max = toLeft0;
  char best = 'l'; 
  
  if (mode == SINGLE){ // to be used in Q-learning and Sarsa
    best = (toRight0 > max) ? 'r' : best;
    max = (toRight0 > max) ? toRight0 : max;

    best = (toTop0 > max) ? 't' : best;
    max = (toTop0 > max) ? toTop0 : max;

    best = (toBottom0 > max) ? 'd' : best;
    max = (toBottom0 > max) ? toBottom0 : max;   
  }else
  {
    double sumLeft = (toLeft0 == -DBL_MAX) ? -DBL_MAX: toLeft0 + toLeft1;
    double sumRight = (toRight0 == -DBL_MAX) ? -DBL_MAX: toRight0 + toRight1;
    double sumTop = (toTop0 == -DBL_MAX) ? -DBL_MAX: toTop0 + toTop1;
    double sumBottom = (toBottom0 == -DBL_MAX) ? -DBL_MAX: toBottom0 + toBottom1;
    
    max = sumLeft;

    best = (sumRight > max) ? 'r' : best;
    max = (sumRight > max) ? sumRight : max;

    best = (sumTop > max) ? 't' : best;
    max = (sumTop > max) ? sumTop : max;

    best = (sumBottom > max) ? 'd' : best;
    max = (sumBottom > max) ? sumBottom : max;   
  }


  return best;
}

// returns the reward
double State::getR(){
  return r;
}


// returns the largest value for an action in that state
double State::maxValue(){
  double max = toLeft0;
  max = (toRight0 > max) ? toRight0 : max;
  max = (toTop0 > max) ? toTop0 : max;
  max = (toBottom0 > max) ? toBottom0 : max; 


  return max; 
}



void State::setDirectionValue(int set, char direction, double newVal){

  if (set == 0){
    switch (direction)
    {
    case 'l': // left
      toLeft0 = newVal;
      break;
    case 'r': // right
      toRight0 = newVal;
      break;
    case 't': // up
      toTop0 = newVal;
      break;
    case 'd': // down
      toBottom0 = newVal;
      break;
    default:
      std::cout << "There has been an error, the direction cant be " << direction << std::endl;
    } 
  }else
  {
    switch (direction)
    {
    case 'l': // left
      toLeft1 = newVal;
      break;
    case 'r': // right
      toRight1 = newVal;
      break;
    case 't': // up
      toTop1 = newVal;
      break;
    case 'd': // down
      toBottom1 = newVal;
      break;
    default:
      std::cout << "There has been an error, the direction cant be " << direction << std::endl;
    }  
  }
   
}

// directionValue also known as Q(t,a)
double State::getDirectionValue(int set, char direction){
  
  double returnValue;
  switch (direction)
  {
  case 'l': // left
    returnValue = (set == SINGLE)? toLeft0: toLeft1;
    break;
  case 'r': // right
    returnValue = (set == SINGLE)? toRight0: toRight1;
    break;
  case 't': // up
    returnValue = (set == SINGLE)? toTop0: toTop1;
    break;
  case 'd': // down
    returnValue = (set == SINGLE)? toBottom0: toBottom1;
    break;
  } 
  return returnValue;
}
