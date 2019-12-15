%{

#include "scanner.hh"
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
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

"Construire"    return token::build;
"Maison"        return token::maison;
"Route"         return token::route;
"->"            return token::arrow;
"Tourner"       return token::turn;
"horaire"       return token::horaire;
"Orienter"      return token::orienter;
"Orientation"   return token::orientation;
"Detruire"      return token::destroy;
"Deplacer"      return token::deplacer;
"Position"      return token::position;
"Voisinage"     return token::voisinage;
"maison"        return token::indmaison;
"Coloriser"     return token::coloriser;
"Couleur"       return token::couleur;
"Voisin"        return token::voisin;

"occupe"        return token::occupe;
"vide"          return token::vide;
"non"           return token::non;
"Si"            return token::sicond;
"Tant que"      return token::tantque;
"Repeter"       return token::repeter;
"void"          return token::fonctionvoid;
"Sinon"         return token::sinon;
"fois"          return token::fois;

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
    yylval->build<float>(std::atoi(YYText()));
    return token::NUMBER;
}
(%%.*)$      {
        return token::com;
}
(%\/(.|\n)*\/%)   {
    return token::com;
}

([A-Z][a-zA-Z0-9_]*) {
	yylval->build<std::string>(YYText());
	return token::nom;
}

([a-z][a-zA-Z0-9_]*)    {
    yylval->build<std::string>(YYText());
	return token::variable;
}
(#[a-fA-F0-9]{6})   {
     yylval->build<std::string>(YYText());
	return token::couleurhexa;
}

"\n"          {
    loc->lines();
    return token::NL;
}

%%
