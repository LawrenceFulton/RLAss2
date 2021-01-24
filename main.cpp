#include "main.h"


void printResults(int length, double *arr){
  int sum = 0;
  std::cout << "rewards123:" << std::endl;
  for (size_t i = 0; i < length; i++)
  {
    if(arr[i] == 1) sum +=1;
    std::cout << arr[i] << ", ";
  }
  std::cout << "\nMouse wins " << double(sum) / length << "percentage of the time " << std::endl; 
}


void runAlgorithms(){
  int algorithm = 2;  // 0 = SARSA, 1 = Q-learning, 2 = double Q-learning
  World world(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS);
  Cat cat(ROWS-2, COLUMNS-2, ROWS,COLUMNS);

  Location* curLoc;
  double alpha = 0.9;
  double discount = 0.9;
  double eps = 0.8;
  int repetitions = 1000;
  int mode = (algorithm == 2)? 1: 0; 
  int binRan; // needed for the coinflip in double Q-learning
  double *arr = (double*) calloc (repetitions,sizeof(double));

  int mROld, mCOld, mRNew, mCNew; // mouse column and row
  int cROld, cCOld, cRNew, cCNew; // cat column and row

  // keeps track of the best move for the agent
  char mBestMove;
  char cBestMove;

  char mBestMoveNewState;
  char cBestMoveNewState;

  // keeps track of the reward of the agents (mousseReward = -cReward)
  int mReward;
  int cReward;

  // keeps track of the states of the mouse 
  State *mNewState; //State_t+1
  State *mOldState; //State_t

  // keeps track of the states of the cat
  State *cNewState; //State_t+1
  State *cOldState; //State_t

  // the new Q value 
  double mNewVal;
  double cNewVal;

  // cat and mouse get to know eachother from far away
  cat.setMouse(&mouse);
  mouse.setCat(&cat);

  // both agents learn the map
  mouse.learnTransitions(&world);
  cat.learnTransitions(&world);

 for (size_t i = 0; i < repetitions; i++)
  {
    // resetting coordinates for each trial (could maybe do random)
    mouse.setCoordinates(0,0);
    cat.setCoordinates(ROWS-2, COLUMNS-2); // will be just in front of the exit

    mOldState =  mouse.getInternalState();
    cOldState = cat.getInternalState();

    do // reward will stay 0 until either the mouse got eaten or managed to esceape 
    {
      // the current agent state Q
      mBestMove = mouse.getBestMove(mode,eps);
      cBestMove = cat.getBestMove(mode,eps);   

      
      mouse.move(mBestMove);
      cat.move(cBestMove);

      cNewState = cat.getInternalState();
      mNewState = mouse.getInternalState();


      // the new state from which we can get the reward and the max value
      mReward = mNewState->getR();
      cReward = cNewState->getR();


      switch (algorithm)
      {
      case 0: //////// SARSA 
        cBestMoveNewState = cNewState->getBestMove(mode);
        mBestMoveNewState = mNewState->getBestMove(mode);

        //Bellman equation for mouse   (-testReward)
        mNewVal = mOldState->getDirectionValue(mode, mBestMove) 
                    + alpha * (-cReward + discount 
                    * mNewState->getDirectionValue(mode,mBestMoveNewState) 
                    - mOldState->getDirectionValue(mode,mBestMove));
                    
        mOldState->setDirectionValue(mode,mBestMove, mNewVal);


        // important is the -1 infront of reward reward for the cat
        cNewVal = cOldState->getDirectionValue(mode,cBestMove) 
                  + alpha * (cReward + discount 
                  * cNewState->getDirectionValue(mode,cBestMoveNewState) 
                  - cOldState->getDirectionValue(mode,cBestMove));
      
        cOldState->setDirectionValue(mode,cBestMove,cNewVal);

        break;
      
      case 1: /////// Q-Learning
        //Bellman equation for mouse   (-testReward)
        mNewVal = mOldState->getDirectionValue(mode,mBestMove) 
                    + alpha * (mReward + discount * mNewState->maxValue() 
                    - mOldState->getDirectionValue(mode, mBestMove));

        mOldState->setDirectionValue(mode,mBestMove, mNewVal);


        // important is the -1 infront of reward reward for the cat
        cNewVal = cOldState->getDirectionValue(mode,cBestMove) 
                  + alpha * (cReward + discount * cNewState->maxValue() 
                  - cOldState->getDirectionValue(mode,cBestMove));

        cOldState->setDirectionValue(mode,cBestMove,cNewVal);

        break;
      case 2: ////// doubleQ-learning 
        // binRan can either be 0 or 1 for mouse 
        binRan = rand()%2;
        mBestMoveNewState = mNewState->getBestMove(binRan);
        // double Q update mouse 
        mNewVal = mOldState->getDirectionValue(binRan,mBestMove) + 
                      alpha * (mReward + discount * 
                      mNewState->getDirectionValue(!binRan,mBestMoveNewState) -
                      mOldState->getDirectionValue(binRan,mBestMove));

        mOldState->setDirectionValue(binRan,mBestMove, mNewVal);
        
        // binRan can either be 0 or 1 for cat
        binRan = rand()%2;    
        cBestMoveNewState = cNewState->getBestMove(binRan);
        // double Q update cat
        cNewVal = cOldState->getDirectionValue(binRan,cBestMove) + 
                      alpha * (cReward + discount * 
                      cNewState->getDirectionValue(!binRan,cBestMoveNewState) -
                      cOldState->getDirectionValue(binRan,cBestMove));

        cOldState->setDirectionValue(binRan,cBestMove, cNewVal);
        break;
      }

      // S <- S'
      mOldState =  mouse.getInternalState();
      cOldState = cat.getInternalState();

    }while (mReward == 0);
    arr[i] = mReward;
  }
  printResults(repetitions,arr);

}




int main(int argc, char const *argv[])
{
  srand(time(0));
  runAlgorithms();
  return 0;
}