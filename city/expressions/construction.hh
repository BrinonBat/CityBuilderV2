#pragma once
#include <iostream>
#include <vector>
#include <memory>
struct coordonnee{
    int _x,_y,_z;
};

class Maison{
private:
    coordonnee _coord;
    std::vector<coordonnee> _arcs;
public:
    Maison(coordonnee c):_coord(c){}
    Maison();
};