#ifndef DRIVER_H
#define DRIVER_H

#include "../IG/villeGUI.hh"
#include <string>

#include "contexte.hh"

class Driver {
private:
    Contexte _variables;
    VilleGUI *V;

public:
    Driver();
    ~Driver();
    Driver(const Driver&) = default;

    VilleGUI * getVille()const{return V;}

    const Contexte &getContexte() const;
    double getVariable(const std::string &name) const;
    void setVariable(const std::string &name, double value);

    // Ville GUI V

    void setRadius(unsigned int r) {V->setRadius(r);}
    unsigned int getRadius() {return V->getRadius();}
    void construireMaison(int x, int y, int z) {V->construireMaison(x,y,z);}
    void construireRoute(int x1, int y1, int z1, int x2, int y2, int z2) {V->construireRoute(x1,y1,z1,x2,y2,z2);}
    void detruireMaison(int x, int y, int z);
    void detruireRoute(int x1, int y1, int z1, int x2, int y2, int z2);
    MaisonGUI* getMaison(int x, int y, int z);
    RouteGUI* getRoute(int x1, int y1, int z1, int x2, int y2, int z2);
    CouleurGUI getCouleur(int x, int y, int z) {return V->getCouleur(x,y,z);}
    void setCouleur(int x, int y, int z, int r, int g, int b) {V->setCouleur(x,y,z,r,g,b);}
    int getOrientation(int x, int y, int z) {return V->getOrientation(x,y,z);}
    void setOrientation(int x, int y, int z, int o) {V->setOrientation(x,y,z,o);}
    unsigned int getRayon() {return V->getRayon();}
    void setRayon(unsigned int r) {V->setRayon(r);}

    //DRAWING
    unsigned int housesDistance(PositionGUI P1, PositionGUI P2);
    void drawHexagon(QPainter& p, int x, int y, int z);
    void drawHouses(QPainter& p);
    void drawRoads(QPainter& p);
    void drawHouse(QPainter& p, MaisonGUI* M);
    void drawRoad(QPainter& p, RouteGUI* R);
    void drawRoadIn(QPainter& p, PositionGUI P1, PositionGUI P2, bool start, bool end);
    void drawRoundAbout(QPainter& p, int x, int y, int z);
    void drawMap(QPainter& p, unsigned int r);
};

#endif
