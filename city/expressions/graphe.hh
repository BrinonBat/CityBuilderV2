#pragma once
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <array>
#include <limits>
#include "construction.hh"
#include <memory>

const int Max = 1000;

class Graphe{
  private : 
    std::array<std::array<int,Max>, Max> matrice;
    int nbSommet;
    bool oriente;
    
  public :

    Graphe();
    ~Graphe();
    void initMatrice();

    int getnbSommet()const {return nbSommet;}
    void setnbSommet(int n){nbSommet=n;}
    void setOriente(bool o) {oriente = o;};
    std::array<std::array<int, Max>, Max> mat()const{return matrice;}
        //void ajoutArc(int,int,int); pas utile comme ya pas de poids d'arc
        void ajoutArc(int, int);
    void affichageMatrice(); 
    void parcoursProfondeur();
    void parcoursLargeur();
};
using graphePtr = std::shared_ptr<Graphe>;