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
    printf("| 2. Llistar tots els usuaris existents |\n");
    printf("| 3. Iniciar sessio                     |\n");
    printf("| 4. Sortir                             |\n");
    printf("=========================================\n");
    printf("Selecciona una opcio: ");
}

int select_option() {
    int option;     // variable per guardar el valor introduït per l'usuari
    while (1) {     // entra en un bucle infinit
        if (scanf("%d", &option) != 1) {      // intenta llegir un enter i comprova si s'ha llegit correctament
            while (getchar() != '\n');              // si la lectura no ha sigut correcte, esborra el contingut del buffer?
        } else if (option >= 1 && option <= 4) {    // comprova que 1 i 4 són opcions vàlides
            printf("\n");
            printf("\n");
            return option;
        }
        printf("Opcio incorrecta. Torna a intentar.\n");
    }
}

int print_option(int option, user_list *Llista) {
    if (option == 1) {
        User *usuari = (User *) malloc(sizeof(User));       // crea un nou usuari amb memòria dinàmica
        printf("------INSERTAR NOU USUARI------\n");
        emmagatzema_dades(usuari);
        afegir_usuari(Llista, usuari);

    } else if (option == 2) {
        printf("------LLISTAR TOTS ELS USUARIS EXISTENTS------\n");
        print_users(Llista);

    } else if (option == 3) {
        opcio3(Llista);

    } else if (option == 4) {
        return 1;
    }
}

void emmagatzema_dades(User *usuari) {         // canviar ordre de preguntes

    printf("Introdueix el teu nom: \n");
    scanf("%s", usuari -> nom);

    printf("Introdueix la contrasenya: \n");
    scanf("%s", usuari -> password);

    printf("Introdueix el teu primer cognom: \n");
    scanf("%s", usuari -> cognom1);

    printf("Introdueix el teu segon cognom: \n");
    scanf("%s", usuari -> cognom2);

    printf("Introdueix la teva edat: \n");
    scanf("%d", &usuari -> edat);      // es fa servir el & perquè és un enter

    printf("Introdueix el teu correu electronic: \n");      //// hem de comprovar que el correu s'escriu correctament
    scanf("%s", usuari -> correu);

    printf("Introdueix la teva ubicacio: \n");
    scanf("%s", usuari -> ubi);

    printf("Introdueix els teus 5 gustos preferits (un per linia):\n");
    scanf("%s", usuari -> gust1);
    scanf("%s", usuari -> gust2);
    scanf("%s", usuari -> gust3);
    scanf("%s", usuari -> gust4);
    scanf("%s", usuari -> gust5);

    usuari -> next = NULL;                  // així sabem quan s'ha arribat al final de la llista en recórrer-la
}

void afegir_usuari(user_list* llista, User* usuari) {
    if (llista -> head == NULL) {           // si la llista esta buida...
        llista -> head = usuari;            // el primer element de la llista és el usuari nou
    } else {                                // si la llista no està buida...
        User* temp = llista -> head;        // temp apunta al head
        while (temp -> next != NULL) {      // mentre no s'hagi arribat al final de la llista...
            temp = temp -> next;            // temp avança al següent element de la llista (fins que arribi al final)
        }
        temp -> next = usuari;              // afegeix un usuari nou al final de la llista
    }
    llista -> num_persones++;               // s'actualitza el nombre de elements de la llista
}

void print_users(user_list *Llista) {
    User *current = Llista -> head;         // current apunta al primer usuari de la llista
    while (current != NULL) {               // mentre la llista no estigui buida...
        printf("          |    %s    |\n", current -> nom);         // imprimeix el nom d'usuari
        current = current -> next;          // ara current avança fins al següent element de la llista, i els va imprimint
    }
    printf("\n");
}

int checkPassword(User *usuari) {
    char input[20];
    int correct = 0;

    while (!correct) {
        printf("Introdueix la contrasenya: ");
        scanf("%s", input);                           // guarda la contrasenya introduïda per l'usuari

        if (strcmp(input, usuari -> password) == 0) {       // comparem la contrasenya introduïda amb l'actual
            printf("Benvingut %s!,\n", usuari -> nom);
            correct = 1;
            return 1;
        } else {
            printf("Contrasenya incorrecta. Intenta-ho de nou.\n");
            return 0;
        }
    }
}

void enviar_solicituds(User *usuari1) {
    User usuari2;
    = scanf("Introdueix el nom del usuari a qui vols enviar la solicitud d'amistat: \n");
    solicituds solicitud;
    strcpy(solicitud.sender, usuari1 -> nom);
    strcpy(solicitud.receptor, &usuari2);
    solicitud.status = 0;           // sol·licitud en pendent

    usuari2 -> solicituds_amistat = solicitud;

    printf("Has enviat una solicitud d'amistat a %s", usuari2 -> nom);
}

/*
void mostrar_solicituds(User *usuari) {
    int num_solicituds_pendents = 0;
    solicituds *solicituds_pendents[MAX_SOLICITUDS];

    for (int i = 0; usuari -> num_amics; i++) {
        if (usuari -> )
    }
}
 */

void opcio3(user_list *Llista) {
    char usuari[MAX_LENGTH];                        // guarda el nom del usuari
    printf("\n---Quin usuari ets?---\n");
    print_users(Llista);
    scanf("%s", usuari);

    User *current = Llista -> head;                 // es declara una variable local del tipus punter a User (current), que comença apuntant al head de la llista
    while (current != NULL) {                       // mentres no s'hagi arribat al final de la llista...
        if (strcmp(usuari, current -> nom) == 0) {  // compara el nom guardat a usuari amb el node actual de la llista
            if (checkPassword(current) == 1){
                printf("\n");
                printf("---| 1. Perfil                        |---\n");
                printf("---| 2. Enviar solicituds d'amistat   |---\n");
                // funcio enviar solitituds
                printf("---| 3. Gestionar solicituds pendents |---\n");
                // funcio mostrar solicituds
                printf("---| 4. Realitzar una publicacio      |---\n");
                printf("---| 5. Llistar les publicacions      |---\n");
                printf("\n");
            }
        }
        current = current -> next;                  // actualitza el valor de current, ara apunta al següent node de la llista

        char opcio;
        scanf("%s", opcio);

        if (opcio == 1) {
            printf("╔════════════════════════╗\n");
            printf("║     Dades personals    ║\n");
            printf("╠════════════════════════╣\n");
            printf("║ Nom:      %s\n", current->nom);
            printf("║ Cognom:   %s\n", current->cognom1);
            printf("║ 2n Cognom: %s\n", current->cognom2);
            printf("║ Edat:     %d\n", current->edat);
            printf("║ Correu:   %s\n", current->correu);
            printf("║ Ubicació: %s\n", current->ubi);
            printf("╠════════════════════════╣\n");
            printf("║         Gustos         ║\n");
            printf("╠════════════════════════╣\n");
            printf("║ Gust 1:   %s\n", current->gust1);
            printf("║ Gust 2:   %s\n", current->gust2);
            printf("║ Gust 3:   %s\n", current->gust3);
            printf("║ Gust 4:   %s\n", current->gust4);
            printf("║ Gust 5:   %s\n", current->gust5);
            printf("╚════════════════════════╝\n");

            printf("Vols canviar alguna dada teva?")
            if(scanf("%s")== "Sí"){

        }


        } else if (opcio == 2) {
            printf("Envia solicitud a: ");
            receptor
            enviar_solicituds(usuari, receptor);


        } else if (opcio == 3) {


        } else if (opcio == 4) {


        } else if (opcio == 5) {


        }
    }
}

void guardar_usuaris_en_arxiu(user_list* Llista) {
    FILE* arxiu = fopen("../PERFIL.txt", "w");

    if (arxiu == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    User* current = Llista->head;
    while (current != NULL) {
        fprintf(arxiu, "%s %s %s %s %d %s %s %s %s %s %s %s\n", current->nom, current->password, current->cognom1, current->cognom2, current->edat, current->correu, current->ubi, current->gust1, current->gust2, current->gust3, current->gust4, current->gust5);
        current = current->next;
    }

    fclose(arxiu);
}

void llegir_usuaris_desde_arxiu(user_list* Llista) {
    FILE* arxiu = fopen("../PERFIL.txt", "r");

    if (arxiu == NULL) {
        printf("No s'ha pogut obrir l'arxiu.\n");
        return;
    }
    char nom[MAX_LENGTH], password[MAX_LENGTH], cognom1[MAX_LENGTH], cognom2[MAX_LENGTH], correu[MAX_LENGTH], ubi[MAX_LENGTH], gust1[MAX_LENGTH], gust2[MAX_LENGTH], gust3[MAX_LENGTH], gust4[MAX_LENGTH], gust5[MAX_LENGTH];
    int edat;
    while (fscanf(arxiu, "%s %s %s %s %d %s %s %s %s %s %s %s", nom, password, cognom1, cognom2, &edat, correu, ubi, gust1, gust2, gust3, gust4, gust5) == 12) {
        User* user = (User*)malloc(sizeof(User));
        strcpy(user->nom, nom);
        strcpy(user->password, password);
        strcpy(user->cognom1, cognom1);
        strcpy(user->cognom2, cognom2);
        user->edat = edat;
        strcpy(user->correu, correu);
        strcpy(user->ubi, ubi);
        strcpy(user->gust1, gust1);
        strcpy(user->gust2, gust2);
        strcpy(user->gust3, gust3);
        strcpy(user->gust4, gust4);
        strcpy(user->gust5, gust5);
        user->next = NULL;

        if (Llista->head == NULL) {
            Llista->head = user;
        } else {
            User* current = Llista->head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = user;
        }
    }

    fclose(arxiu);
}