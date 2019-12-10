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
%token <int>            NUMBER degree 
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
%token                  voisinage
%token                  indmaison

%type <int>             operation indice
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
    operation  {
        std::cout << "#-> " << $1 << std::endl;
    }
    | build '{' NL traitements '}'{
         // creation graphe taille 5
        std::cout<<"Construire {"<<std::endl;
        std::cout<<$4<<std::endl;
        std::cout<<"}"<<std::endl;
        ville.exec(5);

    }
    | build '(' NUMBER ')' '{' NL traitements '}' {
        // creation graphe de taille resultat operation
        // si graphe existe deja change juste la taille graphe
        std::cout<<"Construire ("<<$3<<"){ test"<<std::endl;
        std::cout<<$7<<std::endl;
        std::cout<<"}"<<std::endl;
        ville.exec($3);

    }

traitements:
    traitement NL traitements{

    }
    |
    traitement NL {

    }

traitement:
         maison {
            //construire maison à un emplacement aléatoire
                std::cout<<"Maison ok"<<std::endl;
                ville.ajoutMaison();
        }
        | maison  coordonnee {
            // construire maison selon coordonées
                std::cout<<"Maison cok"<<std::endl;
                ville.ajoutMaison($2);
        }
        | route coordonnee arrow coordonnee  {
            std::cout<<"Route "<<"->"<<std::endl;
            ville.ajoutRoute($2,$4);

        }
        | route coordonnee arrow indice  {
            std::cout<<"Route "<<"->"<<std::endl;
            ville.ajoutRoute($2,$4);

        }
        | route indice arrow indice  {
            std::cout<<"Route "<<"->"<<std::endl;
            ville.ajoutRoute($2,$4);

        }
        | route indice arrow coordonnee  {
            std::cout<<"Route "<<"->"<<std::endl;
            ville.ajoutRoute($2,$4);

        }
        | com {
            std::cout<<"\t\tCommentaire"<<std::endl;
        }
        | turn coordonnee senshoraire {
            std::cout<<"Tourner"<<std::endl;
        } 
        | turn indice senshoraire {
            std::cout<<"Tourner"<<std::endl;
        } 
        | orienter coordonnee operation '°' {
            std::cout<<"Orienter"<<std::endl;
        }
        | orienter indice operation '°' {
            std::cout<<"Orienter"<<std::endl;
        }
        | orientation coordonnee {
            std::cout<<"Orienter"<<std::endl;
        }
        | orientation indice {
            std::cout<<"Orienter"<<std::endl;
        }
        | destroy coordonnee {
            std::cout<<"Detruire"<<std::endl;
        }
        | destroy indice {
            std::cout<<"Detruire"<<std::endl;
        }
        | destroy coordonnee arrow coordonnee {
            std::cout<<"Detruire"<<std::endl;
        }
        | destroy coordonnee arrow indice {
            std::cout<<"Detruire"<<std::endl;
        }
        | destroy indice arrow coordonnee {
            std::cout<<"Detruire"<<std::endl;
        }
        | destroy indice arrow indice {
            std::cout<<"Detruire"<<std::endl;
        }
        | deplacer coordonnee arrow coordonnee {
            std::cout<<"Deplacer"<<std::endl;
        }
        | deplacer indice arrow coordonnee {
            std::cout<<"Deplacer"<<std::endl;
        }
        | position indice {
            std::cout<<"position indice"<<std::endl;
        } 
        | voisinage coordonnee {
            std::cout<<"voisinage indice"<<std::endl;
        } 
        | voisinage indice {
            std::cout<<"voisinage indice"<<std::endl;
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
        $$=$3;
    }

coordonnee:
        '(' operation ',' operation ',' operation ')' {
            $$._x = $2;
            $$._y = $4;
            $$._z = $6;
            std::cout<<"Coordonnée";
            }

operation:
    NUMBER {
        $$ = $1;
    }
    | '(' operation ')' {
        $$ = $2;
    }
    | operation '+' operation {
        $$ = $1 + $3;
    }
    | operation '-' operation {
        $$ = $1 - $3;
    }
    | operation '*' operation {
        $$ = $1 * $3;
    }
    | operation '/' operation {
        $$ = $1 / $3;
    }
    | '-' operation %prec NEG {
        $$ = - $2;
    }

%%

void yy::Parser::error( const location_type &l, const std::string & err_msg) {
    std::cerr << "Erreur : " << l << ", " << err_msg << std::endl;
}
