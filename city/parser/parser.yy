%skeleton "lalr1.cc"
%require "3.0"

%defines
%define parser_class_name { Parser }
%define api.value.type variant
%define parse.assert

%locations

%code requires{
    #include "contexte.hh"
    #include "expressionBinaire.hh"
    #include "expressionUnaire.hh"
    #include "constante.hh"
    #include "variable.hh"
    #include "expression.hh"
    #include "graphe.hh"
    #include "construction.hh"
    #include "instrution.hh"
    #include <iostream>

    class Scanner;
    class Driver;
    class instruction;
}

%parse-param { Scanner &scanner }
%parse-param { Driver &driver }
%parse-param { instruction &ville }

%code{
    #include <iostream>
    #include <string>

    #include "scanner.hh"
    #include "driver.hh"

    #undef  yylex
    #define yylex scanner.yylex
}

%token                  NL
%token <float>          NUMBER
%token                  build
%token                  maison
%token                  route
%token                  arrow
%token                  comcourt
%token                  com
%token                  horaire
%token                  turn
%token                  orienter orientation
%token                  destroy
%token                  deplacer
%token                  position
%token                  voisinage voisin
%token                  indmaison
%token                  degree
%token                  coloriser couleur
%token<std::string>		nom variable couleurhexa

%token<bool>            occupe vide
%token                  non
%token                  sicond
%token                  tantque
%token                  repeter
%token                  fonctionvoid
%token                  sinon
%token                  fois


%type <int>             indice expression
%type<ExpressionPtr>    operation
%type <coordonnee>      coordonnee
%type<bool>             senshoraire
%left '-' '+'
%left '*' '/'
%precedence  NEG

%%
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////
programme:
    instruction NL programme
    | instruction{
        YYACCEPT;
    }
instruction:
     build init NL traitements '}' {
        std::cout<<"Fin de la construction"<<std::endl;
        ville.exec();
    }
    | build init NL traitements '}' NL {
        std::cout<<"Fin de la construction"<<std::endl;
        ville.exec();
    }
init:
    '(' expression ')' '{'{
        ville.setRayon($2);
    }
    | '{' {
        if(!ville.estConstruit()){
            ville.setRayon(5);
        }
    }
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////
traitements:
    traitement NL traitements
    |traitement NL

traitement:
        %empty
        | operation  {std::cout << "#-> " << $1 << std::endl;}
		| maison maisTrait
        | route routeTrait
        | com {std::cout<<"----------------------------------------------Commentaire"<<std::endl;}
        | turn turnTrait
        | orienter orienterTrait
        | orientation orientationTrait
        | destroy destroyTrait
        | deplacer deplacerTrait
        | position indice {
            std::cout<<"Position maison["<<$2<<"] ";
            std::cout<<ville.getMaisons()[$2].getCoord()<<std::endl;
        }
        | position nom {
            std::cout<<"Position "+$2;
            std::cout<<ville.getMaisons()[ville.indiceMaison($2)].getCoord()<<std::endl;
        }
        | voisinage voisinageTrait
        | affectation
        | coloriser coloriserTrait
        | couleur couleurTrait
		| voisin voisinTrait

maisTrait:
		%empty {
		//construire maison à un emplacement aléatoire
			std::cout<<"Maison ok"<<std::endl;
			ville.ajoutMaison("");
		}

		| nom {
		//construire maison à un emplacement aléatoire
			std::cout<<"Maison nommée "<<std::endl;
			ville.ajoutMaison($1);
		}
		| coordonnee {
		// construire maison selon coordonées
			std::cout<<"Maison "<<$1<<std::endl;
			ville.ajoutMaison($1,"");
		}
		| nom coordonnee {
		//construire maison nom selon coordonnées
			std::cout<<"Maison "<<$1<<" "<<$2<<std::endl;
			ville.ajoutMaison($2,$1);
		}

routeTrait:
	coordonnee arrow coordonnee  {
		std::cout<<"Route  "<<$1<<" -> "<<$3<<std::endl;
		ville.ajoutRoute(ville.indiceMaison($1),ville.indiceMaison($3));

	}
	| coordonnee arrow indice  {
		std::cout<<"Route "<<$1<<" -> "<<$3<<std::endl;
		ville.ajoutRoute(ville.indiceMaison($1),$3);

	}
	| indice arrow indice  {
		std::cout<<"Route "<<$1<<" -> "<<$3<<std::endl;
		ville.ajoutRoute($1,$3);

	}
	| indice arrow coordonnee  {
		std::cout<<"Route "<<$1<<" -> "<<$3<<std::endl;
		ville.ajoutRoute($1,ville.indiceMaison($3));

	}
	| indice arrow nom  {
		std::cout<<"Route "<<$1<<" -> "<<$3<<std::endl;
		ville.ajoutRoute($1,ville.indiceMaison($3));

	}
	| nom arrow indice  {
		std::cout<<"Route "<<$1<<" -> "<<$3<<std::endl;
		ville.ajoutRoute(ville.indiceMaison($1),$3);

	}
	| nom arrow nom  {
		std::cout<<"Route  "<<$1<<" -> "<<$3<<std::endl;
		ville.ajoutRoute(ville.indiceMaison($1),ville.indiceMaison($3));

	}
	| coordonnee arrow nom  {
		std::cout<<"Route  "<<$1<<" -> "<<$3<<std::endl;
		ville.ajoutRoute(ville.indiceMaison($1),ville.indiceMaison($3));

	}
	| nom arrow coordonnee  {
		std::cout<<"Route  "<<$1<<" -> "<<$3<<std::endl;
		ville.ajoutRoute(ville.indiceMaison($1),ville.indiceMaison($3));

	}

turnTrait:
	coordonnee senshoraire {
   		std::cout<<"Tourner"<<std::endl;
   		ville.tournerMaison(ville.indiceMaison($1),$2);
   	}
   	|indice senshoraire {
   		std::cout<<"Tourner"<<std::endl;
   		ville.tournerMaison($1,$2);
   	}
   	| nom senshoraire {
   		std::cout<<"Tourner"<<std::endl;
   		ville.tournerMaison(ville.indiceMaison($1),$2);
   	}

orienterTrait:
	coordonnee expression degree {
		std::cout<<"Orienter"<<std::endl;
		ville.orienterMaison(ville.indiceMaison($1),$2);
	}
	| nom expression degree {
		std::cout<<"Orienter"<<std::endl;
		ville.orienterMaison(ville.indiceMaison($1),$2);
	}
	| indice expression degree {
		std::cout<<"Orienter"<<std::endl;
		ville.orienterMaison($1,$2);
	}

orientationTrait:
	coordonnee {
		std::cout<<"Orientation de Maison"<<$1<<" - "
			<<ville.getMaisons()[ville.indiceMaison($1)].getOrientation()<<std::endl;
	}
	|nom {
		std::cout<<"Orientation de Maison"<<$1<<" - "
			<<ville.getMaisons()[ville.indiceMaison($1)].getOrientation()<<std::endl;
	}
	| indice {
		std::cout<<"Orientation de Maison"<<$1<<" - "
			<<ville.getMaisons()[$1].getOrientation()<<std::endl;
	}

destroyTrait:
	coordonnee {
	   std::cout<<"Detruire maison "<<$1<<std::endl;
	   ville.detruireMaison(ville.indiceMaison($1));
   }
   | indice {
	   std::cout<<"Detruire maison "<<$1<<std::endl;
	   ville.detruireMaison($1);
   }
   | nom {
	   std::cout<<"Detruire maison "<<$1<<std::endl;
	   ville.detruireMaison(ville.indiceMaison($1));
   }
   | coordonnee arrow coordonnee {
	   std::cout<<"Detruire route "<<$1<<" -> "<<$3<<std::endl;
	   ville.detruireRoute(ville.indiceMaison($1),ville.indiceMaison($3));
   }
   | coordonnee arrow indice {
		std::cout<<"Detruire route "<<$1<<" -> "<<$3<<std::endl;
	   ville.detruireRoute(ville.indiceMaison($1),$3);
   }
   | indice arrow coordonnee {
		std::cout<<"Detruire route "<<$1<<" -> "<<$3<<std::endl;
	   ville.detruireRoute($1,ville.indiceMaison($3));
   }
   | indice arrow indice {
		std::cout<<"Detruire route "<<$1<<" -> "<<$3<<std::endl;
	   ville.detruireRoute($1,$3);
   }
   |  indice arrow nom {
		std::cout<<"Detruire route "<<$1<<" -> "<<$3<<std::endl;
	   ville.detruireRoute($1,ville.indiceMaison($3));
   }
   |  nom arrow indice {
		std::cout<<"Detruire route "<<$1<<" -> "<<$3<<std::endl;
	   ville.detruireRoute(ville.indiceMaison($1),$3);
   }
   |  nom arrow nom {
		std::cout<<"Detruire route "<<$1<<" -> "<<$3<<std::endl;
	   ville.detruireRoute(ville.indiceMaison($1),ville.indiceMaison($3));
   }
   |  coordonnee arrow nom {
	   std::cout<<"Detruire route "<<$1<<" -> "<<$3<<std::endl;
	   ville.detruireRoute(ville.indiceMaison($1),ville.indiceMaison($3));
   }
   |  nom arrow coordonnee {
	   std::cout<<"Detruire route "<<$1<<" -> "<<$3<<std::endl;
	   ville.detruireRoute(ville.indiceMaison($1),ville.indiceMaison($3));
   }
deplacerTrait:
   coordonnee arrow coordonnee {
  	std::cout<<"Deplacer maison "<<$1<<" -> "<<$3<<std::endl;
  	ville.deplaceMaison($1,$3);
  }
  |indice arrow coordonnee {
  	std::cout<<"Deplacer maison "<<$1<<" -> "<<$3<<std::endl;
  	ville.deplaceMaison($1,$3);
  }
  |nom arrow coordonnee {
  	std::cout<<"Deplacer maison "<<$1<<" -> "<<$3<<std::endl;
  	ville.deplaceMaison(ville.indiceMaison($1),$3);
  }

voisinageTrait:
  coordonnee {
	  ville.voisinage(ville.indiceMaison($1));
  }
  | indice {
	  ville.voisinage($1);
  }
  | nom {
	  ville.voisinage(ville.indiceMaison($1));
  }

coloriserTrait:
  coordonnee couleurhexa {
	  ville.coloriser(ville.indiceMaison($1),$2);
  }
  | indice couleurhexa {
	  ville.coloriser($1,$2);
  }
  | nom couleurhexa {
	  ville.coloriser(ville.indiceMaison($1),$2);
  }
  | variable couleurhexa {
	  ville.coloriser(((int)driver.getVariable($1))-1,$2);
  }
  | coordonnee '(' expression ',' expression ',' expression ')' {
	  ville.coloriser(ville.indiceMaison($1),ville.intTohexa($3,$5,$7));
  }
  | indice '(' expression ',' expression ',' expression ')' {
	  ville.coloriser($1,ville.intTohexa($3,$5,$7));
  }
  | nom '(' expression ',' expression ',' expression ')' {
	  ville.coloriser(ville.indiceMaison($1),ville.intTohexa($3,$5,$7));
  }
  | variable '(' expression ',' expression ',' expression ')' {
	  ville.coloriser(((int)driver.getVariable($1))-1,ville.intTohexa($3,$5,$7));
  }

couleurTrait:
  coordonnee {
	  ville.afficheCouleur(ville.indiceMaison($1));
  }
  | indice {
	  ville.afficheCouleur($1);
  }
  | nom {
	  ville.afficheCouleur(ville.indiceMaison($1));
  }

voisinTrait:
  coordonnee expression {
	  ville.voisin($1,$2);
  }
  | indice expression {
	  ville.voisin($1,$2);
  }
  | nom expression {
	  ville.voisin($1,$2);
  }
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////
senshoraire:
    horaire{
        std::cout<<"horaire";
        $$=true;
    }
    | '!' horaire{
        std::cout<<"!horaire";
        $$=false;
    }

indice:
    indmaison '[' NUMBER ']' {
        $$=$3-1;
    }

coordonnee:
        '(' expression ',' expression ',' expression ')' {
            $$._x = $2;
            $$._y = $4;
            $$._z = $6;
            }

expression:
    operation {
        $$= static_cast<int>($1->calculer(driver.getContexte()));
    }

affectation:
    variable '=' operation {
        try {
            double val = $3->calculer(driver.getContexte());
            driver.setVariable($1, val);
            std::cout << "#-> " << $1 << " = " << val << std::endl;
        } catch(const std::exception& err) {
            std::cerr << "#-> " << err.what() << std::endl;
        }
    }


operation:
    NUMBER {
        $$ = std::make_shared<Constante>($1);
    }
    | variable {
        $$ = std::make_shared<Variable>($1);
    }
    | '(' operation ')' {
        $$ = $2;
    }
    | operation '+' operation {
        $$ = std::make_shared<ExpressionBinaire>($1, $3, OperateurBinaire::plus);
    }
    | operation '-' operation {
        $$ = std::make_shared<ExpressionBinaire>($1, $3, OperateurBinaire::moins);
    }
    | operation '*' operation {
        $$ = std::make_shared<ExpressionBinaire>($1, $3, OperateurBinaire::multiplie);
    }
    | operation '/' operation {
        $$ = std::make_shared<ExpressionBinaire>($1, $3, OperateurBinaire::divise);
    }
    | '-' operation %prec NEG {
        $$ = std::make_shared<ExpressionUnaire>($2, OperateurUnaire::neg);
    }

%%

void yy::Parser::error( const location_type &l, const std::string & err_msg) {
    std::cerr << "Erreur : " << l << ", " << err_msg << std::endl;
}
