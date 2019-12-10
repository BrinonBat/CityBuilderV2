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
    Maison m(_rayon);
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

void instruction::tournerMaison(int i, bool horaire){
    if(horaire){
        _maisons[i - 1].setOrientation(_maisons[i - 1].getOrientation()+60);
    }else{
        _maisons[i - 1].setOrientation(_maisons[i - 1].getOrientation() - 60);
    }
}
void instruction::tournerMaison(coordonnee c, bool horaire){
    if (horaire){
        _maisons[indiceMaison(c)].setOrientation(_maisons[indiceMaison(c)].getOrientation() + 60);
    }
    else{
        _maisons[indiceMaison(c)].setOrientation(_maisons[indiceMaison(c)].getOrientation() - 60);
    }
}
void instruction::orienterMaison(int i,int r){
    _maisons[i - 1].setOrientation(r);
}
void instruction::orienterMaison(coordonnee c, int r){
    _maisons[indiceMaison(c)].setOrientation(r);
}

void instruction::ajoutRoute(coordonnee src,coordonnee dst){
    for(auto & i:_maisons){
        if(i.getCoord()==src){
            i.ajoutRoute(dst);
        }
    }
}
void instruction::ajoutRoute(int src, coordonnee dst){
    _maisons[src-1].ajoutRoute(dst);
}
void instruction::ajoutRoute(coordonnee src, int dst){
    for (auto &i : _maisons){
        if (i.getCoord() == src){
            i.ajoutRoute(_maisons[dst-1].getCoord());
        }
    }
}
void instruction::ajoutRoute(int src, int dst){
    _maisons[src-1].ajoutRoute(_maisons[dst-1].getCoord());
}

void instruction::detruireMaison(int i){
	if((unsigned int)i<=_maisons.size()){
		//suppression des routes sortantes
		_maisons[i-1].clearRoutes();
		//suppression des routes entrantes
		for(auto m : _maisons){
			m.retireRoute(_maisons[i-1].getCoord());
		}
		//suppression de la maison
		_maisons.erase(_maisons.begin()+(i-1));
	}
}

void instruction::detruireMaison(coordonnee c){
	for(unsigned int i(0);i<=_maisons.size();++i){
		if(_maisons[i].getCoord()==c){
			detruireMaison(i);
			break;
		}
	}
}
/*
void instruction::detruireRoute(int srx,int dst){
	_maisons[src-1].retireRoute(_maisons[dst-1].getCoord());
}
void instruction::detruireRoute(int srx, coordonnee dst){

}
void instruction::detruireRoute(coordonnee srx, int dst){
}
void instruction::detruireRoute(coordonnee srx, coordonnee dst){
}
*/










int instruction::indiceMaison(coordonnee c){
    for(int i=0;i<(int)_maisons.size();i++){
        if(_maisons[i].getCoord()==c){
            return i;
        }
    }
    return -1;
}

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
        std::cout<<"indice: "<<indiceMaison(i.getCoord())<<" ";
        i.sortieflux(std::cout);
        std::cout<<std::endl;
    }
    std::cout<<"Matrice d'adjacence: nbSommet: "<<_graphe.getnbSommet()<<std::endl;
    _graphe.affichageMatrice();
}
