#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
struct coordonnee{
    int _x,_y,_z;
    bool operator==(coordonnee const &c)const{
        return (_x==c._x)&&(_y==c._y)&&(_z==c._z);
    }
	coordonnee()=default;
	coordonnee(int x,int y,int z):
		_x(x),_y(y),_z(z){}
};

class Maison{
private:
    coordonnee _coord;
    int _orientation; // orientation en degrée mod 360 de la maison
    std::vector<coordonnee> _routes;
	std::string _nom,_couleur;

public:
	//constructeur
    Maison(coordonnee c,std::string nom);
    Maison(int r,std::string nom);//r est le rayon du graphe
    coordonnee getCoord()const{return _coord;}
	void setCoord(coordonnee nouv){_coord=nouv;}

    std::vector<coordonnee> getRoute()const{return _routes;}

    int getOrientation()const{return _orientation;}
    void setOrientation(int o){_orientation=(o%360);}

    void setNom(std::string const & s){_nom=s;}
	std::string getNom()const{return _nom;}

    void setColor(std::string const &s) { _couleur = s; }
    std::string getColor() const { return _couleur; }





    void deplaceRoutes(coordonnee avant,coordonnee apres);
    bool dejaRelie(coordonnee const & c)const;//test si il y a deja une route vers ces coordonnées,renvoie true si oui false sinon
    void ajoutRoute(coordonnee c);//ajoute une route vers ces coordonnées
	void clearRoutes(){_routes.clear();}
	void retireRoute(coordonnee c);//supprime une route vers ces coordonnées
    bool operator==(Maison const & m);
    void sortieflux(std::ostream & os)const;
};
std::ostream & operator<<(std::ostream & os,Maison const & m);
std::ostream &operator<<(std::ostream &os, coordonnee c);

std::vector<coordonnee> range(int r, coordonnee c); // retourne la liste de toute les coords dans le rayon r autour de c
int distance(coordonnee c1,coordonnee c2); //retourne la distance entre la maison et les coordonées c1 et c2
