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


void SARSA(){
	// initialise the state
  World world(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS);
  Cat cat(ROWS-2, COLUMNS-2, ROWS,COLUMNS);
  Location* curLoc;

  cat.setMouse(&mouse);
  mouse.setCat(&cat);

  double alpha = 0.9;
  double discount = 0.9;
  double eps = 0.8;
  int repetitions = 1000;
  int catReward;
  int mode = 0; // should be 0 for 

  double arr[repetitions];

  char input;
  int mROld, mCOld, mRNew, mCNew; // mouse column and row
  int cROld, cCOld, cRNew, cCNew; // cat column and row
  mouse.learnTransitions(&world);
  cat.learnTransitions(&world);

  char bestMoveMouse;
  char bestMoveCat;
  char oldMoveMouse;
  char oldMoveCat;


  int reward;  //same reward can be used for mouse and cat (just need to multiply the result by -1)
  State *mouseNewState; //State_t+1
  State *mouseOldState; //State_t

  State *catNewState; //State_t+1
  State *catOldState; //State_t

  double mouseNewVal;
  double catNewVal;

  std::cout << "print internal states cat:" << std::endl;
  cat.printInteralStates();



	for (size_t i = 0; i < repetitions; i++){
    mouse.setCoordinates(0,0);
    cat.setCoordinates(ROWS-2, COLUMNS-2); // will be just in front of the exit

    reward = 0;
    // the current mouse state and intital action selection
    mouseOldState =  mouse.getInternalState();
    oldMoveMouse = mouse.getBestMove(mode,eps);

    catOldState = cat.getInternalState();
    oldMoveCat = cat.getBestMove(mode,eps);   

		do // reward will stay 0 until either the mouse got eaten or managed to escape 
		{
      //take action and update reward and state'
      mouse.move(oldMoveMouse);
      cat.move(oldMoveCat);

      //new state
      catNewState = cat.getInternalState(); 
      mouseNewState = mouse.getInternalState();

      // the new state from which we can get the reward 
      reward = mouseNewState->getR();
      catReward = catNewState->getR();

      // select next action from the new state
      bestMoveMouse = mouse.getBestMove(mode,eps);
      bestMoveCat = cat.getBestMove(mode,eps);   

      //Bellman equation for mouse   (-testReward)
      mouseNewVal = mouseOldState->getDirectionValue(mode, oldMoveMouse) + alpha * (-catReward + discount * mouseNewState->getDirectionValue(mode,bestMoveMouse) - mouseOldState->getDirectionValue(mode,oldMoveMouse));
      mouseOldState->setDirectionValue(mode,oldMoveMouse, mouseNewVal);


      // important is the -1 infront of reward reward for the cat
      catNewVal = catOldState->getDirectionValue(mode,oldMoveCat) + alpha * (catReward + discount * catNewState->getDirectionValue(mode,bestMoveCat) - catOldState->getDirectionValue(mode,oldMoveCat));
      catOldState->setDirectionValue(mode,oldMoveCat,catNewVal);


      oldMoveMouse = mouse.getBestMove(mode,eps);
      oldMoveCat = cat.getBestMove(mode,eps);

      //update the state Q <- Q'
      mouseOldState =  mouse.getInternalState();
      catOldState = cat.getInternalState();

    }while (catReward == 0);

    arr[i] = -catReward;
  }
  printResults(repetitions, arr); 
}

void qLearning(){
  World world(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS);
  Cat cat(ROWS-2, COLUMNS-2, ROWS,COLUMNS);
  Location* curLoc;


  cat.setMouse(&mouse);
  mouse.setCat(&cat);


  double alpha = 0.9;
  double discount = 0.9;
  double eps = 0.8;
  int testReward;
  int repetitions = 1000;
  int mode = 0; // 0 for Q-learning + Sarsa, 1 for double Q-learning 


  double arr[repetitions];

  char input;
  int mROld, mCOld, mRNew, mCNew; // mouse column and row
  int cROld, cCOld, cRNew, cCNew; // cat column and row
  mouse.learnTransitions(&world);
  cat.learnTransitions(&world);

  char bestMoveMouse;
  char bestMoveCat;



  int mouseReward;  //same reward can be used for mouse and cat (have to use it *-1)
  int catReward;

  State *mouseNewState; //State_t+1
  State *mouseOldState; //State_t

  State *catNewState; //State_t+1
  State *catOldState; //State_t
  double mouseNewVal;
  double catNewVal;

  std::cout << "print internal states cat:" << std::endl;
  cat.printInteralStates();


  for (size_t i = 0; i < repetitions; i++)
  {
    //std::cout << "__________________epoche "<< i << "____________"<< std::endl;
    mouse.setCoordinates(0,0);
    cat.setCoordinates(ROWS-2, COLUMNS-2); // will be just in front of the exit

    mouseOldState =  mouse.getInternalState();
    catOldState = cat.getInternalState();


    do // reward will stay 0 until either the mouse got eaten or managed to escape 
    {
      // the current mouse state 
      bestMoveMouse = mouse.getBestMove(mode, eps);
      bestMoveCat = cat.getBestMove(mode, eps);   

      mouse.move(bestMoveMouse);
      cat.move(bestMoveCat);


      catNewState = cat.getInternalState();
      mouseNewState = mouse.getInternalState();


      // the new state from which we can get the reward and the max value
      mouseReward = mouseNewState->getR();
      catReward = catNewState->getR();


      //Bellman equation for mouse   (-testReward)
      mouseNewVal = mouseOldState->getDirectionValue(mode,bestMoveMouse) + alpha * (mouseReward + discount * mouseNewState->maxValue() - mouseOldState->getDirectionValue(mode, bestMoveMouse));
      mouseOldState->setDirectionValue(mode,bestMoveMouse, mouseNewVal);


      // important is the -1 infront of reward reward for the cat
      catNewVal = catOldState->getDirectionValue(mode,bestMoveCat) + alpha * (catReward + discount * catNewState->maxValue() - catOldState->getDirectionValue(mode,bestMoveCat));
      catOldState->setDirectionValue(mode,bestMoveCat,catNewVal);

      //Q <- Q'
      mouseOldState =  mouse.getInternalState();
      catOldState = cat.getInternalState();

    }while (catReward == 0);

    arr[i] = -catReward;
  }
  
  printResults(repetitions, arr);
}

void doubleQLearning(){
  World world(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS);
  Cat cat(ROWS-2, COLUMNS-2, ROWS,COLUMNS);

  Location* curLoc;
  double alpha = 0.1;
  double discount = 0.9;
  double eps = 0.8;
  int repetitions = 1000;
  int mode = 1; // 0 for Q-learning + Sarsa, 1 for double Q-learning 
  int binRan; // needed for the coinflip in double Q-learning
  double *arr = (double*) calloc (repetitions,sizeof(double));

  int mROld, mCOld, mRNew, mCNew; // mouse column and row
  int cROld, cCOld, cRNew, cCNew; // cat column and row

  // keeps track of the best move for the agent
  char bestMoveMouse;
  char bestMoveCat;

  // keeps track of the reward of the agents (mousseReward = -catReward)
  int mouseReward;
  int catReward;

  // keeps track of the states of the mouse 
  State *mouseNewState; //State_t+1
  State *mouseOldState; //State_t

  // keeps track of the states of the cat
  State *catNewState; //State_t+1
  State *catOldState; //State_t

  // the new Q value 
  double mouseNewVal;
  double catNewVal;

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

    mouseOldState =  mouse.getInternalState();
    catOldState = cat.getInternalState();

    do // reward will stay 0 until either the mouse got eaten or managed to esceape 
    {
      // the current agent state Q
      bestMoveMouse = mouse.getBestMove(mode,eps);
      bestMoveCat = cat.getBestMove(mode,eps);   

      
      mouse.move(bestMoveMouse);
      cat.move(bestMoveCat);

      catNewState = cat.getInternalState();
      mouseNewState = mouse.getInternalState();


      // the new state from which we can get the reward and the max value
      mouseReward = mouseNewState->getR();
      catReward = catNewState->getR();

      // binRan can either be 0 or 1 for mouse 
      binRan = rand()%2;

      // double Q update mouse 
      mouseNewVal = mouseOldState->getDirectionValue(binRan,bestMoveMouse) + 
                    alpha * (mouseReward + discount * mouseNewState->getDirectionValue(!binRan,mouseNewState->getBestMove(binRan)) -
                    mouseOldState->getDirectionValue(binRan,bestMoveMouse));

      mouseOldState->setDirectionValue(binRan,bestMoveMouse, mouseNewVal);
      
      // binRan can either be 0 or 1 for cat
      binRan = rand()%2;    

      // double Q update cat
      catNewVal = catOldState->getDirectionValue(binRan,bestMoveCat) + 
                    alpha * (catReward + discount * catNewState->getDirectionValue(!binRan,catNewState->getBestMove(binRan)) -
                    catOldState->getDirectionValue(binRan,bestMoveCat));

      catOldState->setDirectionValue(binRan,bestMoveCat, catNewVal);

      // S <- S'
      mouseOldState =  mouse.getInternalState();
      catOldState = cat.getInternalState();

    }while (catReward == 0);
    arr[i] = -catReward;
  }
  printResults(repetitions, arr);
}


void runAlgorithms(){
  int algotithm = 0;  // 0 = SARSA, 1 = Q-learning, 2 = double Q-learning





}







int main(int argc, char const *argv[])
{
  srand(time(0));
  // qLearning();
  // doubleQLearning();
  SARSA();
  return 0;
}