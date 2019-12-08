#include "instrution.hh"
bool instruction::estoccupe(coordonnee c){
    for (auto &i : _maisons)
    {
        if (i.getCoord._x == c._x && i.getCoord._y==c._y && i.getCoord._z==c._z){
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
        if(i.getCoord==src){
            i.ajoutRoute(dst);
        }
    }
}



void instruction::exec(int rayon){
    _rayon=rayon;
    for(auto const & i:_maisons){
        
    }
}