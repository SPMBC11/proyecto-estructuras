#ifndef MALLA_H
#define MALLA_H

#include <list>
#include <string>
#include "vertice.h"
#include "arista.h"
#include "cara.h"

using namespace std; 

class Malla {
public:
    // Constructor por defecto
    Malla();

    // Constructor parametrizado
    Malla(const string& nombre, const list<Vertice*>& vertices, const list<Arista*>& aristas, const list<Cara*>& caras);

    // Destructor
    virtual ~Malla();

    // Getters
    string getNombre() const;
    list<Vertice*> getVertices() const;
    list<Arista*> getAristas() const;
    list<Cara*> getCaras() const;

    // Setters
    void setNombre(const string& nombre);
    void setVertices(const list<Vertice*>& newVertices);
    void setAristas(const list<Arista*>& newAristas);
    void setCaras(const list<Cara*>& newCaras);

protected:
    string nombre; // Atributo añadido
    list<Vertice*> vertices;
    list<Arista*> aristas;
    list<Cara*> caras;
};

#endif
