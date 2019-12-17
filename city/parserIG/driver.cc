#include "driver.hh"
#include <iostream>

Driver::Driver() {
    V = new VilleGUI();
}
Driver::~Driver() {}

const Contexte &Driver::getContexte() const
{
    return _variables;
}

double Driver::getVariable(const std::string &name) const
{
    return _variables.get(name);
}

void Driver::setVariable(const std::string &name, double value)
{
    _variables[name] = value;
}

MaisonGUI* Driver::getMaison(int x,int y,int z){
    return V->getMaison(x,y,z);
}

void Driver::detruireMaison(int x, int y, int z){
    V->detruireMaison(x,y,z);
}

RouteGUI* Driver::getRoute(int x1, int y1, int z1, int x2, int y2, int z2){
    return V->getRoute(x1,y1,z1,x2,y2,z2);
}

void Driver::detruireRoute(int x1, int y1, int z1, int x2, int y2, int z2){
    V->detruireRoute(x1,y1,z1,x2,y2,z2);
}

void Driver::drawMap(QPainter& p, unsigned int radius) {
  V->drawMap(p,radius);
}

void Driver::drawHouse(QPainter& p, MaisonGUI* M){
 V->drawHouse(p,M);
}

unsigned int Driver::housesDistance(PositionGUI P1, PositionGUI P2){
  return V->housesDistance(P1,P2);
}

void Driver::drawRoad(QPainter& p, RouteGUI* R){
  V->drawRoad(p,R);
}

void Driver::drawRoadIn(QPainter& p, PositionGUI P1, PositionGUI P2, bool start, bool end){
  V->drawRoadIn(p,P1,P2,start,end);
}

void Driver::drawRoundAbout(QPainter& p, int x, int y, int z){
  V->drawRoundAbout(p,x,y,z);
}

void Driver::drawHexagon(QPainter& p, int x, int y, int z){
    V->drawHexagon(p,x,y,z);
}

void Driver::drawRoads(QPainter& p){
  V->drawRoads(p);
}

void Driver::drawHouses(QPainter& p){
  V->drawHouses(p);
}
