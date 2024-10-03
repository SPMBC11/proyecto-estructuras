#include "nodokd.h"

// Constructor
NodoKD::NodoKD(Vertice* vertice, NodoKD* hijoIzq, NodoKD* hijoDer)
    : vertice(vertice), hijoIzq(hijoIzq), hijoDer(hijoDer) {}

// Destructor
NodoKD::~NodoKD() {}

// Getters
Vertice* NodoKD::getVertice() const {
    return vertice;
}

NodoKD* NodoKD::getHijoIzq() const {
    return hijoIzq;
}

NodoKD* NodoKD::getHijoDer() const {
    return hijoDer;
}

// Setters
void NodoKD::setVertice(Vertice* vertice) {
    this->vertice = vertice;
}

void NodoKD::setHijoIzq(NodoKD* nodo) {
    hijoIzq = nodo;
}

void NodoKD::setHijoDer(NodoKD* nodo) {
    hijoDer = nodo;
}

// M�todo para verificar si es una hoja
bool NodoKD::esHoja() const {
    return hijoIzq == nullptr && hijoDer == nullptr;
}
