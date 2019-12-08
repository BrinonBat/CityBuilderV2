#pragma once
#include "construction.hh"
#include "graphe.hh"
#include <vector>
//class qui contient les instruction de construction qui est lu dans le parser
//elle contient le graphe/matrice d'adjacence et la liste des maisons
class instruction{
private:
    Graphe _graphe;
    int _rayon;
    int _nbsommet;
    bool _estConstruit;//retourne true si la ville est construite
    std::vector<Maison> _maisons;
public:
    instruction():_nbsommet(0),_estConstruit(false){};
    instruction(const instruction & autre)=default;
    //accesseurs
    Graphe getGraphe()const{return _graphe;}
    int getRayon()const{return _rayon;}
    int getNbsommet()const{return _nbsommet;}
    std::vector<Maison> getMaisons()const{return _maisons;}
    
    bool estoccupe(coordonnee c);//retourne true si cet emplacement est occupé
    void ajoutMaison();//ajout d'une maison avec une position aléatoire dans la lsite
    void ajoutMaison(coordonnee c);//ajout d'une maison avec coord dans la liste
    void ajoutRoute(coordonnee src,coordonnee dst);
    int indiceMaison(coordonnee c);//retourne l'indice de la maison situé aux coordonée données
    
    void exec(int rayon);//construit _graphe en fonction de _maisons et set _estconstruit a true

    void affichageVille();


};