#include "arista.h"
using namespace std;

// Constructor por defecto
Arista::Arista() : inicio(nullptr), fin(nullptr) {}

// Constructor parametrizado
Arista::Arista(Vertice* inicio, Vertice* fin) : inicio(inicio), fin(fin) {}

// Destructor
Arista::~Arista() {}

// Getters
Vertice* Arista::getInicio() const {
    return inicio;
}

Vertice* Arista::getFin() const {
    return fin;
}

// Setters
void Arista::setInicio(Vertice* newInicio) {
    inicio = newInicio;
}

void Arista::setFin(Vertice* newFin) {
    fin = newFin;
}
