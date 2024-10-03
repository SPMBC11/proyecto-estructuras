#include "gestorMallas.h"
#include "arbolkd.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

// Getter
list<Malla> GestorMallas::getMallas() {
    return mallas;
}

// Setter
void GestorMallas::setMallas(const list<Malla>& nuevasMallas) {
    mallas = nuevasMallas;
}


void GestorMallas::cargar(string nombreArchivo) {

    ifstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()) {
        cout << "El archivo " << nombreArchivo << " no existe o es ilegible." << endl;
        return;
    }

    string meshName;
    int nVertices;

    // Leer el nombre de la malla
    archivo >> meshName;
    if (meshName.empty()) {
        cout << "El archivo " << nombreArchivo << " no contiene un objeto 3D válido." << endl;
        return;
    }

    // Verificar si el objeto ya existe en memoria
    for (const Malla& malla : mallas) {
        if (malla.getNombre() == meshName) {  // Supongo que existe un método getNombre en la clase Malla
            cout << "El objeto " << meshName << " ya ha sido cargado en memoria." << endl;
            return;
        }
    }

    // Leer la cantidad de vértices
    archivo >> nVertices;
    if (nVertices <= 0) {
        cout << "El archivo " << nombreArchivo << " no contiene un objeto 3D válido." << endl;
        return;
    }

    list<Vertice*> vertices;
    for (int i = 0; i < nVertices; ++i) {
        double x, y, z;
        archivo >> x >> y >> z;
        if (archivo.fail()) {
            cout << "El archivo " << nombreArchivo << " no contiene un objeto 3D válido." << endl;
            return;
        }
        Vertice* vertice = new Vertice(x, y, z);
        vertices.push_back(vertice);
    }

    list<Arista*> aristas;
    list<Cara*> caras;

    // Leer las caras (cada cara contiene índices de vértices)
    while (true) {
        int nCarasVertices;
        archivo >> nCarasVertices;

        if (nCarasVertices == -1) {
            break;  // Fin del archivo
        }

        if (nCarasVertices <= 0 || archivo.fail()) {
            cout << "El archivo " << nombreArchivo << " no contiene un objeto 3D válido." << endl;
            return;
        }

        list<Arista*> caraAristas;
        vector<Vertice*> caraVertices;

        for (int i = 0; i < nCarasVertices; ++i) {
            int indiceVertice;
            archivo >> indiceVertice;
            if (indiceVertice < 0 || indiceVertice >= nVertices || archivo.fail()) {
                cout << "El archivo " << nombreArchivo << " no contiene un objeto 3D válido." << endl;
                return;
            }
            list<Vertice*>::iterator it = vertices.begin();
            advance(it, indiceVertice);  // Encontrar el vértice en la lista
            caraVertices.push_back(*it);
        }

        // Crear las aristas para la cara
        for (size_t i = 0; i < caraVertices.size(); ++i) {
            Arista* arista = new Arista(caraVertices[i], caraVertices[(i + 1) % caraVertices.size()]);
            aristas.push_back(arista);
            caraAristas.push_back(arista);
        }

        // Crear la cara y añadirla a la lista
        Cara* cara = new Cara(caraAristas);
        caras.push_back(cara);
    }

    // Crear la malla y agregarla a la lista de mallas
    Malla malla(meshName, vertices, aristas, caras);
    mallas.push_back(malla);

    cout << "El objeto " << meshName << " ha sido cargado exitosamente desde el archivo " << nombreArchivo << "." << endl;

}

void GestorMallas::listado() {

    if (mallas.empty()) {
        cout << "Ningun objeto ha sido cargado en memoria." << endl;
    } else {
        cout << "Hay " << mallas.size() << " objetos en memoria:" << endl;
    }
    for (auto it = mallas.begin(); it != mallas.end(); ++it) {
        cout << it->getNombre() << " ";
        cout << "Contiene " << it->getVertices().size() << " vértices, ";
        cout << it->getAristas().size() << " aristas y ";
        cout << it->getCaras().size() << " caras." << endl;
    }

}

void GestorMallas::envolvente(string nombreObjeto, bool global) {


    if (mallas.empty()) {
        cout << "Ningun objeto ha sido cargado en memoria." << endl;
        return;
    }
    // Inicializar puntos extremos
    double xmin = numeric_limits<double>::max();
    double ymin = numeric_limits<double>::max();
    double zmin = numeric_limits<double>::max();
    double xmax = numeric_limits<double>::lowest();
    double ymax = numeric_limits<double>::lowest();
    double zmax = numeric_limits<double>::lowest();

    if(global == false){

    Malla* objetoEncontrado = nullptr;
    for (auto& malla : mallas) {
        if (malla.getNombre() == nombreObjeto) {
            objetoEncontrado = &malla;
            break;
        }
    }

    if (objetoEncontrado == nullptr) {
        cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << endl;
        return;
    }

    // Obtener los vértices de la malla
    list<Vertice*> vertices = objetoEncontrado->getVertices();
    if (vertices.empty()) {
        cout << "El objeto no tiene vértices válidos." << endl;
        return;
    }


    // Calcular los extremos pmin y pmax
    for (Vertice* vertice : vertices) {
        if (vertice->getX() < xmin) xmin = vertice->getX();
        if (vertice->getY() < ymin) ymin = vertice->getY();
        if (vertice->getZ() < zmin) zmin = vertice->getZ();
        if (vertice->getX() > xmax) xmax = vertice->getX();
        if (vertice->getY() > ymax) ymax = vertice->getY();
        if (vertice->getZ() > zmax) zmax = vertice->getZ();
    }
}
    if(global == true){
        // Iterar sobre todas las mallas en memoria
        for (const Malla& malla : mallas) {
            list<Vertice*> vertices = malla.getVertices();

            // Calcular los extremos de cada malla y ajustar los extremos globales
            for (Vertice* vertice : vertices) {
                if (vertice->getX() < xmin) xmin = vertice->getX();
                if (vertice->getY() < ymin) ymin = vertice->getY();
                if (vertice->getZ() < zmin) zmin = vertice->getZ();
                if (vertice->getX() > xmax) xmax = vertice->getX();
                if (vertice->getY() > ymax) ymax = vertice->getY();
                if (vertice->getZ() > zmax) zmax = vertice->getZ();
            }
        }
    }

    // Crear los vértices de la caja envolvente
    list<Vertice*> envolventeVertices;
    envolventeVertices.push_back(new Vertice(xmin, ymin, zmin));
    envolventeVertices.push_back(new Vertice(xmax, ymin, zmin));
    envolventeVertices.push_back(new Vertice(xmin, ymax, zmin));
    envolventeVertices.push_back(new Vertice(xmax, ymax, zmin));
    envolventeVertices.push_back(new Vertice(xmin, ymin, zmax));
    envolventeVertices.push_back(new Vertice(xmax, ymin, zmax));
    envolventeVertices.push_back(new Vertice(xmin, ymax, zmax));
    envolventeVertices.push_back(new Vertice(xmax, ymax, zmax));

    // Crear las aristas de la caja envolvente
    list<Arista*> envolventeAristas;
// Crear las 12 aristas de la caja envolvente (conectando los vértices)
    envolventeAristas.push_back(new Arista(envolventeVertices.front(), envolventeVertices.back())); // V0 - V1
        envolventeAristas.push_back(new Arista(*next(envolventeVertices.begin(), 1), *next(envolventeVertices.begin(), 2))); // V1 - V2
        envolventeAristas.push_back(new Arista(*next(envolventeVertices.begin(), 2), *next(envolventeVertices.begin(), 3))); // V2 - V3
        envolventeAristas.push_back(new Arista(*next(envolventeVertices.begin(), 3), envolventeVertices.front())); // V3 - V0

        envolventeAristas.push_back(new Arista(*next(envolventeVertices.begin(), 4), *next(envolventeVertices.begin(), 5))); // V4 - V5
        envolventeAristas.push_back(new Arista(*next(envolventeVertices.begin(), 5), *next(envolventeVertices.begin(), 6))); // V5 - V6
        envolventeAristas.push_back(new Arista(*next(envolventeVertices.begin(), 6), *next(envolventeVertices.begin(), 7))); // V6 - V7
        envolventeAristas.push_back(new Arista(*next(envolventeVertices.begin(), 7), *next(envolventeVertices.begin(), 4))); // V7 - V4

        envolventeAristas.push_back(new Arista(envolventeVertices.front(), *next(envolventeVertices.begin(), 4))); // V0 - V4
        envolventeAristas.push_back(new Arista(*next(envolventeVertices.begin(), 1), *next(envolventeVertices.begin(), 5))); // V1 - V5
        envolventeAristas.push_back(new Arista(*next(envolventeVertices.begin(), 2), *next(envolventeVertices.begin(), 6))); // V2 - V6
        envolventeAristas.push_back(new Arista(*next(envolventeVertices.begin(), 3), *next(envolventeVertices.begin(), 7))); // V3 - V7

    // Crear las caras de la caja envolvente
    list<Cara*> envolventeCaras;

    // Cara inferior (V0, V1, V2, V3)
    list<Arista*> caraInferior;
    caraInferior.push_back(*next(envolventeAristas.begin(), 0)); // V0 - V1
    caraInferior.push_back(*next(envolventeAristas.begin(), 1)); // V1 - V2
    caraInferior.push_back(*next(envolventeAristas.begin(), 2)); // V2 - V3
    caraInferior.push_back(*next(envolventeAristas.begin(), 3)); // V3 - V0
    envolventeCaras.push_back(new Cara(caraInferior));

    // Cara superior (V4, V5, V6, V7)
    list<Arista*> caraSuperior;
    caraSuperior.push_back(*next(envolventeAristas.begin(), 4)); // V4 - V5
    caraSuperior.push_back(*next(envolventeAristas.begin(), 5)); // V5 - V6
    caraSuperior.push_back(*next(envolventeAristas.begin(), 6)); // V6 - V7
    caraSuperior.push_back(*next(envolventeAristas.begin(), 7)); // V7 - V4
    envolventeCaras.push_back(new Cara(caraSuperior));

    // Cara lateral frontal (V0, V1, V5, V4)
    list<Arista*> caraFrontal;
    caraFrontal.push_back(*next(envolventeAristas.begin(), 0)); // V0 - V1
    caraFrontal.push_back(*next(envolventeAristas.begin(), 8)); // V0 - V4
    caraFrontal.push_back(*next(envolventeAristas.begin(), 9)); // V1 - V5
    caraFrontal.push_back(*next(envolventeAristas.begin(), 4)); // V4 - V5
    envolventeCaras.push_back(new Cara(caraFrontal));

    // Cara lateral trasera (V2, V3, V7, V6)
    list<Arista*> caraTrasera;
    caraTrasera.push_back(*next(envolventeAristas.begin(), 2)); // V2 - V3
    caraTrasera.push_back(*next(envolventeAristas.begin(), 10)); // V2 - V6
    caraTrasera.push_back(*next(envolventeAristas.begin(), 11)); // V3 - V7
    caraTrasera.push_back(*next(envolventeAristas.begin(), 6)); // V6 - V7
    envolventeCaras.push_back(new Cara(caraTrasera));

    // Cara lateral derecha (V1, V2, V6, V5)
    list<Arista*> caraDerecha;
    caraDerecha.push_back(*next(envolventeAristas.begin(), 1)); // V1 - V2
    caraDerecha.push_back(*next(envolventeAristas.begin(), 9)); // V1 - V5
    caraDerecha.push_back(*next(envolventeAristas.begin(), 10)); // V2 - V6
    caraDerecha.push_back(*next(envolventeAristas.begin(), 5)); // V5 - V6
    envolventeCaras.push_back(new Cara(caraDerecha));

    // Cara lateral izquierda (V0, V3, V7, V4)
    list<Arista*> caraIzquierda;
    caraIzquierda.push_back(*next(envolventeAristas.begin(), 3)); // V3 - V0
    caraIzquierda.push_back(*next(envolventeAristas.begin(), 8)); // V0 - V4
    caraIzquierda.push_back(*next(envolventeAristas.begin(), 11)); // V3 - V7
    caraIzquierda.push_back(*next(envolventeAristas.begin(), 7)); // V4 - V7
    envolventeCaras.push_back(new Cara(caraIzquierda));

    if(global == false){
        // Generar un nuevo nombre para la malla envolvente
        string nombreEnvolvente = "env_" + nombreObjeto;

        // Crear la nueva malla para la caja envolvente
        Malla cajaEnvolvente(nombreEnvolvente, envolventeVertices, envolventeAristas, envolventeCaras);

        // Agregar la malla envolvente a la lista de mallas
        mallas.push_back(cajaEnvolvente);

        cout << "La caja envolvente del objeto " << nombreObjeto << " se ha generado con el nombre " << nombreEnvolvente << " y se ha agregado a los objetos en memoria." << endl;
    }

    if(global == true){
        // Generar un nuevo nombre para la malla envolvente global
        string nombreEnvolventeGlobal = "env_global";

        // Crear la nueva malla para la caja envolvente global
        Malla cajaEnvolventeGlobal(nombreEnvolventeGlobal, envolventeVertices, envolventeAristas, envolventeCaras);

        // Agregar la malla envolvente global a la lista de mallas
        mallas.push_back(cajaEnvolventeGlobal);

        cout << "La caja envolvente de los objetos en memoria se ha generado con el nombre " << nombreEnvolventeGlobal << " y se ha agregado a los objetos en memoria." << endl;
    }

}

void GestorMallas::descargar(string nombreObjeto) {

    // Buscar el objeto en la lista de mallas
    auto it = mallas.begin();
    bool objetoEncontrado = false;

    for (; it != mallas.end(); ++it) {
        if (it->getNombre() == nombreObjeto) {
            objetoEncontrado = true;
            break;
        }
    }

    if (!objetoEncontrado) {
        cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << endl;
        return;
    }

    // Eliminar el objeto de la lista de mallas
    mallas.erase(it);

    cout << "El objeto " << nombreObjeto << " ha sido eliminado de la memoria de trabajo." << endl;
}

void GestorMallas::guardar(string nombreObjeto, string nombreArchivo) {

    // Buscar el objeto en memoria
    Malla* objetoEncontrado = nullptr;
    for (auto& malla : mallas) {
        if (malla.getNombre() == nombreObjeto) {
            objetoEncontrado = &malla;
            break;
        }
    }

    if (objetoEncontrado == nullptr) {
        cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << endl;
        return;
    }

    // Abrir el archivo de salida
    ofstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << " para escribir." << endl;
        return;
    }

    // Escribir el nombre del objeto
    archivo << objetoEncontrado->getNombre() << endl;

    // Escribir los vértices
    list<Vertice*> vertices = objetoEncontrado->getVertices();
    archivo << vertices.size() << endl;  // Número de vértices
    for (Vertice* vertice : vertices) {
        archivo << vertice->getX() << " " << vertice->getY() << " " << vertice->getZ() << endl;
    }

    // Escribir las caras
    list<Cara*> caras = objetoEncontrado->getCaras();
    for (Cara* cara : caras) {
        list<Arista*> aristas = cara->getAristas();

        // Vector para almacenar los índices únicos de vértices
        vector<int> indicesVertices;

        for (Arista* arista : aristas) {
            Vertice* inicio = arista->getInicio();
            Vertice* fin = arista->getFin();

            // Encontrar el índice del vértice de inicio manualmente
            int indiceInicio = 0;
            int i = 0;
            for (Vertice* v : vertices) {
                if (v == inicio) {
                    indiceInicio = i;
                    break;
                }
                i++;
            }

            // Verificar si el índice ya está en el vector
            bool existeInicio = false;
            for (int indice : indicesVertices) {
                if (indice == indiceInicio) {
                    existeInicio = true;
                    break;
                }
            }
            if (!existeInicio) {
                indicesVertices.push_back(indiceInicio);
            }

            // Encontrar el índice del vértice de fin manualmente
            int indiceFin = 0;
            i = 0;
            for (Vertice* v : vertices) {
                if (v == fin) {
                    indiceFin = i;
                    break;
                }
                i++;
            }

            // Verificar si el índice ya está en el vector
            bool existeFin = false;
            for (int indice : indicesVertices) {
                if (indice == indiceFin) {
                    existeFin = true;
                    break;
                }
            }
            if (!existeFin) {
                indicesVertices.push_back(indiceFin);
            }
        }

        // Escribir el número de vértices únicos en la cara
        archivo << indicesVertices.size();

        // Escribir los índices de los vértices
        for (int indice : indicesVertices) {
            archivo << " " << indice;
        }

        archivo << endl;
    }

    // Marcar el final de la información
    archivo << "-1" << endl;

    // Cerrar el archivo
    archivo.close();

    cout << "La información del objeto " << nombreObjeto << " ha sido guardada exitosamente en el archivo " << nombreArchivo << "." << endl;
}


void GestorMallas::vCercano(double px, double py, double pz, string nombreObjeto, bool global) {
    // Verificar si hay objetos cargados en memoria
    if (mallas.empty()) {
        cout << "Ningún objeto ha sido cargado en memoria." << endl;
        return;
    }

    ArbolKD arbol;
    Vertice* mejorVertice = nullptr;
    double mejorDistancia = numeric_limits<double>::max();

    if(global == false) {
        // Buscar el objeto en memoria
        Malla* objetoEncontrado = nullptr;
        for (auto& malla : mallas) {
            if (malla.getNombre() == nombreObjeto) {
                objetoEncontrado = &malla;
                break;
            }
        }

        if (objetoEncontrado == nullptr) {
            cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << endl;
            return;
        }

        // Obtener los vértices del objeto
        list<Vertice*> vertices = objetoEncontrado->getVertices();
        if (vertices.empty()) {
            cout << "El objeto " << nombreObjeto << " no tiene vértices válidos." << endl;
            return;
        }

        for (Vertice* vertice : vertices) {
            // Insertar el vértice en el árbol K-d
            arbol.insertar(vertice);
        }

        mejorVertice = arbol.buscarCercano(arbol.getRaiz(), px, py, pz, 0, mejorVertice, mejorDistancia);


        // Buscar el índice del mejor vértice
            int indice = 1;
            for (Vertice* vertice : vertices) {
                if (vertice == mejorVertice) {
                    break;
                }
                indice++;
            }

        // Mostrar el resultado en pantalla
        if (mejorVertice != nullptr) {
            cout << "El vertice " << indice << " ("
                 << mejorVertice->getX() << ", " << mejorVertice->getY() << ", "
                 << mejorVertice->getZ() << ") del objeto " << nombreObjeto
                 << " es el más cercano al punto (" << px << ", " << py << ", " << pz
                 << "), a una distancia de " << mejorDistancia << "." << endl;
        }
    }
    if(global == true){
        // Buscar el vértice más cercano entre todos los objetos cargados en memoria
        for (auto& malla : mallas) {
            // Obtener los vértices de cada objeto
            list<Vertice*> vertices = malla.getVertices();
            if (vertices.empty()) {
                continue; // Si no hay vértices, saltar al siguiente objeto
            }

            // Insertar los vértices en el árbol K-d
            for (Vertice* vertice : vertices) {
                arbol.insertar(vertice);
            }
        }

        // Buscar el vértice más cercano en el árbol K-d
        mejorVertice = arbol.buscarCercano(arbol.getRaiz(), px, py, pz, 0, mejorVertice, mejorDistancia);

        // Mostrar el resultado en pantalla
        if (mejorVertice != nullptr) {
            // Obtener el índice y el nombre del objeto del mejor vértice
            string nombreObjetoEncontrado;
            int indice = 0;
            for (auto& malla : mallas) {
                list<Vertice*> vertices = malla.getVertices();
                indice = 1;
                for (Vertice* vertice : vertices) {
                    if (vertice == mejorVertice) {
                        nombreObjetoEncontrado = malla.getNombre();
                        break;
                    }
                    indice++;
                }
            }

            cout << "El vértice " << indice << " ("
                 << mejorVertice->getX() << ", " << mejorVertice->getY() << ", "
                 << mejorVertice->getZ() << ") del objeto " << nombreObjetoEncontrado
                 << " es el más cercano al punto (" << px << ", " << py << ", " << pz
                 << "), a una distancia de " << mejorDistancia << "." << endl;
        }
    }
}


void GestorMallas::vCercanosCaja(string nombreObjeto) {

    // Verificar si hay objetos cargados en memoria
    if (mallas.empty()) {
        cout << "Ningún objeto ha sido cargado en memoria." << endl;
        return;
    }

    // Buscar el objeto en memoria
    Malla* objetoEncontrado = nullptr;
    for (auto& malla : mallas) {
        if (malla.getNombre() == nombreObjeto) {
            objetoEncontrado = &malla;
            break;
        }
    }

    if (objetoEncontrado == nullptr) {
        cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << endl;
        return;
    }

    // Verificar si ya existe la caja envolvente del objeto
    string nombreEnvolvente = "env_" + nombreObjeto;
    bool envolventeExiste = false;

    for (const auto& malla : mallas) {
        if (malla.getNombre() == nombreEnvolvente) {
            envolventeExiste = true;
            break;
        }
    }

    // Si no existe la caja envolvente, crearla
    if (!envolventeExiste) {
        envolvente(nombreObjeto, false);
    }

    // Obtener la caja envolvente del objeto
    Malla* cajaEnvolvente = nullptr;
    // Después de crearla, buscarla nuevamente
            for (auto& malla : mallas) {
                if (malla.getNombre() == nombreEnvolvente) {
                    cajaEnvolvente = &malla;
                    break;
                }
            }

    // Obtener los vértices de la caja envolvente
    list<Vertice*> envolventeVertices = cajaEnvolvente->getVertices();

    // Crear un árbol K-d para los vértices del objeto
    list<Vertice*> vertices = objetoEncontrado->getVertices();
    ArbolKD arbol;
    for (Vertice* vertice : vertices) {
        arbol.insertar(vertice);
    }

    // Mostrar el resultado en pantalla
    cout << "Los vertices del objeto " << nombreObjeto << " más cercanos a las esquinas de su caja envolvente son:" << endl;
    cout << "     Esquina         " << "      Vertice      " << "    Distancia" << endl;

    // Buscar el vértice más cercano a cada esquina de la caja envolvente
    int indiceEsquina = 1;
    for (auto it = envolventeVertices.begin(); it != envolventeVertices.end(); ++it) {
        Vertice* esquina = *it;
        Vertice* mejorVertice = nullptr;
        double mejorDistancia = numeric_limits<double>::max();

        mejorVertice = arbol.buscarCercano(arbol.getRaiz(), esquina->getX(), esquina->getY(), esquina->getZ(), 0, mejorVertice, mejorDistancia);

        // Buscar el índice del mejor vértice
        int indice = 0;
        for (Vertice* vertice : vertices) {
            if (vertice == mejorVertice) {
                break;
            }
            indice++;
        }

        // Imprimir los resultados
        cout << indiceEsquina++ << "\t(" << esquina->getX() << ", " << esquina->getY() << ", " << esquina->getZ() << ")\t"
             << indice << "\t(" << mejorVertice->getX() << ", " << mejorVertice->getY() << ", " << mejorVertice->getZ() << ")\t"
             << mejorDistancia << endl;
    }
}
