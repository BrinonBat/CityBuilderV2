#pragma once
#include <iostream>
#include <vector>
#include <memory>
struct coordonnee{
    int _x,_y,_z;
    bool operator==(coordonnee const &c)const{
        return (_x==c._x)&&(_y==c._y)&&(_z==c._z);
    }
};

class Maison{
private:
    coordonnee _coord;
    std::vector<coordonnee> _routes;
public:
    Maison(coordonnee c):_coord(c){}
    Maison();
    coordonnee getCoord()const{return _coord;}
    std::vector<coordonnee> getRoute()const{return _routes;}
    bool dejaRelie(coordonnee const & c)const;//test si il y a deja une route vers ces coordonnées,renvoie true si oui false sinon
    void ajoutRoute(coordonnee c);//ajoute une route vers ces coordonnées
    bool operator==(Maison const & m);
};

