%{

#include "scanner.hh"
#include <cstdlib>
#include <iostream>
#include <string>

#define YY_NO_UNISTD_H

using token = yy::Parser::token;

#undef  YY_DECL
#define YY_DECL int Scanner::yylex( yy::Parser::semantic_type * const lval, yy::Parser::location_type *loc )

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option c++
%option yyclass="Scanner"
%option noyywrap

%%
%{
    yylval = lval;
%}
fin return token::END;

"Construire" return token::build;
"Maison" return token::maison;
"Route" return token::route;
"->" return token::arrow;
"Tourner" return token::turn;
"horaire" return token::horaire;
"Orienter" return token::orienter;
"Orientation" return token::orientation;
"Detruire" return token::destroy;
"Deplacer" return token::deplacer;
"Position" return token::position;
"Voisinage" return token::voisinage;
"maison" return token::indmaison;


"+" return '+';
"*" return '*';
"-" return '-';
"/" return '/';
"(" return '(';
")" return ')';
"=" return '=';
"{" return '{';
"}" return '}';
"," return ',';
"\'" return '\'';
"!" return '!';
"[" return '[';
"]" return ']';
"°" return token::degree;

[0-9]+      {
    yylval->build<int>(std::atoi(YYText()));
    return token::NUMBER;
}
(%%.*)$      {
        return token::com;
}
(%\/(.|\n)*\/%)   {
    return token::com;
}

"\n"          {
    loc->lines();
    return token::NL;
}

%%
