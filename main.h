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
#include <string.h>


#include <iostream>
#include <iomanip>

#define ROWS 8
#define COLUMNS 8


//might not be needed
#define MOUSE 0
#define CAT 1


#define QLEARN 0
#define DOUBLEQ 1
#define SARSA 2
#define RANDOM 3

#define EPS 0
#define UCB 1

#endif 
