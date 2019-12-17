#include "construction.hh"
#include <cstdlib>
#include <time.h>
#include<ctime>
#include <iostream>

std::vector<coordonnee> range(int r,coordonnee c)
{
    std::vector<coordonnee> res;
     for (int i = -r+c._x; i <= r+c._x; i++)
    {
        int max = ((-r < (-i - r)) ? (-i - r) : -r);
        int min = ((r > (-i + r)) ? (-i + r) : r);
        for (int j = max+c._y; j <= min+c._y; j++)
        {
            int k = -i - j;
            coordonnee c;c._x=i;c._y=j;c._z=k;
            res.push_back(c);
        }
    }
    return res;
}

Maison::Maison(int r,std::string nom):_orientation(90){
    std::srand(std::time(nullptr));
    auto ra =range(r,coordonnee(0,0,0));
    _coord._x = (rand() % (r * 2) + 1) - r;
    _coord._z = (rand() % (r * 2) + 1) - r;
    _coord._y = -_coord._x-_coord._z;
    if(nom!=""){ _nom=nom;}
}
Maison::Maison(coordonnee c, std::string nom) : _coord(c), _orientation(90) {
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
    os<<"Nom: "+_nom+" Coordonées: "<<_coord<<std::endl;
    if(_routes.size()>0){
        os<<"\t\tRoutes:\n";
        os << "\t\t\t";
        for (auto const &i : _routes)
        {
            os<<"#->"<< i <<" ";
        }
        os<<"\n";
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


//-----------------------------------------------------------------------------------------------------------


int distance(coordonnee c1,coordonnee c2){
    return (std::abs(c2._x - c1._x)+(std::abs(c2._y - c1._y))+(std::abs(c2._z - c1._z))) / 2;
}
