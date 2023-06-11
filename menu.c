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
    if (option == 1) {                                           //opció inserir nou usuari.
        User *usuari = (User *) malloc(sizeof(User));       // crea un nou usuari amb memòria dinàmica
        emmagatzema_dades(usuari, Llista);
        afegir_usuari(Llista, usuari);
        return 0;

    } else if (option == 2) {                                   //opció imprimir llista d'usuaris.
        print_users(Llista);
        sleep(1.5);
        return 0;

    } else if (option == 3) {                                   //opció per interactuar amb les opcions d'un usuari.
        menu_usuari(Llista, TaulaHash);
        return 0;

    } else if (option == 4) {                                   //Finalitzar amb el programa.
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

void print_users(user_list* Llista) {
    printf("------ LLISTA DE TOTS ELS USUARIS ------\n");

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

    printf("\n--- Quin usuari ets? ---\n");
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
            if (strcmp(usuari, current -> nom) == 0) {      // compara el nom guardat a usuari amb el node actual de la llista
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
                while (opcio3 == 1) {                                   //opció imprimir les dades de l'usuari.
                    print_user_info(current);

                    if (resp_bol() == 1) {
                        canvi_de_dades(current);                        //Permet canviar qualsevol dada de l'usuari.
                    } else {
                        break;
                    }
                }

            } else if (opcio3 == 2) {                                   //opció per enviar solicituts d'amistat.
                enviar_solicitud(Llista, current);
                current = Llista -> head;

            } else if (opcio3 == 3) {                                   //opció per gestionar les solicituts d'amistat.
                if (current -> num_solicituds == 0) {
                    printf("\nNo tens sol.licituds d'amistat pendents.\n");
                }
                else {
                    acceptar_denegar_solicituds(current);
                }

            } else if (opcio3 == 4) {                                   //opció per imprimir la llista d'amics.
                //Aqui hem de llistar els nostres amics
                llistar_amics_acceptats(current);
                sleep(1.5);

            } else if (opcio3 == 5) {                                   //opció per fer una nova publicació.
                fer_publicacio(current, TaulaHash);

            } else if (opcio3 == 6) {                                   //opció per imprimir totes les publicacions realitzades per un usuari.
                Timeline(current);

            } else if (opcio3 == 7) {                                   //opció per imprimir les 10 paraules més utlitzades.
                trending(TaulaHash);

            } else if(opcio3 == 8) {                                    //opció per imprimir el rànking dels usuaris segons el kiilòmetres recorreguts
                printf("\nRanking km recorreguts:\n");
                print_rankingKM(Llista, current);

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
    printf("---| 8. Ranking km recorreguts          |---\n");
    printf("---| 9. Sortir                          |---\n");
}


/// ---------------- AUXILIARS ----------------
bool comprovar_correu(char *correu) {
    int longitud = strlen(correu);      // longitud del correu
    int posArroba = 0;                      // variable per la posició del '@'
    bool teArroba = false;
    bool tePunt = false;

    if (longitud < 5) {     // el correu almenys té 5 caràcters
        return false;
    }

    // Comprovar que només té un '@'
    for (int i = 0; i < longitud; i++) {
        if (correu[i] == '@') {             // si el caràcter és '@', entra
            if (teArroba) {                 // si ja s'ha trobat un '@', retorna fals
                return false;

            } else {
                teArroba = true;            // Sinó, estableix teArroba com a vertader
                posArroba = i;              // i guarda la posició del '@'
            }
        }
    }

    if (!teArroba) {        // Si no s'ha trobat '@', retorna fals
        return false;
    }

    // Comprovar que només té un '.' després del '@'
    for (int i = posArroba + 1; i < longitud; i++) {
        if (correu[i] == '.') {         // si el caràcter és '.', entra
            tePunt = true;              // i estableix que té punt
            break;
        }
    }

    if (!tePunt) {          // Si no s'ha trobat '.', retorna fals
        return false;
    }

    return true;
}

bool comprovar_usuari(user_list* llista, char* nom) {
    if (llista -> head == NULL) {                   // comprovem que la llista no està buida
        return false;
    }

    User* temp = llista -> head;                    // variable temporal per recórrer la llista d'usuaris
    while (temp != NULL) {                          // mentres no estigui buida la llista, entra
        if (strcmp (temp -> nom, nom) == 0) {       // si troba l'usuari retorna vertader
            return true;
        }
        temp = temp -> next;                        // s'avança al següent usuari
    }
    return false;
}

int resp_bol() {
    char resposta[10];
    bool respostaValida = false;

    printf("\nVols modificar alguna opcio? (si/no): ");

    while (!respostaValida) {                  // bucle infinit
        scanf("%s", resposta);

        for (size_t i = 0; i < strlen(resposta); i++) {     // converteix la resposta a minúscules
            resposta[i] = tolower(resposta[i]);
        }

        if (strcmp(resposta, "si") == 0) {      // si la resposta és 'si'
            respostaValida = true;              // la resposta es vàlida
            return 1;                           // i retornem 1 (per modificar alguna opció)

        } else if (strcmp(resposta, "no") == 0) {   // si la resposta és 'no'
            respostaValida = true;                  // la resposta és vàlida
            return 0;                               // i retornem 0 (per no modificar res)

        } else {
            printf("Resposta invalida. Introdueix una resposta correcta ('si', 'no').\n");      // resposta invàlida
        }
    }
}

int checkPassword(User *usuari) {
    char input[20];
    bool correct = false;

    while (!correct) {                                                      // bucle infinit
        printf("Introdueix la contrasenya: ");
        scanf("%s", input);                                             // guarda la contrasenya introduïda per l'usuari

        if (strcmp(input, usuari -> password) == 0) {                        // comparem la contrasenya introduïda amb l'actual
            printf("Benvingut %s!,\n", usuari -> nom);
            return 1;           // entrem al perfil

        } else {
            printf("Contrasenya incorrecta. Intenta-ho de nou.\n");
            return 0;           // no entrem al perfil
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

    if (isQueueEmpty(queue)) {                              // si la cua està buida, el nou usuari és el primer i darrer de la cua
        queue -> head = usuari_nou;
        queue -> last = usuari_nou;

    } else {                                                // si no, el nou usuari és el darrer de la cua
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