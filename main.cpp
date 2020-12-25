#include "main.h"


int main(int argc, char const *argv[])
{
  World *world = new World(2,2);
  // Cat *cat = new Cat(1,2,3);
  Mouse *mouse = new Mouse(0,0);
  Location *loc = world->getLocation(0,0);

  mouse->setCurrentLoc(loc);




  char input;

  while (input != 'z')
  {
    std::cin >> input; 
    std::cout << "input was " << input << std::endl;
    switch (input)
    {
    case 'w':
      std::cout << "should have gone up" <<std::endl;
      mouse->move('t');      
      break;

    case 'a':
      std::cout << "should have gone left" <<std::endl;
      mouse->move('l');
      break;

    case 's':
      std::cout << "should have gone down" <<std::endl;
      mouse->move('d');
      break;
    
    case 'd':
      std::cout << "should have gone right" <<std::endl;
      mouse->move('r');
      break;
    
    default:
      std::cout << "please try again, type z for exit" << std::endl;
    }
    mouse->printCoordinates();

  }
  



  world->printAllPossDirect();
  return 0;
}



