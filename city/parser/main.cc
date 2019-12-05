#include "parser.hpp"
#include "scanner.hh"
#include "driver.hh"
#include "graphe.hh"

#include <iostream>
#include <fstream>

#include <cstring>

int main( int  argc, char* argv[]) {
    Driver driver;
    std::ifstream fichier("../exemples/01.city");

    Scanner scanner(fichier, std::cout);
    yy::Parser parser(scanner, driver);

    Graphe g;
    g.initMatrice();
    g.affichageMatrice();
    coordonnee coo,coor;
    coo._x=0;coo._y=0;coo._z=0;
    coor._x = 1;
    coor._z = 0;
    coor._y = -coor._x - coor._z;
    Maison m(coo);Maison m2(coor);
    
    
    parser.parse();

    return 0;
}
