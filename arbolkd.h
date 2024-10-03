#ifndef ARBOLKD_H
#define ARBOLKD_H
#include "cmath"
#include "nodokd.h"

class ArbolKD {
public:
    // Constructor
    ArbolKD();

    // Destructor
    virtual ~ArbolKD();

    // Getter
    NodoKD* getRaiz() const;

    // Setter
    void setRaiz(NodoKD* nodo);

    int getDim() const;

    void setDim(int dimension);

    // M�todo para verificar si el �rbol est� vac�o
    bool esVacio() const;

    // M�todo para insertar un v�rtice en el �rbol K-d
    bool insertar(Vertice* vertice);
    bool insertarRec(NodoKD* nodo, Vertice* vertice, int dim);

    // M�todos de recorridos
    void preorden() const;
    void inorden() const;
    void posorden() const;

    // Método para buscar el vértice más cercano
    Vertice* buscarCercano(NodoKD* nodo, double px, double py, double pz, int dim, Vertice* mejorVertice, double& mejorDistancia) const;

    /*
    NodoArbol* buscarMinimo(NodoArbol* raiz);

    // Liberar la memoria del árbol
    void eliminarArbol(NodoArbol* raiz);
    */

protected:
    NodoKD* raiz;
    int dimension;
    void preorden(NodoKD* nodo) const;
    void inorden(NodoKD* nodo) const;
    void posorden(NodoKD* nodo) const;
};

#endif // ARBOLKD_H

