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


void saveOutput( double *reward, int len){

  //Saves the percentage the optimal arm is used
  std::ofstream outRew( "data/reward.txt" );
  copy( reward, reward + len, std::ostream_iterator<double>( outRew, "," ) );

}

void runAlgorithms(){
  int mAlg = DOUBLEQ;
  int cAlg = RANDOM;  

  World world(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS, &world);
  Cat cat(ROWS-2, COLUMNS-2, ROWS,COLUMNS, &world);

  int mMode = (mAlg == DOUBLEQ)? 1: 0; 
  int cMode = (cAlg == DOUBLEQ)? 1: 0;
  
  int repetitions = 10000;

  double cAlpha = 0.11;
  double cDiscount = 0.2;
  double cEps = 0.01;

  double mAlpha = 0.11;
  double mDiscount = 0.2;
  double mEps = 0.01;

  int sum = 0;
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

  if (mAlg == RANDOM) mEps = 0;
  if (cAlg == RANDOM) cEps = 0;
  




  for (size_t i = 0; i < repetitions; i++)
  {
    // resetting coordinates for each trial (could maybe do random)
    std::cout << i << std::endl;


    mouse.setCoordinates(rand() % (ROWS - 2), rand() % (ROWS - 2));
    cat.setCoordinates(ROWS - 2, COLUMNS - 2); // will be just in front of the exit

    mOldState =  mouse.getInternalState();
    cOldState = cat.getInternalState();

    mBestMoveNewState = mouse.getBestMove(mMode,mEps);
    cBestMoveNewState = cat.getBestMove(cMode,cEps);   

    do // reward will stay 0 until either the mouse got eaten or managed to esceape 
    {

      // the current agent state Q 
      mBestMove = (mAlg != SARSA)? mouse.getBestMove(mMode, mEps): mBestMoveNewState;
      cBestMove = (cAlg != SARSA)? cat.getBestMove(cMode, cEps): cBestMoveNewState;

      mouse.move(mBestMove);
      cat.move(cBestMove);

      cNewState = cat.getInternalState();
      mNewState = mouse.getInternalState();

      // the new state from which we can get the reward and the max value
      mReward = mNewState->getR();
      cReward = cNewState->getR();

      ////////////////// Update Mouse ///////////////////////////

      switch (mAlg)
      {
      case SARSA: //////// SARSA 
        mBestMoveNewState = mouse.getBestMove(mMode, mEps);

        //Bellman equation for mouse   (-testReward)
        mNewVal = mOldState->getDirectionValue(mMode, mBestMove) 
                    + mAlpha * (-cReward + mDiscount 
                    * mNewState->getDirectionValue(mMode,mBestMoveNewState) 
                    - mOldState->getDirectionValue(mMode,mBestMove));
                    
        mOldState->setDirectionValue(mMode,mBestMove, mNewVal);

        break;
      
      case QLEARN: /////// Q-Learning
        //Bellman equation for mouse   (-testReward)
        mNewVal = mOldState->getDirectionValue(mMode,mBestMove) 
                    + mAlpha * (mReward + mDiscount * mNewState->maxValue() 
                    - mOldState->getDirectionValue(mMode, mBestMove));

        mOldState->setDirectionValue(mMode,mBestMove, mNewVal);

        break;
      case DOUBLEQ: ////// doubleQ-learning 
        // binRan can either be 0 or 1 for mouse 
        binRan = rand()%2;
        mBestMoveNewState = mNewState->argMaxMove(binRan);
        // double Q update mouse 
        mNewVal = mOldState->getDirectionValue(binRan,mBestMove) + 
                      mAlpha * (mReward + mDiscount * 
                      mNewState->getDirectionValue(!binRan,mBestMoveNewState) -
                      mOldState->getDirectionValue(binRan,mBestMove));

        mOldState->setDirectionValue(binRan,mBestMove, mNewVal);
        
        break;
      }
        

      //////////////////////// UPDATE CAT /////////////////////// 

      switch (cAlg)
      {
      case SARSA: 

        cBestMoveNewState = cat.getBestMove(cMode,cEps);

        // important is the -1 infront of reward reward for the cat
        cNewVal = cOldState->getDirectionValue(cMode,cBestMove) 
                  + cAlpha * (cReward + cDiscount 
                  * cNewState->getDirectionValue(cMode,cBestMoveNewState) 
                  - cOldState->getDirectionValue(cMode,cBestMove));
      
        cOldState->setDirectionValue(cMode,cBestMove,cNewVal);

        break;
      
      case QLEARN:

        // important is the -1 infront of reward reward for the cat
        cNewVal = cOldState->getDirectionValue(cMode,cBestMove) 
                  + cAlpha * (cReward + cDiscount * cNewState->maxValue() 
                  - cOldState->getDirectionValue(cMode,cBestMove));

        cOldState->setDirectionValue(cMode,cBestMove,cNewVal);

        break;
      case DOUBLEQ:

        // binRan can either be 0 or 1 for cat
        binRan = rand()%2;    
        cBestMoveNewState = cNewState->argMaxMove(binRan);
        // double Q update cat
        cNewVal = cOldState->getDirectionValue(binRan,cBestMove) + 
                      cAlpha * (cReward + cDiscount * 
                      cNewState->getDirectionValue(!binRan,cBestMoveNewState) -
                      cOldState->getDirectionValue(binRan,cBestMove));

        cOldState->setDirectionValue(binRan,cBestMove, cNewVal);
        break;
      }

      // S <- S'
      mOldState = mouse.getInternalState();
      cOldState = cat.getInternalState();
    }while (mReward == 0);
    arr[i] = mReward;

  }
  
  printResults(repetitions, arr);
}

void gridSearch(){
  int mAlg = DOUBLEQ;
  int cAlg = RANDOM;  

  World world(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS, &world);
  Cat cat(ROWS-2, COLUMNS-2, ROWS,COLUMNS, &world);

  int mMode = (mAlg == DOUBLEQ)? 1: 0; 
  int cMode = (cAlg == DOUBLEQ)? 1: 0;
  
  int repetitions = 10000;

  double mAlpha = 0.11;
  double mDiscount = 0.2;
  double mEps = 0.01;

  double cAlpha = 0.11;
  double cDiscount = 0.2;
  double cEps = 0.01;



  int sum = 0;
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

  if (mAlg == RANDOM) mEps = 0;
  if (cAlg == RANDOM) cEps = 0;
  
  for (size_t a = 30; a < 55; a++)
  {
    mAlpha = double(a) / 100;

    for (size_t d = 40; d < 60; d++)
    {
      mDiscount = double(d) / 100;

      for (size_t e = 1; e < 15; e++)
      {
        mEps = double(e)/1000;
        
        // should be done for memory allocation issues 
        cat.deleteStates();
        mouse.deleteStates();
        cat.init();
        mouse.init();


        for (size_t i = 0; i < repetitions; i++)
        {
          // resetting coordinates for each trial (could maybe do random)

          mouse.setCoordinates(rand() % (ROWS - 2), rand() % (ROWS - 2));
          cat.setCoordinates(ROWS - 2, COLUMNS - 2); // will be just in front of the exit

          mOldState =  mouse.getInternalState();
          cOldState = cat.getInternalState();

          mBestMoveNewState = mouse.getBestMove(mMode,mEps);
          cBestMoveNewState = cat.getBestMove(cMode,cEps);   

          do // reward will stay 0 until either the mouse got eaten or managed to esceape 
          {

            // the current agent state Q 
            mBestMove = (mAlg != SARSA)? mouse.getBestMove(mMode, mEps): mBestMoveNewState;
            cBestMove = (cAlg != SARSA)? cat.getBestMove(cMode, cEps): cBestMoveNewState;

            mouse.move(mBestMove);
            cat.move(cBestMove);

            cNewState = cat.getInternalState();
            mNewState = mouse.getInternalState();

            // the new state from which we can get the reward and the max value
            mReward = mNewState->getR();
            cReward = cNewState->getR();

            ////////////////// Update Mouse ///////////////////////////

            switch (mAlg)
            {
            case SARSA: //////// SARSA 
              mBestMoveNewState = mouse.getBestMove(mMode, mEps);

              //Bellman equation for mouse   (-testReward)
              mNewVal = mOldState->getDirectionValue(mMode, mBestMove) 
                          + mAlpha * (-cReward + mDiscount 
                          * mNewState->getDirectionValue(mMode,mBestMoveNewState) 
                          - mOldState->getDirectionValue(mMode,mBestMove));
                          
              mOldState->setDirectionValue(mMode,mBestMove, mNewVal);

              break;
            
            case QLEARN: /////// Q-Learning
              //Bellman equation for mouse   (-testReward)
              mNewVal = mOldState->getDirectionValue(mMode,mBestMove) 
                          + mAlpha * (mReward + mDiscount * mNewState->maxValue() 
                          - mOldState->getDirectionValue(mMode, mBestMove));

              mOldState->setDirectionValue(mMode,mBestMove, mNewVal);

              break;
            case DOUBLEQ: ////// doubleQ-learning 
              // binRan can either be 0 or 1 for mouse 
              binRan = rand()%2;
              mBestMoveNewState = mNewState->argMaxMove(binRan);
              // double Q update mouse 
              mNewVal = mOldState->getDirectionValue(binRan,mBestMove) + 
                            mAlpha * (mReward + mDiscount * 
                            mNewState->getDirectionValue(!binRan,mBestMoveNewState) -
                            mOldState->getDirectionValue(binRan,mBestMove));

              mOldState->setDirectionValue(binRan,mBestMove, mNewVal);
              
              break;
            }
              

            //////////////////////// UPDATE CAT /////////////////////// 

            switch (cAlg)
            {
            case SARSA: 

              cBestMoveNewState = cat.getBestMove(cMode,cEps);

              // important is the -1 infront of reward reward for the cat
              cNewVal = cOldState->getDirectionValue(cMode,cBestMove) 
                        + cAlpha * (cReward + cDiscount 
                        * cNewState->getDirectionValue(cMode,cBestMoveNewState) 
                        - cOldState->getDirectionValue(cMode,cBestMove));
            
              cOldState->setDirectionValue(cMode,cBestMove,cNewVal);

              break;
            
            case QLEARN:

              // important is the -1 infront of reward reward for the cat
              cNewVal = cOldState->getDirectionValue(cMode,cBestMove) 
                        + cAlpha * (cReward + cDiscount * cNewState->maxValue() 
                        - cOldState->getDirectionValue(cMode,cBestMove));

              cOldState->setDirectionValue(cMode,cBestMove,cNewVal);

              break;
            case DOUBLEQ:

              // binRan can either be 0 or 1 for cat
              binRan = rand()%2;    
              cBestMoveNewState = cNewState->argMaxMove(binRan);
              // double Q update cat
              cNewVal = cOldState->getDirectionValue(binRan,cBestMove) + 
                            cAlpha * (cReward + cDiscount * 
                            cNewState->getDirectionValue(!binRan,cBestMoveNewState) -
                            cOldState->getDirectionValue(binRan,cBestMove));

              cOldState->setDirectionValue(binRan,cBestMove, cNewVal);
              break;
            }

            // S <- S'
            mOldState = mouse.getInternalState();
            cOldState = cat.getInternalState();
          }while (mReward == 0);
          arr[i] = mReward;


          if (mReward == 1) sum ++;
        }
        std::cout << mAlpha << ", " << mDiscount << ", " << mEps << ", " << double(sum) / repetitions << std::endl;
        sum = 0;
      }
    }
  }
  printResults(repetitions, arr);
}



int main(int argc, char const *argv[])
{
  srand(time(0));
  // runAlgorithms();
  gridSearch();
  return 0;
}