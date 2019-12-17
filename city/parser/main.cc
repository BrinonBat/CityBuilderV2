#include "parser.hpp"
#include "scanner.hh"
#include "driver.hh"
#include "graphe.hh"
#include "instrution.hh"

#include <iostream>
#include <fstream>

#include <cstring>


int main( int  argc, char* argv[]) {
    Driver driver;
    std::ifstream fichier("../TESTS/city4");
    instruction ville;
    Scanner scanner(fichier, std::cout);
    yy::Parser parser(scanner, driver,ville);

    parser.parse();

    ville.affichageVille();
    return 0;
}
