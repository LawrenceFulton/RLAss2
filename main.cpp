#include "main.h"



void qLearning(){

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
  World newWorld(ROWS,COLUMNS);
  Mouse mouse(0,0,ROWS, COLUMNS);
  World* pointerW = &newWorld; 
  Location* curLoc;
  char input;
  int mR, mC; // mouse coloum and row
  int cR, cC; // cat coloum and row
  mouse.learnTransitions(pointerW);
  cR = cC = 1;
  char bestMove;

  
  mR = mouse.getR();
  mC = mouse.getC();

  int reward; 

  while (true) //should be changed until mouse is in the goal state 
  {
    bestMove = mouse.getBestMove(cR,cC,1);
    curLoc = newWorld.getLocation(mR,mC);
    mouse.move(bestMove,curLoc);
    reward = mouse.getInternalState(cR,cC).getR();
    

  }
  


  std::cout << "bestMove: " <<bestMove << std::endl; 








  // world->printAllPossDirect();
  return 0;
}



