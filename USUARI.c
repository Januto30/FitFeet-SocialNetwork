#include "menu.h"
#include "USUARI.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <ctype.h>


/// ---------------- FUNCIONS ELEMENTALS ----------------
void guardar_usuaris_en_arxiu(user_list* Llista) {             //Imprimeix els perfils dels usuaris registrats en un FILE un cop finalitza el programa.
    FILE* arxiu = fopen("../PERFIL.txt", "w");    //Obre un FILE.

    if (arxiu == NULL) {                                        //Si el FILE no exsisteix, imprimeix l'error.
        printf("No s'ha pogut obrir el fitxer.\n");
        return;
    }

    User* current = Llista -> head;                               //Determina com a current el head de la llista d'usuaris.
    while (current != NULL) {                                   //Imprimeix tota les dades de l'usuari en una sola línia en el FILE.
        fprintf(arxiu, "%s %s %s %s %d %s %s %s %s %s %s %s %d %d\n", current->nom, current->password, current->cognom1, current->cognom2, current->edat, current->correu, current->ubi, current->gust1, current->gust2, current->gust3, current->gust4, current->gust5, current->num_solicituds, current->num_amics);
        current = current -> next;
    }

    fclose(arxiu);                                          //Tanca l'arxiu per evitar conflictes en l'emmagatzematge de l'espai.
}

void llegir_usuaris_desde_arxiu (user_list* Llista) {           //Emmagatzema els perfils dels usuaris ja registrats un cop s'inicialitza el programa.
    FILE* arxiu = fopen("../PERFIL.txt", "r");    //Obre un FILE.

    if (arxiu == NULL) {
        printf("No s'ha pogut obrir l'arxiu.\n");
        return;
    }

    //Es crean les mateixes variables de la struct user per tal de llegirles del FILE per després emmagatzemar-ho a la llista d'usuaris.
    char nom[MAX_LENGTH], password[MAX_LENGTH], cognom1[MAX_LENGTH], cognom2[MAX_LENGTH], correu[MAX_LENGTH], ubi[MAX_LENGTH], gust1[MAX_LENGTH], gust2[MAX_LENGTH], gust3[MAX_LENGTH], gust4[MAX_LENGTH], gust5[MAX_LENGTH];
    int edat, num_solicituds, num_amics;

    while (fscanf(arxiu, "%s %s %s %s %d %s %s %s %s %s %s %s %d %d", nom, password, cognom1, cognom2, &edat, correu, ubi, gust1, gust2, gust3, gust4, gust5, &num_solicituds, &num_amics) == 14) {
        User* user = (User*)malloc(sizeof(User));
        strcpy(user -> nom, nom);
        strcpy(user -> password, password);
        strcpy(user -> cognom1, cognom1);
        strcpy(user -> cognom2, cognom2);
        user -> edat = edat;
        strcpy(user -> correu, correu);
        strcpy(user -> ubi, ubi);
        strcpy(user -> gust1, gust1);
        strcpy(user -> gust2, gust2);
        strcpy(user -> gust3, gust3);
        strcpy(user -> gust4, gust4);
        strcpy(user -> gust5, gust5);
        user -> next = NULL;
        Llista -> num_persones++;
        user -> num_solicituds = num_solicituds;
        user -> num_amics = num_amics;

        //Aquest fragment s'encarrega d'anar buscant a quina casella de la llista d'usuaris
        //es pot introduir el nou usuari llegit del FILE.
        if (Llista -> head == NULL) {
            Llista -> head = user;

        } else {
            User* current = Llista -> head;

            while (current -> next != NULL) {
                current = current -> next;
            }
            current -> next = user;
        }
    }

    fclose(arxiu);
}

void emmagatzema_dades(User *usuari, user_list *Llista) {         //L'suari insertarà totes les dades necessaries per crear el seu usuari
/// canviar ordre de preguntes?

    while(1) {                                                    //Bucle infinit.
        printf("Introdueix el teu nom: \n");
        scanf("%s", usuari -> nom);

        if (comprovar_usuari(Llista, usuari -> nom)) {      //Si el nom de l'usuari ja exsisteix s'imprimeix l'alerta i es demana que torni a introduir un nou nom.
            printf("L'usuari ja existeix. \n");
        } else {
            break;
        }
    }

    printf("Introdueix la contrasenya: \n");                //Es demana la contrasenya del perfil.
    scanf("%s", usuari -> password);

    printf("Introdueix el teu primer cognom: \n");          //Es demana el primer cognom.
    scanf("%s", usuari -> cognom1);

    printf("Introdueix el teu segon cognom: \n");           //Es demana el segon cognom.
    scanf("%s", usuari -> cognom2);

    printf("Introdueix la teva edat: \n");                  //Es demana l'edat de l'usuari.
    scanf("%d", &usuari -> edat);

    printf("Introdueix el teu correu electronic: \n");      //Es demana el correu electrònic de l'usuari el qual es validarà a continuació.
    scanf("%s", usuari -> correu);

    while (1) {
        if (comprovar_correu(usuari -> correu) == true) {          //funció per validar que el correu està ben escrit
            printf("El correu es valid.\n\n");
            break;
        } else {
            printf("El correu es invalid. Torna a introduir el teu correu: \n");
            scanf("%s", usuari -> correu);
        }
    }

    printf("Introdueix la teva ubicacio: \n");
    scanf("%s", usuari -> ubi);

    printf("Introdueix els teus 5 esports preferits (un per linia):\n");
    scanf("%s", usuari -> gust1);
    scanf("%s", usuari -> gust2);
    scanf("%s", usuari -> gust3);
    scanf("%s", usuari -> gust4);
    scanf("%s", usuari -> gust5);

    usuari -> num_amics = 0;
    usuari -> num_solicituds = 0;
    usuari -> quilometres = 0;

    usuari -> next = NULL;                                          //Així sabem quan s'ha arribat al final de la llista en recórrer-la
}


/// ---------------- FUNCIONS ELEMENTALS ----------------
void print_user_info(User *current) {
    printf("\n");
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
}

void canvi_de_dades(char* option_3_1, User *current){
    while (1) {
        scanf("%s", option_3_1);

        // Convertim l'opció introduïda a minúscula
        for (int i = 0; option_3_1[i]; i++) {
            option_3_1[i] = tolower(option_3_1[i]);
        }

        if (strcmp(option_3_1, "nom") == 0) {
            printf("Ja pots introduir el canvi: ");
            scanf("%s", current -> nom);
            break;

        } else if (strcmp(option_3_1, "cognom") == 0) {
            printf("Ja pots introduir el canvi: ");
            scanf("%s", current -> cognom1);
            break;

        } else if (strcmp(option_3_1, "2ncognom") == 0 || strcmp(option_3_1, "2cognom") == 0) {
            printf("Ja pots introduir el canvi: ");
            scanf("%s", current -> cognom2);
            break;

        } else if (strcmp(option_3_1, "edat") == 0) {
            printf("Ja pots introduir el canvi: ");
            scanf("%d", &current -> edat);
            break;

        } else if (strcmp(option_3_1, "correu") == 0) {
            printf("Ja pots introduir el canvi: ");
            scanf("%s", current -> correu);
            break;

        } else if (strcmp(option_3_1, "ubicacio") == 0) {
            printf("Ja pots introduir el canvi: ");
            scanf("%s", current -> ubi);
            break;

        } else if (strcmp(option_3_1, "gust1") == 0) {
            printf("Ja pots introduir el canvi: ");
            scanf("%s", current -> gust1);
            break;

        } else if (strcmp(option_3_1, "gust2") == 0) {
            printf("Ja pots introduir el canvi: ");
            scanf("%s", current -> gust2);
            break;

        } else if (strcmp(option_3_1, "gust3") == 0) {
            printf("Ja pots introduir el canvi: ");
            scanf("%s", current -> gust3);
            break;

        } else if (strcmp(option_3_1, "gust4") == 0) {
            printf("Ja pots introduir el canvi: ");
            scanf("%s", current -> gust4);
            break;

        } else if (strcmp(option_3_1, "gust5") == 0) {
            printf("Ja pots introduir el canvi: ");
            scanf("%s", current -> gust5);
            break;

        } else {
            printf("Opcio incorrecta, introdueix una valida: ");
        }
    }
}


/// ---------------- PUBLICACIÓ ----------------
void fer_publicacio(User* usuari, st_Diccionari* Taula) {                           //Emmagatzema les publicacions de cada usuari així com cada paraula en una pila.
    char text[MAX_CHARACTERS + 1];
    printf("Introdueix el text de la publicacio (maxim %d caracters) ", MAX_CHARACTERS);
    scanf(" %[^\n]", text);
    quilometres(usuari);

    Publicacio* nova_publicacio = (Publicacio*) malloc(sizeof(Publicacio));     //Creem una estructura ""Publicacio"" de memòria dinàmica.
    strcpy(nova_publicacio -> text, text);                               //Insertem el text dona per l'usuari en la variable text de la publicacio que acabem de crear.
    nova_publicacio -> seguent = usuari -> publicacio.top;
    usuari -> publicacio.top = nova_publicacio;

    //Dividim la publicació en paraules i inserim cada una d'elles en el diccionari.
    char copia_text[MAX_CHARACTERS + 1];
    strcpy(copia_text, text);
    char* token = strtok(copia_text, " ");
    while (token != NULL) {
        Paraula* existent = buscar_paraula(Taula, token);                       //Es busca si la paraula exsistia ja en el diccionari.
        if (existent == NULL) {                                                      //En cas de que la paraula nova no estigui ja en el diccionari s'afegirà, en cas contrari es sumarà el contador d'aquella paraula repetida.
            if (Taula -> num_paraules < MAX_PARAULES) {
                afegir_paraula_nova(Taula, token);                              //Afegim la paraula en qüestió en la seva posició corresponent en la pila.
            }
        }
        token = strtok(NULL, " ");
    }
}

void Timeline (User* usuari) {                                  //Imprimeix tot el registre de publicacions de l'usuari
    printf("Timeline de %s:\n", usuari -> nom);

    Publicacio* publicacio_actual = usuari -> publicacio.top;   // Comença des del primer element de la pila

                                                                // Recorre la pila de publicacions
    while (publicacio_actual != NULL) {
        printf("- %s\n", publicacio_actual -> text);
        publicacio_actual = publicacio_actual -> seguent;
    }

    printf("Fi del Timeline.\n");
}

void quilometres(User* usuari){
    int quilometres;
    printf("Quants quilometres has recorregut avui? ");
    scanf("%d", &quilometres);
    usuari->quilometres += quilometres;
}

void print_quilometres(User* usuari){
    printf("En total has recorreut %d quilometres.\n", usuari->quilometres);
}


/// ---------------- DICCIONARI ----------------
void swap(Paraula** a, Paraula** b) {           //Intercanvia el primer paràmetre pel segon paràmetre.
    Paraula* x = *a;
    *a = *b;
    *b = x;
}

int  particio (Paraula** a, int bot, int top) {         //Intercanvia els elements de la pila de més petit a més gran de manera recursiva.
    int i = bot - 1;
    Paraula* pivot = a[top];

    for(int j=bot; j<top; j++) {
        if (a[j] -> cont > pivot -> cont) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i+1], &a[top]);
    return i+1;
}

void quicksort (Paraula** a, int bot, int top) {        //Funció recursiva que organitza una pila recursivament
    if (bot < top){
        int pivot = particio(a, bot, top);
        quicksort(a, bot, pivot - 1);
        quicksort(a, pivot + 1, top);
    }
}

void trending (st_Diccionari* diccionari) {                                 //Imprimeix les 10 paraules més usades per tots els usuaris exsistents.
    if (diccionari -> num_paraules == 0){                                   //En cas que la pila no contingui paraules s'imprimirà l'error.
        printf("Encara no s'ha realitzat ninguna publicacio");
        return;
    }
    quicksort(diccionari -> paraules,0,diccionari -> num_paraules - 1); //Ordenem la pila de les paraules més freqüents a les menys.

    printf("\nTop paraules:\n");
    for(int i = 0; i < diccionari -> num_paraules && i < 10; i++) {
        printf("La paraula '%s', s'ha utilitzat %d.\n", diccionari -> paraules[i] -> paraula, diccionari -> paraules[i] -> cont);
    }
}

Paraula* buscar_paraula (st_Diccionari* Taula, char* word) {            //Busca si una paraula ja està emmagatzemada en la pila.
    for (int i = 0; i < Taula -> num_paraules; i++) {                   //Es reocrrerà tot el Diccionari.
        if (strcmp(Taula -> paraules[i] -> paraula, word) == 0) {       //Es compara la variable word amb cada element del Diccionari.
            Taula -> paraules[i] -> cont++;                             //Es suma el contador de paraules exsistents en el diccionari.
            return Taula -> paraules[i];                                //Retorna la direcció de memòria a la casella la qual conté la paraula que coincideix amb el char "word".
        }
    }
    return NULL;                                                        //Retorna NULL en cas que la paraula no es trobi..
}

void afegir_paraula_nova (st_Diccionari* Taula, char* word) {           //Afegeix una paraula a la pila.
    Paraula* new_paraula = (Paraula*) malloc(sizeof(Paraula));     //Declarem una direcció de memòria a una struct Paraula.
    strcpy(new_paraula -> paraula, word);                   //Copiem la variable "word" a la variable "paraula" de la struct acabada de declarar.
    new_paraula -> cont = 1;                                            //Declarem el recompte d'aquella paraula en 1.
    Taula -> paraules[Taula -> num_paraules] = new_paraula;             //Copiem en una casella del Diccionari la variable "new_paraula".
    strcpy(Taula -> paraules[Taula -> num_paraules] -> paraula, word);
    Taula -> num_paraules++;                                            //Sumem el contador de paraules del Diccionari.
}