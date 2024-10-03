#include "cara.h"
using namespace std;

// Constructor por defecto
Cara::Cara() {}

// Constructor parametrizado
Cara::Cara(const list<Arista*>& aristas) : aristas(aristas) {}

// Destructor
Cara::~Cara() {}

// Getter
list<Arista*> Cara::getAristas() const {
    return aristas;
}

// Setter
void Cara::setAristas(const list<Arista*>& newAristas) {
    aristas = newAristas;
}