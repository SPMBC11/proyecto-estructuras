#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include "gestorMallas.h"
using namespace std;

class Menu{
public:
    void helpCommand();
    string getCommand();
protected:
    GestorMallas gestor;  // Instancia global de GestorMallas
};

#endif