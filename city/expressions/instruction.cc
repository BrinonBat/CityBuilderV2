#include "instrution.hh"
bool instruction::estOccupe(coordonnee c){
	if(existe(c)){
	    for (auto &i : _maisons)
	    {
	        if (i.getCoord()==c){
	            return true;
	        }
	    }
	}
	    return false;
}
bool instruction::existe(coordonnee c){
	// if dans le graphe
	return true;
	//else return false
}

void instruction::ajoutMaison(){
    Maison m(_rayon);
    if(!estOccupe(m.getCoord())){
        _nbsommet++;
        _maisons.push_back(m);
    }

}
void instruction::ajoutMaison(std::string s){
	//verification que le nom n'est pas pris
	bool estPris(false);
	for(auto &m : _maisons){
		if(m.getNom()==s)estPris=true;
	}
	if(!estPris){
		//ajout de la maison & ajout du nom
		ajoutMaison();
		_maisons.back().setNom(s);
	}else
		std::cout<<"le nom est déjà pris! annulation de la creation de la maison "<<s<<std::endl;
}

void  instruction::ajoutMaison(coordonnee c){
    if(!estOccupe(c)){
         _nbsommet++;
        _maisons.push_back(Maison(c));
    }

}
void instruction::ajoutMaison(coordonnee c,std::string s){
	//verification que le nom n'est pas pris
	bool estPris(false);
	for(auto &m : _maisons){
		if(m.getNom()==s)estPris=true;
	}
	if(!estPris){
		//ajout de la maison & ajout du nom
		ajoutMaison(c);
		_maisons.back().setNom(s);
	}else
		std::cout<<"le nom est déjà pris! annulation de la creation de la maison "<<s<<std::endl;
}
void instruction::tournerMaison(int i, bool horaire){
    if (i < (int)_maisons.size() && i > -1)
    {
        if (horaire)
        {
            _maisons[i].setOrientation(_maisons[i].getOrientation() + 60);
        }
        else
        {
            _maisons[i].setOrientation(_maisons[i].getOrientation() - 60);
        }
    } else{
        std::cout << "Erreur la maison d'entrée à tourner n'existe pas " << std::endl;
    }
}

void instruction::orienterMaison(int i,int r){
    if(i<(int)_maisons.size() && i>-1){
        _maisons[i].setOrientation(r);
    }else{
        std::cout << "Erreur la maison d'entrée à orienter n'existe pas " << std::endl;
    }
}

void instruction::ajoutRoute(int src, int dst){
    if ((unsigned int)src < _maisons.size() && src > -1 && dst < (int)_maisons.size() && dst > -1){
        _maisons[src].ajoutRoute(_maisons[dst].getCoord());
    }else{
        std::cout << "Erreur ajoutRoute la maison d'entrée ou de sortie n'existe pas src:" << src << " dst:" << dst << std::endl;
    }
}

void instruction::detruireMaison(int i){
	if((unsigned int)i<=_maisons.size()){
		//suppression des routes sortantes
		_maisons[i].clearRoutes();
		//suppression des routes entrantes
		for(auto &m : _maisons){
			m.retireRoute(_maisons[i].getCoord());
		}
		//suppression de la maison
		_maisons.erase(_maisons.begin()+(i));
	}
}

void instruction::detruireRoute(int src,int dst){
    if ((unsigned int)src < _maisons.size() && src > -1 && dst<(int)_maisons.size() && dst>-1)
        _maisons[src].retireRoute(_maisons[dst].getCoord());
    else
        std::cout<<"Erreur detruire route la maison d'entrée ou de sortie n'existe pas src:"<<src<<" dst:"<<dst<<std::endl;
     
}


void instruction::deplaceMaison(int src, coordonnee dst){
	if((unsigned int)src<_maisons.size()&& src>-1){
		deplaceMaison(_maisons[src].getCoord(),dst);
    }else{
        std::cout<<"L'indice "+std::to_string(src)+" n'existe pas "<<std::endl;
    }
}

void instruction::deplaceMaison(coordonnee src, coordonnee dst){
	if(!estOccupe(dst)){
		//redirection des routes
		for(auto &m : _maisons){
			m.deplaceRoutes(src,dst);
		}
		//déplacement de la maison
		_maisons[indiceMaison(src)].setCoord(dst);
	}

}

void instruction::voisinage(int i){
    if(i<(int)_maisons.size() && i>-1){
        if (_maisons[i].getRoute().size()>0){
            std::cout << "voisinage " << i << " - ";
            for (auto const &j : _maisons[i].getRoute()){
                std::cout<<j<<" distance relative -> ";
				std::cout<<((	(std::abs(_maisons[i].getCoord()._x - j._x))
								+(std::abs(_maisons[i].getCoord()._y - j._y))
						 		+(std::abs(_maisons[i].getCoord()._z - j._z))
							) / 2) <<std::endl;
            }
            std::cout<<std::endl;
        }else{
            std::cout<<"La maison "+std::to_string(i)+" n'a pas de voisins"<<std::endl;
        }
    }
}


int instruction::indiceMaison(coordonnee c){
    for(int i=0;i<(int)_maisons.size();i++){
        if(_maisons[i].getCoord()==c){
            return i;
        }
    }
    std::cout<<"Il n'y a pas de maison à ces coordonées"<<c<<std::endl;
    return -1;
}

int instruction::indiceMaison(std::string s)
{
    for (int i = 0; i < (int)_maisons.size(); i++)
    {
        if (_maisons[i].getNom() == s)
        {
            return i;
        }
    }
    std::cout << "Il n'y a pas de maison nommée ainsi" << s << std::endl;
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
