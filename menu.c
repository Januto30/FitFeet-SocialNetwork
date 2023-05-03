#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void menu() {
    printf("=========================================\n");
    printf("|           Benvingut a Feetfit         |\n");
    printf("=========================================\n");
    printf("| 1. Insereix nou usuari                |\n");
    printf("| 2. Llistar tots els usuaris exsistens |\n");
    printf("| 3. Iniciar sessio                     |\n");
    printf("| 4. Sortir                             |\n");
    printf("=========================================\n");
    printf("Selecciona una opcio: ");
}

int select_option() {
    int option;
    while (1) {
        if (scanf("%d", &option) != 1) {
            while (getchar() != '\n');
        } else if (option >= 1 && option <= 4) {
            printf("\n");
            printf("\n");
            return option;
        }
        printf("Opcio incorrecta. Torna a intentar.\n");
    }
}

int print_option(int option, user_list *Llista){
    if (option == 1){
        User *usuari = (User *) malloc(sizeof(User));
        printf("------INSERTAR NOU USUARI------\n");
        emmagatzema_dades(usuari);
        afegir_usuari(Llista, usuari);

    } else if (option == 2){
        printf("------LLISTAR TOTS ELS USUARIS EXSISTENTS------\n");
        print_users(Llista);
    } else if (option == 3){
        char usuari[MAX_LENGTH];
        printf("\n---Quin usuari ets?---\n");
        print_users(Llista);
        scanf("%s", usuari);
        User *current = Llista -> head;
        while (current != NULL) {
            if (strcmp(usuari, current -> nom) == 0) {
                checkPassword(current);
            }
            current = current -> next;
        }
        printf("\n");
        printf("---| 1. Enviar solicituds d'amistat   |---\n");
        printf("---| 2. Gestionar solicituds pendents |---\n");
        printf("---| 3. Realitzar una publicacio      |---\n");
        printf("---| 4. Llistar les publicacions      |---\n");
        printf("\n");
    } else if (option == 4) {
        return 1;
    }
}