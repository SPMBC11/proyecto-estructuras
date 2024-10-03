#include "malla.h"
using namespace std;

// Constructor por defecto
Malla::Malla() : nombre("") {}

// Constructor parametrizado
Malla::Malla(const string& nombre, const list<Vertice*>& vertices, const list<Arista*>& aristas, const list<Cara*>& caras) 
    : nombre(nombre), vertices(vertices), aristas(aristas), caras(caras) {}

// Destructor
Malla::~Malla() {}

// Getters
string Malla::getNombre() const { return nombre; }
list<Vertice*> Malla::getVertices() const { return vertices; }
list<Arista*> Malla::getAristas() const { return aristas; }
list<Cara*> Malla::getCaras() const { return caras; }

// Setters
void Malla::setNombre(const string& nombre) { this->nombre = nombre; }
void Malla::setVertices(const list<Vertice*>& newVertices) { vertices = newVertices; }
void Malla::setAristas(const list<Arista*>& newAristas) { aristas = newAristas; }
void Malla::setCaras(const list<Cara*>& newCaras) { caras = newCaras; }