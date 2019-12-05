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
    std::array<bool,Max> parcourus;
    int nbSommet;
    int rayon;
    bool oriente;
    std::vector<Maison> _sommets;
    
  public :

    Graphe();
    Graphe(int r);
    ~Graphe();
    void initMatrice();
    int getnbSommet(int i) {return nbSommet;}
    void setOriente(bool o) {oriente = o;};
    void ajoutSommet(Maison const &m);
    void ajoutArc(int,int,int); 
    void affichageMatrice(); 
    void parcoursProfondeur();
    void explorer(int s);
    void parcoursLargeur();
};
