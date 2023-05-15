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

    printf("Introdueix el teu correu electronic: \n");
    scanf("%s", usuari -> correu);
    comprovar_correu(usuari, usuari -> correu);         // funció per validar que el correu està ben escrit

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

void comprovar_correu(User *usuari, char *correu) {
    while(1) {
        if ((strchr(usuari -> correu, '@') == NULL) || strchr(usuari -> correu, '.') == NULL) {
            printf("El correu es invalid. Torna a introduir el teu correu: \n");
            scanf("%s", usuari -> correu);
        } else {
            printf("El correu es valid.\n\n");
            break;
        }
    }
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

/*int enviar_solicitud(User* emisor, User* receptor) {
    // Mirem que els paràmetres no estiguin buits
    if (emisor == NULL || receptor == NULL) {
        return -1;
    }
    //Comprovem que emisor i receptor no siguin els mateixos
    if (emisor == receptor) {
        return -1;
    }
    //Mirem si el emisor no tingui ja al receptor com a amic
    for (int i = 0; i < emisor->num_amics; i++) {
        if (emisor->amics[i] == receptor) {
            return -1;
        }
    }
    //Mirem si el receptor no tingui ja al emisor com a amic
    for (int i = 0; i < receptor->num_amics; i++) {
        if (receptor->amics[i] == emisor) {
            return -1;
        }
    }
    //Comprovem que el emisor no hagi enviat ja una solicitud d'amistat al receptor
    for (int i = 0; i < emisor->num_solicituds; i++) {
        if (emisor->solicituds[i] == receptor) {
            return -1;
        }
    }
    //Mirem que el receptor no hagi rebut ja una solicitud del emisor
    for (int i = 0; i < receptor->num_solicituds; i++) {
        if (receptor->solicituds[i] == emisor) {
            return -1;
        }
    }
    //si no hi ha errors, afegim la solicitud a la llista del receptor
    receptor->solicituds[receptor->num_solicituds] = emisor;
    receptor->num_solicituds++;

    return 0;
}
*/



/*
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
*/
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
    int opcio3, permis;
    printf("\n---Quin usuari ets?---\n");
    print_users(Llista);
    scanf("%s", usuari);

    User *current = Llista->head;                 // es declara una variable local del tipus punter a User (current), que comença apuntant al head de la llista
    while (current != NULL) {                       // mentres no s'hagi arribat al final de la llista...
        if (strcmp(usuari, current->nom) == 0) {  // compara el nom guardat a usuari amb el node actual de la llista
            if (checkPassword(current) == 1) {
                printf_menu(); //¡¡¡Aquí el menu no s'imprimeix quan toca!!!
                permis = 0;
            }
        } else {
            current = current->next;                  // actualitza el valor de current, ara apunta al següent node de la llista
        }
        /// Tot aquest tros del codi no pot anar aquí ja que en la línia 172 (la se a sobre) itera el usuari en qüestió.
        if (permis == 0) {
            printf("Tria l'opcio desitjada: ");
            scanf("%d", &opcio3);
            if (opcio3 == 1) {
                char option_3[10];
                printf("==========================\n");
                printf("|     Dades personals    |\n");
                printf("|========================|\n");
                printf("| Nom:      %s\n", current->nom);
                printf("| Cognom:   %s\n", current->cognom1);
                printf("| 2n Cognom: %s\n", current->cognom2);
                printf("| Edat:     %d\n", current->edat);
                printf("| Correu:   %s\n", current->correu);
                printf("| Ubicacio: %s\n", current->ubi);
                printf("|========================|\n");
                printf("|         Gustos         |\n");
                printf("|========================|\n");
                printf("| Gust 1:   %s\n", current->gust1);
                printf("| Gust 2:   %s\n", current->gust2);
                printf("| Gust 3:   %s\n", current->gust3);
                printf("| Gust 4:   %s\n", current->gust4);
                printf("| Gust 5:   %s\n", current->gust5);
                printf("==========================\n");
                printf("Vols canviar alguna dada ?");
                scanf("%s", option_3);

                if (strcmp(option_3, "Sí") == 0 || strcmp(option_3, "Si") == 0) {
                    char option_3_1[MAX_LENGTH];
                    printf("Quina?");
                    scanf("%s", option_3_1);
                    if (strcmp(option_3_1, "Nom") == 0 || strcmp(option_3_1, "nom") == 0) {
                        scanf("%s", current->nom);
                    } else if (strcmp(option_3_1, "Cognom") == 0 || strcmp(option_3_1, "cognom") == 0) {
                        scanf("%s", current->cognom1);
                    } else if (strcmp(option_3_1, "2n Cognom") == 0 || strcmp(option_3_1, "2n cognom") == 0) {
                        scanf("%s", current->cognom2);
                    } else if (strcmp(option_3_1, "Edat") == 0 || strcmp(option_3_1, "edat") == 0) {
                        scanf("%s", current->edat);
                    } else if (strcmp(option_3_1, "Correu") == 0 || strcmp(option_3_1, "correu") == 0) {
                        scanf("%s", current->correu);
                    } else if (strcmp(option_3_1, "Ubicació") == 0 || strcmp(option_3_1, "ubicació") == 0) {
                        scanf("%s", current->ubi);
                    } else if (strcmp(option_3_1, "Gust 1") == 0 || strcmp(option_3_1, "gust 1") == 0) {
                        scanf("%s", current->gust1);
                    } else if (strcmp(option_3_1, "Gust 2") == 0 || strcmp(option_3_1, "gust 2") == 0) {
                        scanf("%s", current->gust2);
                    } else if (strcmp(option_3_1, "Gust 3") == 0 || strcmp(option_3_1, "gust 3") == 0) {
                        scanf("%s", current->gust3);
                    } else if (strcmp(option_3_1, "Gust 4") == 0 || strcmp(option_3_1, "gust 4") == 0) {
                        scanf("%s", current->gust4);
                    } else if (strcmp(option_3_1, "Gust 5") == 0 || strcmp(option_3_1, "gust 5") == 0) {
                        scanf("%s", current->gust5);
                    }
                    printf("Vols canviar alguna altre dada?");
                    scanf("%s", option_3);
                    if (strcmp(option_3, "Sí") == 0 || strcmp(option_3, "Si") == 0) {
                        opcio3 = 0;
                    } else {
                        break;
                    }


                }

            } else if (opcio3 == 2) {
                printf("Envia solicitud a: ");
                //enviar_solicitud(usuari, usuari);
                ///receptor
                ///enviar_solicituds(usuari, receptor);
            } else if (opcio3 == 3) {


            } else if (opcio3 == 4) {


            } else if (opcio3 == 5) {


            } else if (opcio3 == 6){
                break;
            }
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

void printf_menu(){
    printf("\n");
    printf("---| 1. Perfil                        |---\n");
    printf("---| 2. Enviar solicituds d'amistat   |---\n");
    // funcio enviar solitituds
    printf("---| 3. Gestionar solicituds pendents |---\n");
    // funcio mostrar solicituds
    printf("---| 4. Realitzar una publicacio      |---\n");
    printf("---| 5. Llistar les publicacions      |---\n");
    printf("---| 6. Sortir                        |---\n");
}
