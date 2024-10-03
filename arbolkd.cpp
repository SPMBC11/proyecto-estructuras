#include "arbolkd.h"
#include <iostream>
using namespace std;

// Constructor
ArbolKD::ArbolKD() : raiz(nullptr) {}

// Destructor
ArbolKD::~ArbolKD() {
}

// Getter de la ra�z
NodoKD* ArbolKD::getRaiz() const {
    return raiz;
}

// Setter de la ra�z
void ArbolKD::setRaiz(NodoKD* nodo) {
    raiz = nodo;
}

int ArbolKD::getDim() const {
    return dimension;
}

void setDim(int dimension){
    dimension = dimension;
}


// M�todo para verificar si el �rbol est� vac�o
bool ArbolKD::esVacio() const {
    return raiz == nullptr;
}

bool ArbolKD::insertar(Vertice* vertice) {
    if (esVacio()) {
        raiz = new NodoKD(vertice);
        return true;
    }
    return insertarRec(raiz, vertice, 0);
}

bool ArbolKD::insertarRec(NodoKD* nodo, Vertice* vertice, int dim) {
    // Comparar el punto con el dato en el nodo actual
    if (nodo->getVertice()->getX() == vertice->getX() &&
        nodo->getVertice()->getY() == vertice->getY() &&
        nodo->getVertice()->getZ() == vertice->getZ()) {
        return false; // Duplicado
    }

    double v = 0;
    double n = 0;

    if(dimension == 0){
        v = vertice->getX();
        n = nodo->getVertice()->getX();
    } else if(dimension == 1){
        v = vertice->getY();
        n = nodo->getVertice()->getY();
    } else{
        v = vertice->getZ();
        n = nodo->getVertice()->getZ();
    }

    if ( v < n) {
        // Bajar por la izquierda
        if (nodo->getHijoIzq() == nullptr) {
            nodo->setHijoIzq(new NodoKD(vertice));
            return true;
        } else {
            return insertarRec(nodo->getHijoIzq(), vertice, dim + 1);
        }
    } else {
        // Bajar por la derecha
        if (nodo->getHijoDer() == nullptr) {
            nodo->setHijoDer(new NodoKD(vertice));
            return true;
        } else {
            return insertarRec(nodo->getHijoDer(), vertice, dim + 1);
        }
    }
}

// Preorden
void ArbolKD::preorden() const {
    preorden(raiz);
}

void ArbolKD::preorden(NodoKD* nodo) const {
    if (nodo) {
        cout << "(" << nodo->getVertice()->getX() << ", "
                  << nodo->getVertice()->getY() << ", "
                  << nodo->getVertice()->getZ() << ")" << endl;
        preorden(nodo->getHijoIzq());
        preorden(nodo->getHijoDer());
    }
}

// Inorden
void ArbolKD::inorden() const {
    inorden(raiz);
}

void ArbolKD::inorden(NodoKD* nodo) const {
    if (nodo) {
        inorden(nodo->getHijoIzq());
        cout << "(" << nodo->getVertice()->getX() << ", "
                  << nodo->getVertice()->getY() << ", "
                  << nodo->getVertice()->getZ() << ")" << endl;
        inorden(nodo->getHijoDer());
    }
}

// Posorden
void ArbolKD::posorden() const {
    posorden(raiz);
}

void ArbolKD::posorden(NodoKD* nodo) const {
    if (nodo) {
        posorden(nodo->getHijoIzq());
        posorden(nodo->getHijoDer());
        cout << "(" << nodo->getVertice()->getX() << ", "
                  << nodo->getVertice()->getY() << ", "
                  << nodo->getVertice()->getZ() << ")" << endl;
    }
}


Vertice* ArbolKD::buscarCercano(NodoKD* nodo, double px, double py, double pz, int dim,
                                 Vertice* mejorVertice, double& mejorDistancia) const {
    if (nodo == nullptr) {
        return mejorVertice; // Si no hay nodo, devuelve el mejor vértice encontrado
    }

    // Calcular la distancia al vértice actual
    double distancia = sqrt(pow(nodo->getVertice()->getX() - px, 2) +
                             pow(nodo->getVertice()->getY() - py, 2) +
                             pow(nodo->getVertice()->getZ() - pz, 2));

    // Si esta es la primera iteración o si encontramos un vértice más cercano
    if (mejorVertice == nullptr || distancia < mejorDistancia) {
        mejorDistancia = distancia;
        mejorVertice = nodo->getVertice(); // Actualizar el mejor vértice
    }

    // Calcular la dimensión actual
    int currentDim = dim % dimension;

    // Determinar el siguiente nodo a explorar
    NodoKD* siguienteNodo;
    if (currentDim == 0) {
        if (px < nodo->getVertice()->getX()) {
            siguienteNodo = nodo->getHijoIzq();
        } else {
            siguienteNodo = nodo->getHijoDer();
        }
    } else if (currentDim == 1) {
        if (py < nodo->getVertice()->getY()) {
            siguienteNodo = nodo->getHijoIzq();
        } else {
            siguienteNodo = nodo->getHijoDer();
        }
    } else {
        if (pz < nodo->getVertice()->getZ()) {
            siguienteNodo = nodo->getHijoIzq();
        } else {
            siguienteNodo = nodo->getHijoDer();
        }
    }

    // Recursión hacia el subárbol
    mejorVertice = buscarCercano(siguienteNodo, px, py, pz, dim + 1, mejorVertice, mejorDistancia);

    // Comprobar si es necesario explorar el otro subárbol
    NodoKD* otroNodo;
    if (siguienteNodo == nodo->getHijoIzq()) {
        otroNodo = nodo->getHijoDer();
    } else {
        otroNodo = nodo->getHijoIzq();
    }

    if (otroNodo != nullptr) {
        double distanciaAlPlano;
        if (currentDim == 0) {
            distanciaAlPlano = fabs(px - nodo->getVertice()->getX());
        } else if (currentDim == 1) {
            distanciaAlPlano = fabs(py - nodo->getVertice()->getY());
        } else {
            distanciaAlPlano = fabs(pz - nodo->getVertice()->getZ());
        }

        if (distanciaAlPlano < mejorDistancia) {
            mejorVertice = buscarCercano(otroNodo, px, py, pz, dim + 1, mejorVertice, mejorDistancia);
        }
    }

    return mejorVertice; // Devolver el mejor vértice encontrado
}
