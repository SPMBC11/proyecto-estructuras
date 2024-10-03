#include <iostream>
#include "menu.h"

using namespace std;

int main (){/**<  */
  Menu menu;
  string comando;

  while (comando != "salir") {
     comando = menu.getCommand();
  }


}
