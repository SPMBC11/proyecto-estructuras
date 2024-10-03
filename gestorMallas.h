#ifndef GESTORMALLAS_H
#define GESTORMALLAS_H

#include <string>
#include <list>
#include "malla.h"

using namespace std;

class GestorMallas {
public:
    void cargar(string nombreArchivo);
    void listado();
    void envolvente(string nombreObjeto, bool global);
    void descargar(string nombreObjeto);
    void guardar(string nombreObjeto, string nombreArchivo);
    void vCercano(double px, double py, double pz, string nombreObjeto, bool global);
    void vCercanosCaja(string nombreObjeto);

    list<Malla> getMallas();
    void setMallas(const list<Malla>& nuevasMallas);

protected:
    list<Malla> mallas;
};

#endif
