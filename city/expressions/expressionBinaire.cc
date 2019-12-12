#include "expressionBinaire.hh"
#include <math.h>

ExpressionBinaire::ExpressionBinaire(ExpressionPtr gauche, ExpressionPtr droite, OperateurBinaire op):
    _gauche(gauche), _droite(droite), _op(op) {

}

double ExpressionBinaire::calculer(const Contexte& contexte) const {
    double gauche = _gauche->calculer(contexte), droite = _droite->calculer(contexte);
    switch (_op){
    case OperateurBinaire::plus:
        return gauche + droite;
    case OperateurBinaire::moins:
        return gauche - droite;
    case OperateurBinaire::divise:
    {
        if (droite == 0)
            throw std::domain_error("division par 0");
        double fractpart, intpart;
        fractpart = modf((gauche / droite), &intpart); 
        return ((fractpart<0.5)? intpart : intpart+1);
    }
    case OperateurBinaire::multiplie:
        return gauche * droite;
    default:
        return 0;
    }
}