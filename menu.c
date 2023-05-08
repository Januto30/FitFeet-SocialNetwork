#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USERS 100

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
    int option;//variable per guardar el valor introduït per l'usuari
    while (1) { //entra en un bucle infinit
        if (scanf("%d", &option) != 1){//intenta llegir un enter i comprova si s'ha llegit correctament
            while (getchar() != '\n');//si la lectura no ha sigut correcte, esborra el contingut del buffer?
        } else if (option >= 1 && option <= 4) {//comprova que 1 i 4 són opcions vàlides
            printf("\n");
            printf("\n");
            return option;
        }
        printf("Opcio incorrecta. Torna a intentar.\n");
    }
}

int print_option(int option, user_list *Llista){
    if (option == 1){
        User *usuari = (User *) malloc(sizeof(User));//crea un nou usuari amb memòria dinàmica
        printf("------INSERTAR NOU USUARI------\n");
        emmagatzema_dades(usuari);
        afegir_usuari(Llista, usuari);

    } else if (option == 2){
        printf("------LLISTAR TOTS ELS USUARIS EXSISTENTS------\n");
        print_users(Llista);
    } else if (option == 3){
        char usuari[MAX_LENGTH];//guarda el nom del usuari
        printf("\n---Quin usuari ets?---\n");
        print_users(Llista);
        scanf("%s", usuari);
        User *current = Llista -> head;//es declara una variable local del tipus punter a User (current), que comença apuntant al head de la llista
        while (current != NULL) { //mentres no s'hagi arribat al final de la llista...
            if (strcmp(usuari, current -> nom) == 0) {//compara el nom guardat a usuari amb el node actual de la llista
                checkPassword(current);
            }
            current = current -> next; //actualitza el valor de current, ara apunta al següent node de la llista
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

void emmagatzema_dades(User *usuari) {
    printf("Introdueix el teu nom: \n");
    scanf("%s", usuari -> nom);
    printf("Introdueix la contrasenya: \n");
    scanf("%s", usuari -> password);
    printf("Introdueix el teu primer cognom: \n");
    scanf("%s", usuari -> cognom1);
    printf("Introdueix el teu segon cognom: \n");
    scanf("%s", usuari -> cognom2);
    printf("Introdueix la teva edat: \n");
    scanf("%d", &usuari -> edat); //es fa servir el & perquè és un enter
    printf("Introdueix el teu correu electronic: \n");
    scanf("%s", usuari -> correu);
    printf("Introdueix la teva ubicacio: \n");
    scanf("%s", usuari -> ubi);
    printf("Introdueix els teus 5 gustos preferits (un per linia):\n");
    scanf("%s", usuari -> gust1);
    scanf("%s", usuari -> gust2);
    scanf("%s", usuari -> gust3);
    scanf("%s", usuari -> gust4);
    scanf("%s", usuari -> gust5);
    usuari -> next = NULL; //així sabem quan s'ha arribat al final de la llista en recórrer-la
}

void afegir_usuari(user_list* llista, User* usuari) {
    if (llista -> head == NULL) { //si la llista esta buida...
        llista -> head = usuari; //el primer element de la llista és el usuari nou
    } else { //si la llista no està buida...
        User* temp = llista -> head; //temp apunta al head
        while (temp -> next != NULL) { //mentres no s'hagi arribat al final de la llista...
            temp = temp -> next; //temp avança al següent element de la llista (fins que arribi al final)
        }
        temp -> next = usuari; //afegeix un usuari nou al final de la llista
    }
    llista -> num_persones++; //s'actualitza el nombre de elements de la llista
}

void print_users(user_list *Llista) {
    User *current = Llista -> head; //current apunta al primer usuari de la llista
    while (current != NULL) { //mentres la llista no estigui buida...
        printf("          |    %s    |\n", current -> nom);//imprimeix el nom d'usuari
        current = current -> next; //ara current avança final a següent element de la llista, i els va imprimint
    }
    printf("\n");
}

void checkPassword(User *usuari) {
    char input[20];
    int correct = 0;

    while (!correct) {
        printf("Introdueix la contrasenya: ");
        scanf("%s", input); //guarda la contrasenya introduïda per l'usuari

        if (strcmp(input, usuari -> password) == 0) { //comparem la contrasenya introduïda amb l'actual
            printf("Benvingut %s!,\n",usuari -> nom);
            correct = 1;
        } else {
            printf("Contrasenya incorrecta. Intenta-ho de nou.\n");
        }
    }
}