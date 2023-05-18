 #include "menu.h"
#include <stdio.h>

int main() {
    int a = 1;
    user_list Llista;
    Llista.head = NULL;
    Llista.num_persones = 0;
    llegir_usuaris_desde_arxiu(&Llista);
    while (a != 0) {
        int option1;
        menu();
        option1 = select_option();
        if (print_option(option1, &Llista)==1){
            guardar_usuaris_en_arxiu(&Llista);
            break;
        }
    }
    return 0;
}
//dsfsd
