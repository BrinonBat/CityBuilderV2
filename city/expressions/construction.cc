#include "construction.hh"
#include <cstdlib>
#include <time.h>
#include<ctime>

Maison::Maison(){
    std::srand(std::time(nullptr));
    _coord._x = (rand() % (5 * 2) + 1) - 5;
    _coord._z = (rand() % (5 * 2) + 1) - 5;
    _coord._y = -_coord._x-_coord._z;
}