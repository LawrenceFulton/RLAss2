#include "main.h"

void qLearning(){
  World newWorld(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS);
  World* pointerW = &newWorld; 
  Location* curLoc;



  double alpha = 0.5;
  double discount = 0.999;
  double eps = 0.8;
  int repetitions = 10;

  char input;
  int mR, mC; // mouse column and row
  int cR, cC; // cat column and row
  mouse.learnTransitions(pointerW);
  cR = 1;
  cC = 1;
  char bestMove;


  
  mR = mouse.getR();
  mC = mouse.getC();

  int reward; 
  State *newState; //State_t+1
  State *oldState; //State_t
  double newVal;

  for (size_t i = 0; i < repetitions; i++)
  {
    mouse.setCoordinates(0,0);
    mR = mouse.getR();
    mC = mouse.getC();
    while (!(newWorld.getLocation(mR,mC)->isGoal()) ) //should be changed until mouse is in the goal state 
    {
      // the current state 
      oldState =  mouse.getInternalState(cR,cC);


      // getting the best move (we know that that move is a valid move)
      bestMove = mouse.getBestMove(cR,cC,eps);

      // moves the mouse in the correct direction       
      mouse.move(bestMove);

      // gets the new R and C values
      mR = mouse.getR();
      mC = mouse.getC();


      // the new state from which we can get the reward and the max value
      newState = mouse.getInternalState(cR,cC);
      reward = newState->getR();

      //Bellman equation
      newVal = oldState->getDirectionValue(bestMove) + alpha * (reward + discount * newState->maxValue() - oldState->getDirectionValue(bestMove));
      oldState->setDirectionValue(bestMove, newVal);

      std::cout << mR << " " << mC << std::endl;

    }
    
  }
  
}

void walkingWithWASD(){

  World newWorld(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS);
  World* pointerW = &newWorld; 
  Location* curLoc;
  char input;

  int r,c,x = 0;

  while (x < 1)
  {
    x++;
    r = mouse.getR();
    c = mouse.getC();
    std::cout << "r,c: " << r<< c << std::endl; 

    curLoc = newWorld.getLocation(r,c);
    std::cout << "ID:" << curLoc->id << "Possible moves :" << std::endl;
    curLoc->printPossDirect();


    if(curLoc->isGoal()){
      std::cout << "congratulations you won the game" << std::endl;
      return ;
    }



    std::cin >> input; 
    std::cout << "input was " << input << std::endl;
    switch (input)
    {
    case 'w':
      std::cout << "should have gone up" <<std::endl;
      mouse.move('t', curLoc);      
      break;

    case 'a':
      std::cout << "should have gone left" <<std::endl;
      mouse.move('l',curLoc);
      break;

    case 's':
      std::cout << "should have gone down" <<std::endl;
      mouse.move('d',curLoc);
      break;
    
    case 'd':
      std::cout << "should have gone right" <<std::endl;
      mouse.move('r',curLoc);
      break;
    case 'z':
      std::cout << "Undertandable, have a nice day!" <<std::endl;
      return;
      break;

    default:
      std::cout << "please try again, type z for exit" << std::endl;
    }
    mouse.printCoordinates();
  }
}




int main(int argc, char const *argv[])
{
  srand(time(0));
  qLearning();
  return 0;
}



