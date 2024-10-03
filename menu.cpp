#include <iostream>
#include <sstream>
#include "menu.h"
#include "malla.h"
#include "gestorMallas.h"

using namespace std;


string Menu::getCommand() {
    //string in;
    string command;
    //string other;
    cout << "$ ";
    getline(cin, command);
        // Usar un stringstream para separar el comando y el argumento
        string operacion;
        string argumento1, argumento2, argumento3, argumento4;

        // Dividimos la entrada en la primera palabra (operacion) y los dos argumentos
        stringstream ss(command);
        ss >> operacion >> argumento1 >> argumento2 >> argumento3 >> argumento4;

        // Eliminar espacios en blanco al inicio de los argumentos
        argumento1.erase(0, argumento1.find_first_not_of(" \t"));
        argumento2.erase(0, argumento2.find_first_not_of(" \t"));
        argumento3.erase(0, argumento2.find_first_not_of(" \t"));
        argumento4.erase(0, argumento2.find_first_not_of(" \t"));

    cout << endl;
    if (operacion == "cargar") {
            if (!argumento1.empty()) {
                string nombreArchivo = argumento1;
                gestor.cargar(nombreArchivo);
            } else {
                cout << "Opcion no valida." << endl;
            }
    cout << endl;
    }

    else if (operacion == "listado") {
        gestor.listado();
        cout << endl;
    }

    else if (operacion == "envolvente" && !argumento1.empty()) {
        string nombreObjeto = argumento1;
        gestor.envolvente(nombreObjeto, false);
        cout << endl;
    }
    else if (operacion == "envolvente") {
        gestor.envolvente(argumento1, true);
        cout << endl;
    }
    else if (operacion == "descargar") {

        if (!argumento1.empty()) {
                string nombreObjeto = argumento1;
                gestor.descargar(nombreObjeto);
            } else {
                cout << "Opcion no valida." << endl;
            }
    cout << endl;
    }
    else if (operacion == "guardar") {
        if (!argumento1.empty() && !argumento2.empty()) {
                string nombreObjeto = argumento1;
                string nombreArchivo = argumento2;
                gestor.guardar(nombreObjeto, nombreArchivo);
            } else if (argumento1.empty()){
                cout << "Opcion no valida." << endl;
            } else if (argumento2.empty()){
                cout << "Opcion no valida." << endl;
            }
    cout << endl;
    }
    else if (operacion == "v_cercano" && !argumento1.empty() && !argumento2.empty() && !argumento3.empty() && !argumento4.empty()) {
                double px = stod(argumento1);
                double py = stod(argumento2);
                double pz = stod(argumento3);
                string nombreObjeto = argumento4;
                gestor.vCercano(px, py, pz, nombreObjeto, false);
                cout << endl;
    }
    else if (operacion == "v_cercano" && !argumento1.empty() && !argumento2.empty() && !argumento3.empty() && argumento4.empty()) {
                double px = stod(argumento1);
                double py = stod(argumento2);
                double pz = stod(argumento3);
                gestor.vCercano(px, py, pz, argumento4, true);
                cout << endl;
    }
    else if (operacion == "v_cercanos_caja") {
        if (!argumento1.empty()) {
                string nombreObjeto = argumento1;
                gestor.vCercanosCaja(nombreObjeto);
            } else {
                cout << "Opcion no valida." << endl;
            }
    cout << endl;
    }
    else if (operacion == "ayuda") {
        helpCommand();
        cout << endl;
    }
    else if (operacion == "salir") {
        cout << "Saliendo del programa..." << endl;
    }
    else {
        cout << "Opcion no valida." << endl;
        cout << endl;
    }
    return operacion;
}


void Menu::helpCommand() {
    cout << endl << "Comandos disponibles:" << endl << endl;

    cout << "1. cargar nombre_archivo" << endl;
    cout << "-> Carga en memoria la informacion del objeto nombre_objeto contenida en el archivo \n identificado por nombre_archivo . El comando debe estructurar la informacion a partir del archivo \n de forma que sea facil recuperar los datos posteriormente." << endl << endl;

    cout << "2. listado" << endl;
    cout << "-> Lista los objetos cargados actualmente en memoria, junto con la informacion basica \n de cada uno: cantidad de puntos, de aristas y de caras" << endl << endl;

    cout << "3. envolvente nombre_objeto" << endl;
    cout << "-> Calcula la caja envolvente del objeto identificado por nombre_objeto . Esta caja \n envolvente se define a partir de dos puntos, pmin y pmax, los cuales determinan los limites de \n una especie de cuarto donde cabe el objeto completo, es decir, todos los vertices del objeto se \n encuentran contenidos dentro de la caja (ver figura a continuacion). pmin y pmax se calculan \n como los puntos extremos, en cada dimension, del conjunto de vertices que define el objeto. La \n caja envolvente se agrega como un nuevo objeto en memoria, asignandole automaticamente el \n nombre env_nombre_objeto , para distinguirla de los demas objetos en memoria." << endl << endl;

    cout << "4. envolvente" << endl;
    cout << "-> Calcula la caja envolvente que incluye a todos los objetos cargados actualmente en \n memoria. Esta caja envolvente se calcula de la misma forma que en el comando anterior, solo que \n teniendo en cuenta todos los vertices de todos los objetos en memoria, para no dejar ninguno por \n fuera de la caja. La caja envolvente se agrega como un nuevo objeto en memoria, asignandole \n automaticamente el nombre env_global , para distinguirla de los demas objetos en memoria. \n " << endl << endl;

    cout << "5. descargar nombre_objeto" << endl;
    cout << "-> Descarga de la memoria toda la informacion basica (vértices, aristas, caras) del objeto \n identificado por nombre_objeto." << endl << endl;

    cout << "6. guardar nombre_objeto nombre_archivo" << endl;
    cout << "->  Escribe en un archivo de texto, identificado por nombre_archivo , la informacion \n basica (vertices y caras) del objeto identificado por nombre_objeto" << endl << endl;

    cout << "7. v_cercano px py pz nombre_objeto" << endl;
    cout << "-> Identifica el vértice del objeto nombre_objeto más cercano al punto dado por las coordenadas (px, py, pz). Informa el índice del vértice, sus coordenadas, y la distancia al punto" << endl << endl;;

    cout << "8. v_cercano px py pz" << endl;
    cout << "-> Identifica el vértice más cercano al punto (px, py, pz) entre todos los objetos cargados en memoria. Informa el objeto al que pertenece, el índice del vértice, sus coordenadas, y la distancia al punto" << endl << endl;

    cout << "9. v_cercanos_caja nombre_objeto" << endl;
    cout << "-> Identifica los vértices del objeto nombre_objeto más cercanos a las esquinas de su caja envolvente. Muestra una tabla con las coordenadas de las esquinas de la caja envolvente y para cada una, el índice del vértice más cercano, sus coordenadas y la distancia a la esquina correspondiente." << endl << endl;

    cout << "10. ayuda" << endl;
    cout << "-> Imprime en consola el menu presente" << endl << endl;

    cout << "11. salir" << endl;
    cout << "-> Termina la ejecución de la aplicación." << endl << endl;
}
