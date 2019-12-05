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

bool Maison::operator==(Maison const & m){
    return (_coord._x == m._coord._x) && (_coord._y == m._coord._y) && (_coord._z == m._coord._z);
}