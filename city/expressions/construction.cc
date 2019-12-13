#include "construction.hh"
#include <cstdlib>
#include <time.h>
#include<ctime>
#include <iostream>

Maison::Maison(int r,std::string nom):_orientation(90){
    std::srand(std::time(nullptr));
    _coord._x = (rand() % (r * 2) + 1) - 5;
    _coord._z = (rand() % (r * 2) + 1) - 5;
    _coord._y = -_coord._x-_coord._z;
    if(nom!=""){ _nom=nom;}
}
Maison::Maison(coordonnee c, std::string nom) : _coord(c), _orientation(90) {
    if (nom != ""){
        _nom = nom;
    }
}
//retravailler la sécurité ici et les verifs
Maison::Maison(int r,coordonnee c,std::string nom):_orientation(90){
	std::srand(std::time(nullptr));
    _coord._x = (rand() % (r * 2) + 1) - 5 + c._x;
    _coord._z = (rand() % (r * 2) + 1) - 5 + c._z;
    _coord._y = -_coord._x-_coord._z/* + c._y*/;
	// !!! dépassement de terrain possible.
	if (nom != ""){
        _nom = nom;
    }
}

bool Maison::operator==(Maison const & m){
    return _coord==m.getCoord();
}

void Maison::deplaceRoutes(coordonnee avant,coordonnee apres){
	for(auto &c: _routes){
		if(c==avant){
            c=apres;
		    break;
        }
	}
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
    os<<"Nom: "+_nom<<_coord;
    os<<"\t\tRoutes:\n";
    for(auto const & i:_routes){
        os << "\t\t"<<i;
    }
}

std::ostream &operator<<(std::ostream &os, Maison const &m){
    m.sortieflux(os);
    return os;
}
std::ostream &operator<<(std::ostream &os, coordonnee c){
    os<<"("+std::to_string(c._x)+","+std::to_string(c._y)+","+std::to_string(c._z)+")";
    return os;
}
void Maison::ajoutRoute(coordonnee c){
    if(!dejaRelie(c)){
        _routes.push_back(c);
    }else{
        std::cout<<"Maison "<<(*this)<<"possède déjà une route vers cette maison"<<std::endl;
    }
}
void Maison::retireRoute(coordonnee c){
	auto it=std::find(_routes.begin(),_routes.end(),c);
	if(it!=_routes.end()){
		_routes.erase(it);
	}
}
