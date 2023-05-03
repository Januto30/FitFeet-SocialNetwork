#include "menu.h"
#include <stdio.h>

int main() {
    int a = 1;
    user_list Llista;
    Llista.head = NULL;
    Llista.num_persones = 0;
    while (a != 0) {
        int option1;
        menu();
        option1 = select_option();
        print_option(option1, &Llista);
    }
    return 0;
}
