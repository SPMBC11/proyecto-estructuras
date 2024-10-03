#ifndef ARISTA_H
#define ARISTA_H

#include "vertice.h"

class Arista {
public:
    // Constructor por defecto
    Arista();

    // Constructor parametrizado
    Arista(Vertice* inicio, Vertice* fin);

    // Destructor
    virtual ~Arista();

    // Getters
    Vertice* getInicio() const;
    Vertice* getFin() const;

    // Setters
    void setInicio(Vertice* newInicio);
    void setFin(Vertice* newFin);

protected:
    Vertice* inicio;
    Vertice* fin;
};

#endif