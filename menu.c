#include  "menu.h"
#include  "SOCIAL.h"
#include  "USUARI.h"

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <unistd.h>
#include  <stdbool.h>
#include  <ctype.h>


/// ---------------- MENÚ ----------------
void menu() {
    printf("\n");
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

int print_option(int option, user_list *Llista, st_Diccionari* TaulaHash) {
    if (option == 1) {
        User *usuari = (User *) malloc(sizeof(User));       // crea un nou usuari amb memòria dinàmica
        printf("------INSERTAR NOU USUARI------\n");
        emmagatzema_dades(usuari, Llista);
        afegir_usuari(Llista, usuari);
        return 0;

    } else if (option == 2) {
        printf("------LLISTAR TOTS ELS USUARIS EXISTENTS------\n");
        print_users(Llista);
        sleep(1.5);
        return 0;

    } else if (option == 3) {
        menu_usuari(Llista, TaulaHash);
        return 0;

    } else if (option == 4) {
        return 1;
    }
}


/// ---------------- OPCIONS DE MENÚ ----------------
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
}

/*
void print_users(user_list *Llista) {
    User *current = Llista -> head;         // current apunta al primer usuari de la llista
    while (current != NULL) {               // mentre la llista no estigui buida...
        printf("          |    %s    |\n", current -> nom);         // imprimeix el nom d'usuari
        current = current -> next;          // ara current avança fins al següent element de la llista, i els va imprimint
    }
    printf("\n");
}
*/

void print_users(user_list* Llista) {
    Queue queue;
    inicialitzarQueue(&queue);

    User* current = Llista -> head;         // el current és el primer de la llista
    while (current != NULL) {               // si la llista no està buida, entrem al bucle
        enqueue(&queue, current -> nom);    // fica el usuari current dins la cua
        current = current -> next;          // el current és el següent de la llista
    }

    while(!isQueueEmpty(&queue)) {                                      // mentres la cua no estigui buida, entrem al bucle, per escriure cada nom dels usuaris
        printf("          |    %s    |\n", queue.head -> nom);
        dequeue(&queue);
    }
}

void menu_usuari(user_list *Llista, st_Diccionari* TaulaHash) {
    char usuari[MAX_LENGTH];                        // guarda el nom del usuari
    int opcio3, permis;

    printf("\n---Quin usuari ets?---\n");
    print_users(Llista);
    sleep(1.5);

    while (1) {                                     // bucle infinit per verificar que l'usuari s'introdueix correctament
        scanf("%s", usuari);

        User *current = Llista -> head;                 // es declara una variable local del tipus punter a User (current), que comença apuntant al head de la llista
        while (current != NULL) {
            if (strcmp(usuari, current -> nom) == 0) {
                permis = 0;
                break;
            }
            current = current -> next;
        }
        if (current != NULL) {
            break;
        }
        printf("Usuari incorrecta, torna a provar: \n");
    }

    int verif = 0;
    User *current = Llista -> head;                 // es declara una variable local del tipus punter a User (current), que comença apuntant al head de la llista
    while (current != NULL) {                       // mentre no s'hagi arribat al final de la llista...
        while (verif == 0) {
            if (strcmp(usuari, current -> nom) == 0) {  // compara el nom guardat a usuari amb el node actual de la llista
                if (checkPassword(current) == 1) {
                    permis = 0;
                    verif = 1;
                }
            } else {
                current = current -> next;                  // actualitza el valor de current, ara apunta al següent node de la llista
                verif = 0;
            }
        }

        if (permis == 0) {
            printf_menu_usuari();
            printf("Tria l'opcio desitjada: ");
            scanf("%d", &opcio3);

            if (opcio3 == 1) {
                while (opcio3 == 1){
                    print_user_info(current);

                    if (resp_bol() == 1) {
                        char option_3_1[MAX_LENGTH];
                        printf("Quina? ");
                        canvi_de_dades(option_3_1, current);
                    } else {
                        break;
                    }
                }

            } else if (opcio3 == 2) {
                enviar_solicitud(Llista, current);
                current = Llista -> head;

            } else if (opcio3 == 3) {
                if (current -> num_solicituds == 0) {
                    printf("No tens sol.licituds d'amistat pendents.\n");
                }
                else {
                    acceptar_denegar_solicituds(current);
                }

            } else if (opcio3 == 4) {
                //Aqui hem de llistar els nostres amics
                llistar_amics_acceptats(current);
                sleep(1.5);

            } else if (opcio3 == 5) {
                fer_publicacio(current, TaulaHash);

            } else if (opcio3 == 6) {
                Timeline(current);

            } else if (opcio3 == 7) {
                trending(TaulaHash);

            } else if(opcio3 == 8) {
                print_quilometres((User*)usuari);

            } else if(opcio3 == 9) {
                break;
            }
        }
    }
}

void printf_menu_usuari() {
    printf("\n");
    printf("---| 1. Perfil                          |---\n");
    printf("---| 2. Enviar sol.licituds d'amistat   |---\n");
    printf("---| 3. Acceptar/denegar sol.licituds   |---\n");
    printf("---| 4. Llista d'amics                  |---\n");
    printf("---| 5. Realitzar una publicacio        |---\n");
    printf("---| 6. Llistar les publicacions        |---\n");
    printf("---| 7. Llistar paraules TOP            |---\n");
    printf("---| 8. Total de quilòmetres recorreguts|---\n");
    printf("---| 9. Sortir                          |---\n");
}


/// ---------------- AUXILIARS ----------------
bool comprovar_correu(char *correu) {
    int longitud = strlen(correu);
    int posArroba = 0;
    bool teArroba = false;
    bool tePunt = false;

    if (longitud < 5) {     // Almenys 5 caràcters
        return false;
    }

    for (int i = 0; i < longitud; i++) {        // Comprovar que només té un '@'
        if (correu[i] == '@') {
            if (teArroba) {
                return false;

            } else {
                teArroba = true;
                posArroba = i;
            }
        }
    }

    if (!teArroba) {
        return false;
    }

    for (int i = posArroba + 1; i < longitud; i++) {       // Comprovar que només té un '.'
        if (correu[i] == '.') {
            tePunt = true;
            break;
        }
    }

    if (!tePunt) {
        return false;
    }

    return true;
}

bool comprovar_usuari(user_list* llista, char* nom) {
    User* temp = llista -> head;
    while (temp != NULL) {
        if (strcmp (temp -> nom, nom) == 0) {
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

int resp_bol() {
    char resposta[10];
    bool respostaValida = false;

    printf("Vols modificar alguna opcio? (si/no): ");

    while (!respostaValida) {
        scanf("%s", resposta);

        for (size_t i = 0; i < strlen(resposta); i++) {
            resposta[i] = tolower(resposta[i]);
        }

        if (strcmp(resposta, "si") == 0) {
            respostaValida = true;
            return 1;

        } else if (strcmp(resposta, "no") == 0) {
            respostaValida = true;
            return 0;

        } else {
            printf("Resposta invalida. Introdueix una resposta correcta ('si', 'no').\n");
        }
    }
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


/// ---------------- QUEUE FUNCTIONS ----------------
void inicialitzarQueue(Queue* queue) {      // funció per inicialitzar la cua
    queue -> head = NULL;
    queue -> last = NULL;
}

int isQueueEmpty(Queue* queue) {            // funció per comprovar que la cua està buida o no
    return (queue -> head == NULL);
}

void enqueue(Queue* queue, char* nom) {                     // funció per afegir usuaris dins la cua
    User* usuari_nou = (User*) malloc(sizeof(User));   // reservem memòria pel nou usuari
    strcpy(usuari_nou -> nom, nom);             // copiem el nom
    usuari_nou -> next = NULL;                              // el nou usuari és el darrer

    if (isQueueEmpty(queue)) {          // si la cua està buida, el nou usuari és el primer i darrer de la cua
        queue -> head = usuari_nou;
        queue -> last = usuari_nou;

    } else {                                // si no, el nou usuari és el darrer de la cua
        queue -> last -> next = usuari_nou;
        queue -> last = usuari_nou;
    }
}

void dequeue(Queue* queue) {                    // funció per eliminar el primer usuari de la cua
    if (isQueueEmpty(queue)) {                  // si la cua està buida
        printf("La cua esta buida.\n");
        return;
    }

    User* temporal = queue -> head;             // es guarda el primer usuari a una variable temporal
    queue -> head = queue -> head -> next;      // ara el primer és el següent de la llista
    free(temporal);                     // s'elimina el primer
}