#include "variable.hh"

Variable::Variable(const std::string& nom) : _nom(nom) {}

double Variable::calculer(const Contexte & contexte) const {
    try
    {
        return contexte[_nom];
    }
    catch (const std::out_of_range &e)
    {
        throw std::out_of_range("la variable " + _nom + " n'existe pas dans ce contexte");
    }
}