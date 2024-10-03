#ifndef VERTICE_H
#define VERTICE_H

#include <iostream>
using namespace std;

class Vertice {
public:
    // Constructor por defecto
    Vertice();

    // Constructor parametrizado
    Vertice(double x, double y, double z);

    // Destructor
    virtual ~Vertice();

    // Getters
    double getX() const;
    double getY() const;
    double getZ() const;

    // Setters
    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);

protected:
    double x, y, z;
};

#endif