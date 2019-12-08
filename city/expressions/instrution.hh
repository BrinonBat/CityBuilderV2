#pragma once
#include "construction.hh"
#include "graphe.hh"
#include <vector>
//class qui contient les instruction de construction qui est lu dans le parser
//elle contient le graphe/matrice d'adjacence et la liste des maisons
class instruction{
private:
    Graphe _graphe;
    int rayon;
    int _nbsommet;
    std::vector<Maison> _maisons;
public:
    instruction():_nbsommet(0){};
    instruction(const instruction & autre)=default;
    
    bool estoccupe(coordonnee c);
    void ajoutMaison();
    void ajoutMaison(coordonnee c);
    void ajoutRoute(coordonnee src,coordonnee dst);
    

    void exec();


};