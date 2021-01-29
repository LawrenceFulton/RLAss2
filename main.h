#ifndef MAIN_H
#define MAIN_H

#include "code/header/Agent.h"
#include "code/header/Cat.h"
#include "code/header/Mouse.h"
#include "code/header/World.h"
#include "code/header/State.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iterator>
#include <fstream>


#define ROWS 5
#define COLUMNS 5


//might not be needed
#define MOUSE 0
#define CAT 1

#define SARSA 0
#define QLEARN 1
#define DOUBLEQ 2
#define RANDOM 3

#define EPS 0
#define UCB 1

#endif 
