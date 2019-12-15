#ifndef DRIVER_H
#define DRIVER_H

#include <string>

#include "contexte.hh"

class Driver {
private:
    Contexte _variables;       

public:
    Driver();
    ~Driver();
    Driver(const Driver&) = default;

    const Contexte &getContexte() const;
    double getVariable(const std::string &name) const;
    void setVariable(const std::string &name, double value);
};

#endif
