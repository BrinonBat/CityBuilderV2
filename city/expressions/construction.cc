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
    return _coord==m.getCoord();
}
bool Maison::dejaRelie(coordonnee const &c)const{
    for(auto const &i:_routes){
        if(i==c){
            return true;
        }
    }
    return false;
}

void Maison::ajoutRoute(coordonnee c){
    if(!dejaRelie(c)){
        _routes.push_back(c);
    }
}