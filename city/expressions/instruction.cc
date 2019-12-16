#include "instrution.hh"
#include <sstream>
#include <ctime>
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
    // test toutes les coordonnées qui sont correcte et return true si c est égale à l'une d'entre elles
	for(int i=(-_rayon);i<=_rayon;i++){
        int max = ((-_rayon < (-i - _rayon)) ? (-i - _rayon) : -_rayon);
        int min = ((_rayon > (-i + _rayon)) ? (-i + _rayon) : _rayon);
        for (int j = max; j <= min; j++) {
            int k=-i-j;
            std::cout<<c<<" "<<i<<" "<<j<<" "<<k<<std::endl;
            if(c._x==i && c._y==j && c._z==k){
                return true;
            }
        }
    }
    std::cout<<"Ces coordonnées "<<c<<" sont incorrectes"<<std::endl;
	return false;
}
bool instruction::existe(int i){
    if (i < (int)_maisons.size() && i > -1){
        return existe(_maisons[i].getCoord());
    }else{
        std::cout<<"Erreur l'indice demandé est incorrecte"<<std::endl;
        return false;
    }
}

void instruction::ajoutMaison(std::string s){
	//verification que le nom n'est pas pris
	bool estPris(false);
	for(auto &m : _maisons){
		if(m.getNom()==s && !m.getNom().empty())estPris=true;
	}
    std::cout<<std::endl;
	if(!estPris){
		//ajout de la maison & ajout du nom
        Maison m(_rayon,s);
        while(!estOccupe(m.getCoord())){
            Maison m(_rayon,s);
        }_nbsommet++;
        _maisons.push_back(m);
    }else
		std::cout<<"Erreur le nom est déjà pris! annulation de la creation de la maison "<<s<<std::endl;
}

void instruction::ajoutMaison(coordonnee c,std::string s){
	//verification que le nom n'est pas pris
	bool estPris(false);
	for(auto &m : _maisons){
        if (m.getNom() == s && !m.getNom().empty())
            estPris = true;
    }
    std::cout << std::endl;
    if(!estPris){
		//ajout de la maison & ajout du nom
        if (!estOccupe(c)) {
            _nbsommet++;
            _maisons.push_back(Maison(c,s));
        }
        else{
            std::cout << "Erreur Cet emplacement " << c << " est déjà pris" << std::endl;
        }
    }else
		std::cout<<"Erreur le nom est déjà pris! annulation de la creation de la maison "<<s<<std::endl;
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
        std::cout<<"Erreur L'indice "+std::to_string(src)+" n'existe pas "<<std::endl;
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
    // si l'indice est superieure à 0 et inférieure à la taille du vector
    if(i<(int)_maisons.size() && i>-1){
        // si il y a des arcs sortants
        if (_maisons[i].getRoute().size()>0){
            std::cout << "voisinage " << i+1 << " - ";
            for (auto const &j : _maisons[i].getRoute()){
                std::cout<<j<<" distance relative -> ";
				std::cout<<((	(std::abs(_maisons[i].getCoord()._x - j._x))
								+(std::abs(_maisons[i].getCoord()._y - j._y))
						 		+(std::abs(_maisons[i].getCoord()._z - j._z))
							) / 2) <<std::endl;
            }
        }else{
            std::cout<<"La maison "+std::to_string(i+1)+" n'a pas de voisins"<<std::endl;
        }
    }
}
void instruction::voisin(int pos, int i){
    // si l'indice est superieure à 0 et inférieure à la taille du vector
    if ((unsigned int)pos < _maisons.size() && pos > -1){
        std::srand(std::time(nullptr));
        // liste des coordonnées dans un rayon i de la maison num pos
        std::vector<coordonnee> rayon = range(i, _maisons[pos].getCoord());
        // liste des coordonées a exactement 3 de distance et dans le graphe
        std::vector<coordonnee> coordonneInrange;
        for (auto const &j : rayon)
        {
            std::cout<<j<<" "<<distance(j, _maisons[pos].getCoord())<<std::endl;
            if (distance(j, _maisons[pos].getCoord()) == i && existe(j) && !estOccupe(j))
            {
                coordonneInrange.push_back(j);
                std::cout<<"end "<<coordonneInrange.back()<<std::endl;
            }
        }
        // tirage au hasard de coordonées valides parmi coordInrange
        int m = (int)coordonneInrange.size();
        int hasard = (rand() % m);
        //ajoute la maison
        ajoutMaison(coordonneInrange[hasard],"");
        //ajoute une route de la maison nuum pos vers cette nouvelle maison
		ajoutRoute(pos,_maisons.size()-1);
		std::cout<<"La maison numéro "+std::to_string(pos)+" a un nouveau voisin crée "<<_maisons.back()<<std::endl;
	}else{
		std::cout<<"Erreur numero de maison invalide"<<std::endl;
	}
}
void instruction::voisin(coordonnee c, int i){
	voisin(indiceMaison(c),i);
}

void instruction::voisin(std::string s, int i){
	voisin(indiceMaison(s),i);
}

std::string instruction::intTohexa(int r,int v, int b){
    std::stringstream ss;
    ss << std::hex << r;
    ss << std::hex << v;
    ss << std::hex << b;

    std::string s(ss.str());
    std::cout<<"#"+s<<std::endl;
    return "#"+s;
}
void instruction::coloriser(int i,std::string coul){
    if((unsigned int)i<_maisons.size()&& i>-1){
        _maisons[i].setColor(coul);
        std::cout<<"Colorisation de la maison"<<std::endl;
    }else{
        std::cout << "Erreur La maison demandé n'existe pas " << std::endl;
    }

}

void instruction::afficheCouleur(int i){
    if ((unsigned int)i < _maisons.size() && i > -1){
        std::string rouge, vert, bleu;
        rouge = _maisons[i].getColor().substr(1, 2);
        vert = _maisons[i].getColor().substr(3, 2);
        bleu = _maisons[i].getColor().substr(5, 2);
        unsigned int r,v,b;
        std::stringstream ss;
        ss << std::hex<<rouge;
        ss >> r;ss.clear();
        ss << std::hex<<vert;
        ss >> v;ss.clear();
        ss << std::hex << bleu;
        ss >> b;
        std::cout << "La couleur de la Maison["+std::to_string(i+1)+"] est ("+std::to_string(r)+","+std::to_string(v)+","+std::to_string(b)+")" << std::endl;
    }
    else{
        std::cout << "Erreur La maison demandé n'existe pas " << std::endl;
    }
}

int instruction::indiceMaison(coordonnee c){
    for(int i=0;i<(int)_maisons.size();i++){
        if(_maisons[i].getCoord()==c){
            return i;
        }
    }
    std::cout<<"Erreur Il n'y a pas de maison à ces coordonées "<<c<<std::endl;
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
    std::cout << "Erreur Il n'y a pas de maison nommée ainsi :" << s << std::endl;
    return -1;
}

void instruction::exec(){
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

//verifie si toutes les cases sont occupées dans un rayon donné autour d'une coordonnee c
bool instruction::estPlein(coordonnee c,int rayon){
	for(int x(0);x<=rayon;x++){
		for(int y(0);y<=rayon;y++){
			for(int z(0);z<=rayon;z++){
				if(!estOccupe(coordonnee(c._x+x,c._y+y,c._z+z))) return false;
				if(!estOccupe(coordonnee(c._x+x,c._y+y,c._z-z))) return false;
				if(!estOccupe(coordonnee(c._x+x,c._y-y,c._z+z))) return false;
				if(!estOccupe(coordonnee(c._x+x,c._y-y,c._z-z))) return false;
				if(!estOccupe(coordonnee(c._x-x,c._y+y,c._z+z))) return false;
				if(!estOccupe(coordonnee(c._x-x,c._y+y,c._z-z))) return false;
				if(!estOccupe(coordonnee(c._x-x,c._y-y,c._z+z))) return false;
				if(!estOccupe(coordonnee(c._x-x,c._y-y,c._z-z))) return false;
			}
		}
	}
	return true;
}
