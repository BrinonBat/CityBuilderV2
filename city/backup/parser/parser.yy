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
%token                  END
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
%type<std::string>      traitement traitements
%left '-' '+'
%left '*' '/'
%precedence  NEG

%%

programme:
    instruction NL programme
    | instruction{
        YYACCEPT;
    }
    | END NL{
        YYACCEPT;
    }

instruction:
     build init NL traitements '}' {
        std::cout<<"Construire "<<std::endl;
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
traitements:
    traitement NL traitements{

    }
    |
    traitement NL {

    }

traitement:
        operation  {
            std::cout << "#-> " << $1 << std::endl;
        }
        | maison {
            //construire maison à un emplacement aléatoire
                std::cout<<"Maison ok"<<std::endl;
                ville.ajoutMaison("");
        }
		| maison nom{
		   //construire maison à un emplacement aléatoire
			   	std::cout<<"Maison nommée "<<std::endl;
			   	ville.ajoutMaison($2);
	   }
        | maison coordonnee {
            // construire maison selon coordonées
                std::cout<<"Maison "<<$2<<std::endl;
                ville.ajoutMaison($2,"");
        }
		| maison nom coordonnee {
			//construire maison nom selon coordonnées
				std::cout<<"Maison "<<$2<<" "<<$3<<std::endl;
				ville.ajoutMaison($3,$2);
		}
        | route coordonnee arrow coordonnee  {
            std::cout<<"Route  "<<$2<<" -> "<<$4<<std::endl;
            ville.ajoutRoute(ville.indiceMaison($2),ville.indiceMaison($4));

        }
        | route coordonnee arrow indice  {
            std::cout<<"Route "<<$2<<" -> "<<$4<<std::endl;
            ville.ajoutRoute(ville.indiceMaison($2),$4);

        }
        | route indice arrow indice  {
            std::cout<<"Route "<<$2<<" -> "<<$4<<std::endl;
            ville.ajoutRoute($2,$4);

        }
        | route indice arrow coordonnee  {
            std::cout<<"Route "<<$2<<" -> "<<$4<<std::endl;
            ville.ajoutRoute($2,ville.indiceMaison($4));

        }
        | route indice arrow nom  {
            std::cout<<"Route "<<$2<<" -> "<<$4<<std::endl;
            ville.ajoutRoute($2,ville.indiceMaison($4));

        }
        | route nom arrow indice  {
            std::cout<<"Route "<<$2<<" -> "<<$4<<std::endl;
            ville.ajoutRoute(ville.indiceMaison($2),$4);

        }
        | route nom arrow nom  {
            std::cout<<"Route  "<<$2<<" -> "<<$4<<std::endl;
            ville.ajoutRoute(ville.indiceMaison($2),ville.indiceMaison($4));

        }
        | route coordonnee arrow nom  {
            std::cout<<"Route  "<<$2<<" -> "<<$4<<std::endl;
            ville.ajoutRoute(ville.indiceMaison($2),ville.indiceMaison($4));

        }
        | route nom arrow coordonnee  {
            std::cout<<"Route  "<<$2<<" -> "<<$4<<std::endl;
            ville.ajoutRoute(ville.indiceMaison($2),ville.indiceMaison($4));

        }
        | com {
            std::cout<<"----------------------------------------------Commentaire"<<std::endl;
        }
        | turn coordonnee senshoraire {
            std::cout<<"Tourner"<<std::endl;
            ville.tournerMaison(ville.indiceMaison($2),$3);
        }
        | turn indice senshoraire {
            std::cout<<"Tourner"<<std::endl;
            ville.tournerMaison($2,$3);
        }
        | turn nom senshoraire {
            std::cout<<"Tourner"<<std::endl;
            ville.tournerMaison(ville.indiceMaison($2),$3);
        }
        | orienter coordonnee expression degree {
            std::cout<<"Orienter"<<std::endl;
            ville.orienterMaison(ville.indiceMaison($2),$3);
        }
        | orienter nom expression degree {
            std::cout<<"Orienter"<<std::endl;
            ville.orienterMaison(ville.indiceMaison($2),$3);
        }
        | orienter indice expression degree {
            std::cout<<"Orienter"<<std::endl;
            ville.orienterMaison($2,$3);
        }
        | orientation coordonnee {
            std::cout<<"Orientation de Maison"<<$2<<" - "
                <<ville.getMaisons()[ville.indiceMaison($2)].getOrientation()<<std::endl;
        }
        | orientation nom {
            std::cout<<"Orientation de Maison"<<$2<<" - "
                <<ville.getMaisons()[ville.indiceMaison($2)].getOrientation()<<std::endl;
        }
        | orientation indice {
            std::cout<<"Orientation de Maison"<<$2<<" - "
                <<ville.getMaisons()[$2].getOrientation()<<std::endl;
        }
        | destroy coordonnee {
            std::cout<<"Detruire maison "<<$2<<std::endl;
			ville.detruireMaison(ville.indiceMaison($2));
        }
        | destroy indice {
            std::cout<<"Detruire maison "<<$2<<std::endl;
			ville.detruireMaison($2);
        }
        | destroy nom {
            std::cout<<"Detruire maison "<<$2<<std::endl;
			ville.detruireMaison(ville.indiceMaison($2));
        }
        | destroy coordonnee arrow coordonnee {
            std::cout<<"Detruire route "<<$2<<" -> "<<$4<<std::endl;
			ville.detruireRoute(ville.indiceMaison($2),ville.indiceMaison($4));
        }
        | destroy coordonnee arrow indice {
             std::cout<<"Detruire route "<<$2<<" -> "<<$4<<std::endl;
			ville.detruireRoute(ville.indiceMaison($2),$4);
        }
        | destroy indice arrow coordonnee {
             std::cout<<"Detruire route "<<$2<<" -> "<<$4<<std::endl;
			ville.detruireRoute($2,ville.indiceMaison($4));
        }
        | destroy indice arrow indice {
             std::cout<<"Detruire route "<<$2<<" -> "<<$4<<std::endl;
			ville.detruireRoute($2,$4);
        }
        | destroy indice arrow nom {
             std::cout<<"Detruire route "<<$2<<" -> "<<$4<<std::endl;
			ville.detruireRoute($2,ville.indiceMaison($4));
        }
        | destroy nom arrow indice {
             std::cout<<"Detruire route "<<$2<<" -> "<<$4<<std::endl;
			ville.detruireRoute(ville.indiceMaison($2),$4);
        }
        | destroy nom arrow nom {
             std::cout<<"Detruire route "<<$2<<" -> "<<$4<<std::endl;
			ville.detruireRoute(ville.indiceMaison($2),ville.indiceMaison($4));
        }
        | destroy coordonnee arrow nom {
            std::cout<<"Detruire route "<<$2<<" -> "<<$4<<std::endl;
			ville.detruireRoute(ville.indiceMaison($2),ville.indiceMaison($4));
        }
        | destroy nom arrow coordonnee {
            std::cout<<"Detruire route "<<$2<<" -> "<<$4<<std::endl;
			ville.detruireRoute(ville.indiceMaison($2),ville.indiceMaison($4));
        }
        | deplacer coordonnee arrow coordonnee {
            std::cout<<"Deplacer maison "<<$2<<" -> "<<$4<<std::endl;
			ville.deplaceMaison($2,$4);
        }
        | deplacer indice arrow coordonnee {
            std::cout<<"Deplacer maison "<<$2<<" -> "<<$4<<std::endl;
			ville.deplaceMaison($2,$4);
        }
        | deplacer nom arrow coordonnee {
            std::cout<<"Deplacer maison "<<$2<<" -> "<<$4<<std::endl;
			ville.deplaceMaison(ville.indiceMaison($2),$4);
        }
        | position indice {
            std::cout<<"Position maison["<<$2<<"] ";
            std::cout<<ville.getMaisons()[$2].getCoord()<<std::endl;
        }
        | position nom {
            std::cout<<"Position "+$2;
            std::cout<<ville.getMaisons()[ville.indiceMaison($2)].getCoord()<<std::endl;
        }
        | voisinage coordonnee {
            ville.voisinage(ville.indiceMaison($2));
        }
        | voisinage indice {
            ville.voisinage($2);
        }
        | voisinage nom {
            ville.voisinage(ville.indiceMaison($2));
        }
        | affectation {
        }
        | coloriser coordonnee couleurhexa {
            ville.coloriser(ville.indiceMaison($2),$3);
        }
        | coloriser indice couleurhexa {
            ville.coloriser($2,$3);
        }
        | coloriser nom couleurhexa {
            ville.coloriser(ville.indiceMaison($2),$3);
        }
        | coloriser variable couleurhexa {
            ville.coloriser(((int)driver.getVariable($2))-1,$3);
        }
        | coloriser coordonnee '(' expression ',' expression ',' expression ')' {
            ville.coloriser(ville.indiceMaison($2),ville.intTohexa($4,$6,$8));
        }
        | coloriser indice '(' expression ',' expression ',' expression ')' {
            ville.coloriser($2,ville.intTohexa($4,$6,$8));
        }
        | coloriser nom '(' expression ',' expression ',' expression ')' {
            ville.coloriser(ville.indiceMaison($2),ville.intTohexa($4,$6,$8));
        }
        | coloriser variable '(' expression ',' expression ',' expression ')' {
            ville.coloriser(((int)driver.getVariable($2))-1,ville.intTohexa($4,$6,$8));
        }
        | couleur coordonnee {
            ville.afficheCouleur(ville.indiceMaison($2));
        }
        | couleur indice {
            ville.afficheCouleur($2);
        }
        | couleur nom {
            ville.afficheCouleur(ville.indiceMaison($2));
        }
		| voisin coordonnee expression {
			ville.voisin($2,$3);
		}
		| voisin indice expression {
			ville.voisin($2,$3);
		}
		| voisin nom expression {
			ville.voisin($2,$3);
		}




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
