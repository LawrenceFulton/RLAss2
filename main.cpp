#include "main.h"


void printResults(int length, double *arr){
  int sum = 0;
  // std::cout << "rewards123:" << std::endl;
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

std::string arrayToString(double *arr, int len){
  std::ostringstream os;
  for (size_t i = 0; i < len; i++)
  {
    os << arr[i] << ",";
  }
  std::string str(os.str());
  
  return str;
}

void appendOutput( double *reward, int len){
  std::fstream f;
  std::ofstream fout;
  std::ifstream fin;

  // for reward
  fin.open("data/reward.txt");
  fout.open ("data/reward.txt",std::ios::app);
  if(fin.is_open()){
    fout<< "\n" << arrayToString(reward,len);
  }



  std::cout << "_____________\n" <<   arrayToString(reward,len) << std::endl;
  for (size_t i = 0; i < len; i++)
  {
    std::cout << reward[i] << ",";
  }
  std::cout << std::endl;
  

  fin.close();
  fout.close();
}

void runAlgorithms(int catAlg, int catExp, int mouseAlg, int mouseExp){

  //////////////////////// CHANGABLE PARAMETER /////////////////////

  int mAlg = mouseAlg;
  int cAlg = catAlg;  

  int mExp = mouseExp;
  int cExp = catExp;

  double mAlpha = 0.42;
  double mDiscount = 0.59;
  double mEps = 0.005;
  double mC = 0.1;

  double cAlpha = 0.68;
  double cDiscount = 0.85;
  double cEps = 0.0;
  double cC = 0.002;

  switch(catAlg){
    case(0): // QLEARN
      if(catExp==0){ //EPS
        cAlpha = 0.24;
        cDiscount = 0.47;
        cEps = 0.005;
      } else { //UCB
        cAlpha = 0.68;
        cDiscount = 0.85;
        cC = 0.002;
      }
      break;
    case(1): //QQLEARN
      if(catExp==0){ //EPS
        cAlpha = 0.29;
        cDiscount = 0.42;
        cEps = 0.007;
      } else { //UCB
        cAlpha = 0.55;
        cDiscount = 0.85;
        cC = 0.004;
      }
      break;
    case(2)://SARSA
      if(catExp==0){//EPS
        cAlpha = 0.23;
        cDiscount = 0.38;
        cEps = 0.006;
      } else {//UCB
        cAlpha = 0.32;
        cDiscount = 0.7;
        cC = 0.016;
      }
      break;    
  }
  switch(mouseAlg){
    case(0): // QLEARN
      if(mouseExp==0){ //EPS
        mAlpha = 0.42;
        mDiscount = 0.19;
        mEps = 0.02;
      } else { //UCB
        mAlpha = 0.56;
        mDiscount = 0.85;
        mC = 0.001;
      }
      break;
    case(1): //QQLEARN
      if(mouseExp==0){ //EPS
        mAlpha = 0.51;
        mDiscount = 0.53;
        mEps = 0.003;
      } else { //UCB
        mAlpha = 0.82;
        mDiscount = 0.89;
        mC = 0.007;
      }
      break;
    case(2)://SARSA
      if(mouseExp==0){//EPS
        mAlpha = 0.43;
        mDiscount = 0.52;
        mEps = 0.002;
      } else {//UCB
        mAlpha = 0.76;
        mDiscount = 0.82;
        mC = 0.001;
      }
      break;    
  }


  /////////////////// NOT FOR TOUCHING ///////////////////

  World world(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS, &world);
  Cat cat(ROWS-2, COLUMNS-2, ROWS,COLUMNS, &world);

  int mMode = (mAlg == DOUBLEQ)? 1: 0; 
  int cMode = (cAlg == DOUBLEQ)? 1: 0;
  
  int repetitions = 10000;


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

    mouse.setCoordinates(0,0);
    cat.setCoordinates(ROWS - 2, COLUMNS - 2); // will be just in front of the exit

    mOldState =  mouse.getInternalState();
    cOldState = cat.getInternalState();

    mBestMoveNewState = (mExp == EPS) ? mouse.epsGreedy(mMode,mEps):mouse.ucb(mC); 
    cBestMoveNewState = (cExp == EPS) ? cat.epsGreedy(cMode, cEps): cat.ucb(cC);

    do // reward will stay 0 until either the mouse got eaten or managed to esceape 
    {

      // the current agent state Q 
      if (mExp == EPS)
      {
        mBestMove = (mAlg != SARSA)? mouse.epsGreedy(mMode, mEps): mBestMoveNewState;            
      }else
      {
        mBestMove = (mAlg!=SARSA)? mouse.ucb(mC): mBestMoveNewState;
      }
      
      if (cExp == EPS)
      {
        cBestMove = (cAlg != SARSA)? cat.epsGreedy(cMode, cEps): cBestMoveNewState;            
      }else
      {
        cBestMove = (cAlg!=SARSA)? cat.ucb(mC): cBestMoveNewState;
      }


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

        mBestMoveNewState =(mExp == EPS)?  mouse.epsGreedy(mMode, mEps):mouse.ucb(mC) ;

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

        cBestMoveNewState = (cExp == EPS)? cat.epsGreedy(cMode,cEps): cat.ucb(cC);

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
  saveOutput(arr, repetitions);
}

void gridSearch(){

  //////////////////////// CHANGABLE PARAMETER /////////////////////
  int mAlg = QLEARN;
  int cAlg = QLEARN;  

  int mExp = EPS;
  int cExp = UCB;

  double mAlpha = 0.42;
  double mDiscount = 0.59;
  double mEps = 0.005;
  double mC = 0.1;

  double cAlpha = 0.68;
  double cDiscount = 0.85;
  double cEps = 0.0;
  double cC = 0.002;


  /////////////////// NOT FOR TOUCHING ///////////////////

  World world(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS, &world);
  Cat cat(ROWS-2, COLUMNS-2, ROWS,COLUMNS, &world);

  int mMode = (mAlg == DOUBLEQ)? 1: 0; 
  int cMode = (cAlg == DOUBLEQ)? 1: 0;
  
  int repetitions = 10000;

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
  
  for (size_t a = 10; a < 85; a+=10)
  {
    cAlpha = double(a) / 100;

    for (size_t d = 9; d < 90; d+=10)
    {
      cDiscount = double(d) / 100;

      for (size_t e = 1; e < 52; e+=10)
      {
        cC = double(e)/1000;
        
        // should be done for memory allocation issues 
        cat.deleteStates();
        mouse.deleteStates();
        cat.init();
        mouse.init();


        for (size_t i = 0; i < repetitions; i++)
        {
          // resetting coordinates for each trial (could maybe do random)

          mouse.setCoordinates(0,0);
          cat.setCoordinates(ROWS - 2, COLUMNS - 2); // will be just in front of the exit

          mOldState =  mouse.getInternalState();
          cOldState = cat.getInternalState();

          mBestMoveNewState = (mExp == EPS) ? mouse.epsGreedy(mMode,mEps):mouse.ucb(mC); 
          cBestMoveNewState = (cExp == EPS) ? cat.epsGreedy(cMode, cEps): cat.ucb(cC);

          do // reward will stay 0 until either the mouse got eaten or managed to esceape 
          {

            // the current agent state Q 
            if (mExp == EPS)
            {
              mBestMove = (mAlg != SARSA)? mouse.epsGreedy(mMode, mEps): mBestMoveNewState;            
            }else
            {
              mBestMove = (cAlg!=SARSA)? mouse.ucb(mC): mBestMoveNewState;
            }
            
            if (cExp == EPS)
            {
              cBestMove = (cAlg != SARSA)? cat.epsGreedy(cMode, cEps): cBestMoveNewState;            
            }else
            {
              cBestMove = (cAlg!=SARSA)? cat.ucb(mC): cBestMoveNewState;
            }


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

              mBestMoveNewState =(mExp == EPS)?  mouse.epsGreedy(mMode, mEps):mouse.ucb(mC) ;

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

              cBestMoveNewState = (cExp == EPS)? cat.epsGreedy(cMode,cEps): cat.ucb(cC);

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


          if (cReward == 1) sum ++;
        }
        std::cout << cAlpha << ", " << cDiscount << ", " << cC << ", " << double(sum) / repetitions << std::endl;
        sum = 0;
      }
    }
  }
  // printResults(repetitions, arr);
}

void arena(){
  saveOutput(0,0);
  //////////////////////// CHANGABLE PARAMETER /////////////////////
  int mAlg = QLEARN;
  int mExp = UCB;
  int cAlg = SARSA;  
  int cExp = UCB;


  /////////////////// NOT FOR TOUCHING ///////////////////
  double mAlpha;
  double mDiscount;
  double mEps;
  double mC;

  double cAlpha;
  double cDiscount;
  double cEps;
  double cC;

  // Ininitialisation of param 
  //MOUSE
  switch(cAlg){
    case(QLEARN): // QLEARN
      if(cExp == EPS){ //EPS
        cAlpha = 0.24;
        cDiscount = 0.47;
        cEps = 0.005;
      } else { //UCB
        cAlpha = 0.68;
        cDiscount = 0.85;
        cC = 0.002;
      }
      break;
    case(DOUBLEQ): //QQLEARN
      if(cExp==EPS){ //EPS
        cAlpha = 0.29;
        cDiscount = 0.42;
        cEps = 0.007;
      } else { //UCB
        cAlpha = 0.55;
        cDiscount = 0.85;
        cC = 0.004;
      }
      break;
    case(SARSA)://SARSA
      if(cExp==EPS){//EPS
        cAlpha = 0.23;
        cDiscount = 0.38;
        cEps = 0.006;
      } else {//UCB
        cAlpha = 0.32;
        cDiscount = 0.7;
        cC = 0.016;
      }
      break;    
  }
  //CAT
  switch(mAlg){
    case(QLEARN): // QLEARN
      if(mExp == 0){ //EPS
        mAlpha = 0.42;
        mDiscount = 0.19;
        mEps = 0.02;
      } else { //UCB
        mAlpha = 0.56;
        mDiscount = 0.85;
        mC = 0.001;
      }
      break;
    case(DOUBLEQ): //QQLEARN
      if(mExp==EPS){ //EPS
        mAlpha = 0.51;
        mDiscount = 0.53;
        mEps = 0.003;
      } else { //UCB
        mAlpha = 0.82;
        mDiscount = 0.89;
        mC = 0.007;
      }
      break;
    case(SARSA)://SARSA
      if(mExp==EPS){//EPS
        mAlpha = 0.43;
        mDiscount = 0.52;
        mEps = 0.002;
      } else {//UCB
        mAlpha = 0.76;
        mDiscount = 0.82;
        mC = 0.001;
      }
      break;    
  }
  
  World world(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS, &world);
  Cat cat(ROWS-2, COLUMNS-2, ROWS,COLUMNS, &world);

  int mMode = (mAlg == DOUBLEQ)? 1: 0; 
  int cMode = (cAlg == DOUBLEQ)? 1: 0;
  
  int repetitions = 1000;
  int epoche = 10000;


  int sum = 0;
  int binRan; // needed for the coinflip in double Q-learning

  double *arr = (double*) calloc (epoche,sizeof(double));

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
    cat.deleteStates();
    mouse.deleteStates();
    cat.init();
    mouse.init();


    for (size_t j = 0; j < epoche; j++)
    {

      
      // resetting coordinates for each trial (could maybe do random)

      mouse.setCoordinates(0,0);
      cat.setCoordinates(ROWS - 2, COLUMNS - 2); // will be just in front of the exit

      mOldState =  mouse.getInternalState();
      cOldState = cat.getInternalState();

      mBestMoveNewState = (mExp == EPS) ? mouse.epsGreedy(mMode,mEps):mouse.ucb(mC); 
      cBestMoveNewState = (cExp == EPS) ? cat.epsGreedy(cMode, cEps): cat.ucb(cC);

      do // reward will stay 0 until either the mouse got eaten or managed to esceape 
      {

        // the current agent state Q 
        if (mExp == EPS)
        {
          mBestMove = (mAlg != SARSA)? mouse.epsGreedy(mMode, mEps): mBestMoveNewState;            
        }else
        {
          mBestMove = (mAlg!=SARSA)? mouse.ucb(mC): mBestMoveNewState;
        }
        
        if (cExp == EPS)
        {
          cBestMove = (cAlg != SARSA)? cat.epsGreedy(cMode, cEps): cBestMoveNewState;            
        }else
        {
          cBestMove = (cAlg!=SARSA)? cat.ucb(mC): cBestMoveNewState;
        }


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

          mBestMoveNewState =(mExp == EPS)?  mouse.epsGreedy(mMode, mEps):mouse.ucb(mC) ;

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

          cBestMoveNewState = (cExp == EPS)? cat.epsGreedy(cMode,cEps): cat.ucb(cC);

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
      arr[j] = mReward;
    }
    // printResults(epoche, arr);
    appendOutput(arr, epoche);
  }
}



int main(int argc, char const *argv[])
{
  srand(time(0));

  bool manual = true;

  if (manual)
  {
    int catAlg, catExp, mouseAlg, mouseExp;
    std::cout << "Please enter which algorithm you wish to use for the cat:\n(0): Q-learning, (1): Double Q-learning or (2): SARSA" << std::endl; 
    std::cin >> catAlg;
    std::cout << "Please enter which exploration strategy you wish to use for the cat:\n(0): Epsilion-Greedy, (1): Upper confidence bound" << std::endl; 
    std::cin >> catExp;
    std::cout << "Please enter which algorithm you wish to use for the mouse:\n(0): Q-learning, (1): Double Q-learning or (2): SARSA" << std::endl; 
    std::cin >> mouseAlg;
    std::cout << "Please enter which exploration strategy you wish to use for the mouse:\n(0): Epsilion-Greedy, (1): Upper confidence bound" << std::endl; 
    std::cin >> mouseExp;

    // STILL Allows for user to set one agent as random (option 3)!
    if(catAlg < 0 || catAlg > 3 || catExp < 0 || catExp > 1 || mouseAlg < 0 || mouseAlg > 3 || mouseExp < 0 || mouseExp > 1){
      std::cout << "Please enter a valid choice for the algorithm and exploration strategy!" <<std::endl; 
      return 0;
    }
    runAlgorithms(catAlg, catExp, mouseAlg, mouseExp);
  }else
  {
    arena();
  }
  return 0;
}