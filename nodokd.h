#ifndef NODOKD_H
#define NODOKD_H

#include "vertice.h"
using namespace std;

class NodoKD {
public:
    // Constructor
    NodoKD(Vertice* vertice, NodoKD* hijoIzq = nullptr, NodoKD* hijoDer = nullptr);

    // Destructor
    virtual ~NodoKD();

    // Getters
    Vertice* getVertice() const;
    NodoKD* getHijoIzq() const;
    NodoKD* getHijoDer() const;

    // Setters
    void setVertice(Vertice* vertice);
    void setHijoIzq(NodoKD* nodo);
    void setHijoDer(NodoKD* nodo);

    bool esHoja() const;

protected:
    Vertice* vertice; // V�rtice que representa el punto en el �rbol K-d
    NodoKD* hijoIzq; // Puntero al hijo izquierdo
    NodoKD* hijoDer;   // Puntero al hijo derecho
};

#endif // NODOKD_H
