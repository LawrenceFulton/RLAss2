#include "main.h"

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
    std::cout << "__________________epoche "<< i << "____________"<< std::endl;
    mouse.setCoordinates(0,0);
    cat.setCoordinates(ROWS-2, COLUMNS-2); // will be just in front of the exit


    do // reward will stay 0 until either the mouse got eaten or managed to esceape 
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
      mouseReward = mouseNewState->getR();
      catReward = catNewState->getR();


      //Bellman equation for mouse   (-testReward)
      mouseNewVal = mouseOldState->getDirectionValue(bestMoveMouse) + alpha * (mouseReward + discount * mouseNewState->maxValue() - mouseOldState->getDirectionValue(bestMoveMouse));
      mouseOldState->setDirectionValue(bestMoveMouse, mouseNewVal);


      // important is the -1 infront of reward reward for the cat
      catNewVal = catOldState->getDirectionValue(bestMoveCat) + alpha * (catReward + discount * catNewState->maxValue() - catOldState->getDirectionValue(bestMoveCat));
      catOldState->setDirectionValue(bestMoveCat,catNewVal);


    }while (catReward == 0);

    arr[i] = -catReward;
  }
  
  int sum = 0;
  std::cout << "rewards123:" << std::endl;
  for (size_t i = 0; i < repetitions; i++)
  {

    if(arr[i] == 1) sum +=1;
    

    std::cout << arr[i] << ", ";
  }



  std::cout << "\nMouse wins " << double(sum) / repetitions << "percentage of the time " << std::endl; 

  return;

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



