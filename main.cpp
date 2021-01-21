#include "main.h"

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
	int repetitions = 10;
	int catReward;

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
	//State *tempMouseState; //State_t=0

	State *catNewState; //State_t+1
	State *catOldState; //State_t
	//State *tempCatState;//State_t=0

	double mouseNewVal;
	double catNewVal;

	std::cout << "print internal states cat:" << std::endl;
	cat.printInteralStates();

    std::cout << "initialisation complete" << std::endl;

	for (size_t i = 0; i < repetitions; i++){
		mouse.setCoordinates(0,0);
		cat.setCoordinates(ROWS-2, COLUMNS-2); // will be just in front of the exit

		reward = 0;
		// the current mouse state and intital action selection
		mouseOldState =  mouse.getInternalState();
		oldMoveMouse = mouse.getBestMove(eps);
		
        catOldState = cat.getInternalState();
		oldMoveCat = cat.getBestMove(eps);   
        std::cout << "first selection complete" << std::endl;
		do // reward will stay 0 until either the mouse got eaten or managed to escape 
		{
			//take action and update reward and state'
			mouse.move(oldMoveMouse);
			cat.move(oldMoveCat);
            std::cout << "first move complete" << std::endl;

            //new state
			catNewState = cat.getInternalState(); 
			mouseNewState = mouse.getInternalState();
            std::cout << "new state updated" << std::endl;
			
            // the new state from which we can get the reward 
			//reward = mouseNewState->getR();
			catReward = catNewState->getR();
            std::cout << "rewards complete" << std::endl;

			// select next action from the new state
			//mouseNewState =  mouse.getInternalState();
			bestMoveMouse = mouse.getBestMove(eps);
			//catNewState = cat.getInternalState();
			bestMoveCat = cat.getBestMove(eps);   

            std::cout << "before mouse eq" << std::endl;
			//Bellman equation for mouse   (-testReward)
			mouseNewVal = mouseOldState->getDirectionValue(oldMoveMouse) + alpha * (-catReward + discount * mouseNewState->getDirectionValue(bestMoveMouse) - mouseOldState->getDirectionValue(oldMoveMouse));
			mouseOldState->setDirectionValue(bestMoveMouse, mouseNewVal);

            std::cout << "before cat eq" << std::endl;
			// important is the -1 infront of reward reward for the cat
			catNewVal = catOldState->getDirectionValue(oldMoveCat) + alpha * (catReward + discount * catNewState->getDirectionValue(bestMoveCat) - catOldState->getDirectionValue(oldMoveCat));
			catOldState->setDirectionValue(bestMoveCat,catNewVal);


            oldMoveMouse = mouse.getBestMove(eps);
            oldMoveCat = cat.getBestMove(eps);

			//update the state
			mouseOldState =  mouse.getInternalState();
			catOldState = cat.getInternalState();

            std::cout << "loop finished" << std::endl;
		}while (catReward == 0);

		arr[i] = -catReward;
	}
	
	int sum = 0;
	std::cout << "rewards SARSA:" << std::endl;
	for (size_t i = 0; i < repetitions; i++)
	{

		if(arr[i] == 1) sum +=1;

		std::cout << arr[i] << ", ";
	}

	std::cout << "\nMouse wins " << double(sum) / repetitions << " percentage of the time " << std::endl; 

	return;
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
  int repetitions = 1000;
  int testReward;

  double arr[repetitions];

  char input;
  int mROld, mCOld, mRNew, mCNew; // mouse column and row
  int cROld, cCOld, cRNew, cCNew; // cat column and row
  mouse.learnTransitions(&world);
  cat.learnTransitions(&world);

  char bestMoveMouse;
  char bestMoveCat;



  int reward;  //same reward can be used for mouse and cat (have to use it *-1)
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

    reward = 0;

    do // reward will stay 0 until either the mouse got eaten or managed to escape 
    {
      // the current mouse state 
      mouseOldState =  mouse.getInternalState();
      bestMoveMouse = mouse.getBestMove(eps);

      catOldState = cat.getInternalState();
      bestMoveCat = cat.getBestMove(eps);   

      mouse.move(bestMoveMouse);
      cat.move(bestMoveCat);


      catNewState = cat.getInternalState();
      mouseNewState = mouse.getInternalState();


      // the new state from which we can get the reward and the max value
      reward = mouseNewState->getR();
      testReward = catNewState->getR();


      //Bellman equation for mouse   (-testReward)
      mouseNewVal = mouseOldState->getDirectionValue(bestMoveMouse) + alpha * (-testReward + discount * mouseNewState->maxValue() - mouseOldState->getDirectionValue(bestMoveMouse));
      mouseOldState->setDirectionValue(bestMoveMouse, mouseNewVal);


      // important is the -1 infront of reward reward for the cat
      catNewVal = catOldState->getDirectionValue(bestMoveCat) + alpha * (testReward + discount * catNewState->maxValue() - catOldState->getDirectionValue(bestMoveCat));
      catOldState->setDirectionValue(bestMoveCat,catNewVal);

    }while (testReward == 0);

    arr[i] = -testReward;
  }
  
  int sum = 0;
  std::cout << "rewards123:" << std::endl;
  for (size_t i = 0; i < repetitions; i++)
  {

    if(arr[i] == 1) sum +=1;
    

    std::cout << arr[i] << ", ";
  }



  std::cout << "\nMouse wins " << double(sum) / repetitions << " percentage of the time " << std::endl; 

  return;

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
    //qLearning();
    SARSA();
    return 0;
}



