#ifndef CARA_H
#define CARA_H

#include <list>
#include "arista.h"

class Cara {
public:
    // Constructor por defecto
    Cara();

    // Constructor parametrizado
    Cara(const list<Arista*>& aristas);

    // Destructor
    virtual ~Cara();

    // Getter
    list<Arista*> getAristas() const;

    // Setter
    void setAristas(const list<Arista*>& newAristas);

protected:
    list<Arista*> aristas;
};

#endif