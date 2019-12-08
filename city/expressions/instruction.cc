#include "instrution.hh"
bool instruction::estoccupe(coordonnee c){
    for (auto &i : _maisons)
    {
        if (i.getCoord()==c){
            return true;
        }
    }
    return false;
}
void instruction::ajoutMaison(){
    Maison m;
    if(!estoccupe(m.getCoord())){
        _nbsommet++;
        _maisons.push_back(m);
    }

}
void  instruction::ajoutMaison(coordonnee c){
    if(!estoccupe(c)){
         _nbsommet++;
        _maisons.push_back(Maison(c));
    }
    
}

void instruction::ajoutRoute(coordonnee src,coordonnee dst){
    for(auto & i:_maisons){
        if(i.getCoord()==src){
            i.ajoutRoute(dst);
        }
    }
}

int instruction::indiceMaison(coordonnee c){
    for(int i=0;i<(int)_maisons.size();i++){
        if(_maisons[i].getCoord()==c){
            return i;
        }
    }
    return -1;
}
// 
void instruction::exec(int rayon){
    _rayon=rayon;
    if(!_estConstruit){
        _graphe.setnbSommet((int)_maisons.size());
        _graphe.initMatrice();
        for(auto const & i:_maisons){
            for(auto const j:i.getRoute()){
                _graphe.ajoutArc(indiceMaison(i.getCoord()),indiceMaison(j));
            }
        }
        _estConstruit=true;
    }else{
        _graphe.initMatrice();
    }
}

void instruction::affichageVille(){
    std::cout<<"Rayon: "<<std::to_string(_rayon)<<std::endl;
    std::cout << "NBSommets: " << std::to_string(_nbsommet) << std::endl;
    std::cout<<"Maisons: "<<std::endl;
    for(auto const & i:_maisons){
        i.sortieflux(std::cout);
        std::cout<<std::endl;
    }
    std::cout<<"Matrice d'adjacence: nbSommet: "<<_graphe.getnbSommet()<<std::endl;
    _graphe.affichageMatrice();
}