#include "graphe.hh"
#include <sstream>
#include <iostream>
#include <queue>

Graphe::Graphe(): nbSommet(0), oriente(false){
}
Graphe::~Graphe(){

}

void Graphe::initMatrice(){
  for (int i=0; i<nbSommet; ++i){
    for (int j=0; j<nbSommet; ++j){
      if(matrice[i][j]!=1){
        matrice[i][j]=0;
      }
    }
  }
  std::cout << "Graphe initialisé " <<std::endl;
}

void Graphe::ajoutArc(int origine,int destination, int c){
  if (!oriente) matrice[destination-1][origine-1] = c;
  matrice[origine-1][destination-1] = c;
}


void Graphe::affichageMatrice(){
  std::vector<int> largeurColonne;

  for (int i=0; i<nbSommet; ++i){    

    int max=0;
    for (int j=0; j<nbSommet; ++j){
      std::ostringstream tmp;
      tmp << matrice[j][i];
      if (tmp.tellp() > max) {max=tmp.tellp();}
    }
    largeurColonne.push_back(max);
  }
  std::cout << "    ";

  for (int i=0; i<nbSommet; ++i)
    printf("%*d  ",largeurColonne[i],i+1);
  std::cout << std::endl; 
  for (int i=0; i<nbSommet; ++i){
    printf("%3d|",i+1);
    for (int j=0; j<nbSommet; ++j){
      if(j>=0 && (j)<9){
        printf("%*.*d  ",largeurColonne[j],largeurColonne[j],matrice[i][j]);
    }else{
      printf("%*.*d   ",largeurColonne[j],largeurColonne[j],matrice[i][j]);
    }

    }
    std::cout << std::endl;
  }
}


