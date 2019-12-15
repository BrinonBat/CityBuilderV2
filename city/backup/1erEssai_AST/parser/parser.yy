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
	#include "prog.hh"
    #include <iostream>

    class Scanner;
    class Driver;
    class instruction;
}

%parse-param { Scanner &scanner }
%parse-param { Driver &driver }
%parse-param { prog &traiteur }

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


%type <int>             expression
%type<std::vector<instruction>> instructions

%%


programme:
	instructions {
		traiteur.traite($1);
		YYACCEPT;
	}
instructions:
    instruction NL instructions{
		$$=$3;
		$$.push_back($1);
	}
	| %empty {
		$$=std::vector<instruction>();
	}

instruction:
	build '(' expression ')' '{'instructions'}' {
		Construct builder;
		builder.rayon=$3
		builder.traitBuild.push_back($6);
		$$=builder;
	}

%%

void yy::Parser::error( const location_type &l, const std::string & err_msg) {
    std::cerr << "Erreur : " << l << ", " << err_msg << std::endl;
}
