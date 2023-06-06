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
        fprintf(arxiu, "%s %s %s %s %d %s %s %s %s %s %s %s %d %d %d\n", current->nom, current->password, current->cognom1, current->cognom2, current->edat, current->correu, current->ubi, current->gust1, current->gust2, current->gust3, current->gust4, current->gust5, current->num_solicituds, current->num_amics, current -> quilometres);
        current = current -> next;
    }

    fclose(arxiu);                                          //Tanca l'arxiu per evitar conflictes en l'emmagatzematge de l'espai.




    FILE* arxiu_solicituds = fopen("../SOLICITUDS_AMICS.txt","w");    //Mateix codi per afegir el nom dels usuaris que s'afageixen en el mateix ordre al fitxer de solicituds.

        current = Llista->head;

        const char* solicituds;
        for (int i = 0; i < current->num_solicituds; i++) {
            strcat(current->solicituds[i]->nom, solicituds);
        }

        while (current != NULL) {
            fprintf(arxiu_solicituds, "%s ", current->nom);
            for (int i = 0; i < current->num_solicituds; i++) {
                fprintf(arxiu_solicituds, "%s ", current->solicituds[i]->nom);
            }
            fprintf(arxiu_solicituds, "\n");
            current = current->next;
        }
        fclose(arxiu_solicituds);




    FILE* arxiu_amics = fopen("../AMICS.txt","w");    //Mateix codi per afegir el nom dels usuaris que s'afageixen en el mateix ordre al fitxers d'amics.

    current = Llista->head;

    const char* amics;
    for (int i = 0; i < current->num_amics; i++) {
        strcat(current->amics[i]->nom, amics);
    }

    while (current != NULL) {
        fprintf(arxiu_amics, "%s ", current->nom);
        for (int i = 0; i < current->num_amics; i++) {
            fprintf(arxiu_amics, "%s ", current->amics[i]->nom);
        }
        fprintf(arxiu_amics, "\n");
        current = current->next;
    }
    fclose(arxiu_amics);
}

void llegir_usuaris_desde_arxiu (user_list* Llista) {           //Emmagatzema els perfils dels usuaris ja registrats un cop s'inicialitza el programa.
    FILE* arxiu = fopen("../PERFIL.txt", "r");    //Obre un FILE.
    FILE* arxiu_solicituds = fopen("../SOLICITUDS_AMICS.txt", "r");
    FILE* arxiu_amics = fopen("../AMICS.txt", "r");

    if (arxiu == NULL || arxiu_amics == NULL || arxiu_solicituds == NULL) {
        printf("No s'ha pogut obrir l'arxiu.\n");
        return;
    }

    //Es crean les mateixes variables de la struct user per tal de llegirles del FILE per després emmagatzemar-ho a la llista d'usuaris.
    char nom[MAX_LENGTH], password[MAX_LENGTH], cognom1[MAX_LENGTH], cognom2[MAX_LENGTH], correu[MAX_LENGTH], ubi[MAX_LENGTH], gust1[MAX_LENGTH], gust2[MAX_LENGTH], gust3[MAX_LENGTH], gust4[MAX_LENGTH], gust5[MAX_LENGTH];
    int edat, num_solicituds, num_amics, quilometres;

    while (fscanf(arxiu, "%s %s %s %s %d %s %s %s %s %s %s %s %d %d %d", nom, password, cognom1, cognom2, &edat, correu, ubi, gust1, gust2, gust3, gust4, gust5, &num_solicituds, &num_amics, &quilometres) == 15) {
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
        user -> quilometres = quilometres;

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

    User *user = Llista->head;
    User* iterar_llista = Llista->head;
    for(int p = 0; p < Llista->num_persones; p++) {

        // Llegir el fitxer SOLICITUDS_AMICS.txt per línies
        char linia_solicituds[500];
        if (fgets(linia_solicituds, sizeof(linia_solicituds), arxiu_solicituds) != NULL) {
            linia_solicituds[strcspn(linia_solicituds, "\n")] = '\0';

            // Hem de dividir les línies de l'arxiu en tokens, 1 token per a cada nom (el primer no es té en compte perquè és el nom de l'usuari)
            char *tokens_solicituds[MAX_SOLICITUDS];
            int contadorTokensSolicituds = 0;

            char *token_solicituds = strtok(linia_solicituds, " ");
            while (token_solicituds != NULL && contadorTokensSolicituds < MAX_SOLICITUDS) {
                tokens_solicituds[contadorTokensSolicituds] = token_solicituds;
                contadorTokensSolicituds++;
                token_solicituds = strtok(NULL, " ");
            }

            // Es guarden els valors dels tokens a user->solicituds
            int c = 0;
            for(int i = 1; i < contadorTokensSolicituds; i++){
                iterar_llista = Llista->head;
                 for(int j = 0; j < Llista->num_persones; j++) {
                     if (strcmp(iterar_llista->nom, tokens_solicituds[i]) == 0) {
                         user->solicituds[c] = iterar_llista;
                         c++;
                     }
                     iterar_llista = iterar_llista->next;
                 }
            }
        }
        user = user->next;
        iterar_llista = Llista->head;
    }




    user = Llista->head;
    iterar_llista = Llista->head;
    for(int p = 0; p < Llista->num_persones; p++) {

        // Llegir el fitxer AMICS.txt per línies
        char linia_amics[500];
        if (fgets(linia_amics, sizeof(linia_amics), arxiu_amics) != NULL) {
            linia_amics[strcspn(linia_amics, "\n")] = '\0';

            // Dividir les línies del fitxer AMICS.txt en tokens (usant la funció strtok i usant " " com a separador, d'aquesta forma cada nom es converteix en un token)
            char *tokens_amics[MAX_AMICS];
            int contadorTokensAmics = 0;

            char *token_amics = strtok(linia_amics, " ");
            while (token_amics != NULL && contadorTokensAmics < MAX_SOLICITUDS) {
                tokens_amics[contadorTokensAmics] = token_amics;
                contadorTokensAmics++;
                token_amics = strtok(NULL, " ");
            }

            // Guardar els tokens a user->amics
            int c = 0;
            for(int i = 1; i < contadorTokensAmics; i++){
                iterar_llista = Llista->head;
                for(int j = 0; j < Llista->num_persones; j++) {
                    if (strcmp(iterar_llista->nom, tokens_amics[i]) == 0) {
                        user->amics[c] = iterar_llista;

                        c++;
                    }
                    iterar_llista = iterar_llista->next;
                }
            }
        }
        user = user->next;
        iterar_llista = Llista->head;
    }


    fclose(arxiu);
    fclose(arxiu_solicituds);
    fclose(arxiu_amics);
}

void emmagatzema_dades(User *usuari, user_list *Llista) {         //L'usuari insertarà totes les dades necessaries per crear el seu usuari

    printf("------INSERTAR NOU USUARI------\n");

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
    printf("|========================|\n");
    printf("|       Kilometres       |\n");
    printf("|========================|\n");
    printf("| Km totals: %d\n", current->quilometres);
    printf("==========================\n");
}

void canvi_de_dades(User *current){
    char option_3_1[MAX_LENGTH];
    printf("Quina? ");
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

void print_rankingKM(user_list* Llista , User* usuari) {
    User* usuaris[MAX_USERS];
    int numUsuaris = 0;

    User* current = Llista -> head;
    while (current != NULL && numUsuaris < MAX_USERS) {
        usuaris[numUsuaris] = current;
        current = current -> next;
        numUsuaris++;
    }

    for (int i = 0; i < numUsuaris - 1; i++) {
        for (int j = 0; j < numUsuaris - i - 1; j++) {
            if (usuaris[j] -> quilometres < usuaris[j + 1] -> quilometres) {
                User* temp = usuaris[j];
                usuaris[j] = usuaris[j + 1];
                usuaris[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < numUsuaris; i++){
        printf("%d. %s amb %d kilometres\n", i + 1, usuaris[i] -> nom, usuaris[i] -> quilometres);
    }
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