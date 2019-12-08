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
void Maison::sortieflux(std::ostream & os)const{
    os<<"x: "+std::to_string(_coord._x)+" y: "+std::to_string(_coord._y)+" z: "+std::to_string(_coord._z)+"\n";
    os<<"\t\tRoutes :\n";
    for(auto const & i:_routes){
        os << "\t\tx: " + std::to_string(i._x) + " y: " + std::to_string(i._y) + " z: " + std::to_string(i._z) + "\n";
    }
}
std::ostream &operator<<(std::ostream &os, Maison const &m){
    m.sortieflux(os);
    return os;
}
void Maison::ajoutRoute(coordonnee c){
    if(!dejaRelie(c)){
        _routes.push_back(c);
    }else{
        std::cout<<"Maison "<<(*this)<<"possède déjà une route vers cette maison"<<std::endl;
    }
}