#pragma once
#include "construction.hh"
#include "graphe.hh"
#include <vector>

class instruction{
private:
    Graphe _graphe;
    int rayon;
    int _nbsommet;
    std::vector<Maison> _maisons;
public:
    instruction():_nbsommet(0){};
    instruction(const instruction & autre)=default;

    void setMaison( Maison const &  m);
    bool estoccupe(coordonnee c);
    void setMaison(Maison const &m,coordonnee c);

    void exec();


};