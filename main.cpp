#include "main.h"

void qLearning(){
  World newWorld(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS);
  Cat cat(ROWS-1, COLUMNS-1, ROWS,COLUMNS);
  World* pointerW = &newWorld; 
  Location* curLoc;



  double alpha = 0.5;
  double discount = 0.999;
  double eps = 0.8;
  int repetitions = 100;
  int testReward;

  double arr[repetitions];

  char input;
  int mROld, mCOld, mRNew, mCNew; // mouse column and row
  int cROld, cCOld, cRNew, cCNew; // cat column and row
  mouse.learnTransitions(pointerW);

  char bestMoveMouse;
  char bestMoveCat;


  cROld = cat.getC();
  cCOld = cat.getR();
  mROld = mouse.getR();
  mCOld = mouse.getC();

  cRNew = cat.getC();
  cCNew = cat.getR();
  mRNew = mouse.getR();
  mCNew = mouse.getC();



  int reward;  //same reward can be used for mouse and cat (have to use it *-1)
  State *mouseNewState; //State_t+1
  State *mouseOldState; //State_t

  State *catNewState; //State_t+1
  State *catOldState; //State_t
  double mouseNewVal;
  double catNewVal;

  for (size_t i = 0; i < 10; i++)
  {
    mouse.setCoordinates(0,0);
    cat.setCoordinates(ROWS-2, COLUMNS-2);
    cROld = cat.getC();
    cCOld = cat.getR();
    mROld = mouse.getR();
    mCOld = mouse.getC();
    reward = 0;





    while (reward == 0) // reward will stay 0 until either the mouse got eaten or managed to esceape 
    {
      // the current mouse state 
      mouseOldState =  mouse.getInternalState(cROld,cROld);
      // catOldState = cat.getInternalState(mROld, mCOld);


      // getting the best move (we know that that move is a valid move)
      bestMoveMouse = mouse.getBestMove(cROld,cROld,eps);
      // bestMoveCat = cat.getBestMove(mROld, cCOld, eps);


      // moves the mouse in the correct direction       
      mouse.move(bestMoveMouse);
      // cat.move(bestMoveCat);

      // gets the new R and C values
      // cRNew = cat.getC();
      // cCNew = cat.getR();
      mRNew = mouse.getR();
      mCNew = mouse.getC();

      // the new state from which we can get the reward and the max value
      mouseNewState = mouse.getInternalState(cRNew,cCNew);
      // catNewState = cat.getInternalState(mRNew, mCNew );
      reward = mouseNewState->getR();

      // testReward = catNewState->getR();
      
      // // both rewards should be the same ! 
      // if (reward != testReward)
      // {
      //   std::cout << "NONONONONO" << std::endl;
      //   return ;
      // }
      

      //Bellman equation for mouse 
      mouseNewVal = mouseOldState->getDirectionValue(bestMoveMouse) + alpha * (reward + discount * mouseNewState->maxValue() - mouseOldState->getDirectionValue(bestMoveMouse));
      mouseOldState->setDirectionValue(bestMoveMouse, mouseNewVal);

      // catNewVal = catOldState->getDirectionValue(bestMoveCat) + alpha * (reward + discount * catNewState->maxValue() - catOldState->getDirectionValue(bestMoveCat));
      // catOldState->setDirectionValue(bestMoveCat,catNewVal);
      // std::cout << mR << " " << mC << std::endl;
    }
    arr[i] = reward;
  }
  

  std::cout << "rewards:" << std::endl;
  for (size_t i = 0; i < repetitions; i++)
  {
    std::cout << arr[i] << ", ";
  }
  


}

void walkingWithWASD(){

  World newWorld(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS);
  World* pointerW = &newWorld; 
  Location* curLoc;
  char input;

  int r,c;

  while (true)
  {
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



