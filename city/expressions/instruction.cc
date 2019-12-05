#include "instrution.hh"

instruction::setMaison(Maison const &  m){

}
instruction::estoccupe(coordonnee c){
    for (auto &i : _maisons)
    {
        if (i.getCoord._x == c._x && i.getCoord._y==c._y && i.getCoord._z==c._z){
            return false;
        }
    }
    return true;
}
instruction::setMaison(coordonnee c){
    Maison m(c);
    for(auto & i : _maisons){
        if(estoccupe(c)){
            _nbsommet++;
            _maisons.push_back(m);
        }
    }
}
instruction::exec(){}