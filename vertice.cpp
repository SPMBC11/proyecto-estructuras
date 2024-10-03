#include "vertice.h"
using namespace std;

// Constructor por defecto
Vertice::Vertice() : x(0), y(0), z(0) {}

// Constructor parametrizado
Vertice::Vertice(double x, double y, double z) : x(x), y(y), z(z) {}

// Destructor
Vertice::~Vertice() {}

// Getters
double Vertice::getX() const {
    return x;
}

double Vertice::getY() const {
    return y;
}

double Vertice::getZ() const {
    return z;
}

// Setters
void Vertice::setX(double newX) {
    x = newX;
}

void Vertice::setY(double newY) {
    y = newY;
}

void Vertice::setZ(double newZ) {
    z = newZ;
}