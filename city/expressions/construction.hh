#pragma once
#include <iostream>
#include <vector>
struct coordonnee{
    int _x,_y,_z;
};
class Maison{
private:
    coordonnee _coord; // situation sommet
    std::vector<coordonnee> _routes; // arcs
public:
	//constructeur
    Maison(coordonnee c):_coord(c){}
	//getters & setters
	coordonnee get_coord()const{return _coord;}
	void ajoutRoute(Maison m2){_route.push_back(m2);} // ajoute la route (arc) vers m2
};
