#include "menu.h"
#include "USUARI.h"

#include <stdlib.h>
#include <string.h>


///--------------FUNCIONS ELEMENTALS-------------------------
void guardar_usuaris_en_arxiu (user_list* Llista) {             //Imprimeix els perfils dels usuaris registrats en un FILE un cop finalitza el programa.
    FILE* arxiu = fopen("../PERFIL.txt", "w");    //Obre un FILE.

    if (arxiu == NULL) {                                        //Si el FILE no exsisteix, imprimeix l'error.
        printf("No s'ha pogut obrir el fitxer.\n");
        return;
    }

    User* current = Llista->head;                               //Determina com a current el head de la llista d'usuaris.
    while (current != NULL) {                                   //Imprimeix tota les dades de l'usuari en una sola línia en el FILE.
        fprintf(arxiu, "%s %s %s %s %d %s %s %s %s %s %s %s %d %d\n", current->nom, current->password, current->cognom1, current->cognom2, current->edat, current->correu, current->ubi, current->gust1, current->gust2, current->gust3, current->gust4, current->gust5, current->num_solicituds, current->num_amics);
        current = current->next;                                //Itera d'usuari fins a arribar al final de la llsita.
    }

    fclose(arxiu);                                          //Tanca l'arxiu per evitar conflictes en l'emmagatzematge de l'espai.
}
void llegir_usuaris_desde_arxiu (user_list* Llista) {           //Emmagatzema els perfils dels usuaris ja registrats un cop s'inicialitza el programa.
    FILE* arxiu = fopen("../PERFIL.txt", "r");    //Obre un FILE.

    if (arxiu == NULL) {                                        //Si el FILE no exsisteix, imprimeix l'error.
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
void emmagatzema_dades (User *usuari, user_list *Llista) {        //Crea els usuaris.

    while(1) {                                                    //Bucle infinit.
        printf("Introdueix el teu nom: \n");
        scanf("%s", usuari -> nom);

        if (comprovar_usuari(Llista, usuari -> nom)) {
            printf("L'usuari ja existeix. \n");
        } else {
            break;
        }
    }

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

    while (1) {
        if (comprovar_correu(usuari->correu) == true) {       // funció per validar que el correu està ben escrit
            printf("El correu es valid.\n\n");
            break;
        } else {
            printf("El correu es invalid. Torna a introduir el teu correu: \n");
            scanf("%s", usuari -> correu);
        }
    }

    printf("Introdueix la teva ubicacio: \n");
    scanf("%s", usuari -> ubi);

    printf("Introdueix els teus 5 gustos preferits (un per linia):\n");
    scanf("%s", usuari -> gust1);
    scanf("%s", usuari -> gust2);
    scanf("%s", usuari -> gust3);
    scanf("%s", usuari -> gust4);
    scanf("%s", usuari -> gust5);

    usuari -> num_amics = 0;
    usuari -> num_solicituds = 0;

    usuari -> next = NULL;                  // així sabem quan s'ha arribat al final de la llista en recórrer-la
}


///--------------PUBLICACIÓ---------------------------------
void fer_publicacio (User* usuari, st_Diccionari* Taula) {
    char text[MAX_CHARACTERS + 1];
    printf("Introdueix el text de la publicacio (maxim %d caracters) ", MAX_CHARACTERS);
    scanf(" %[^\n]", text);

    Publicacio* nova_publicacio = (Publicacio*) malloc(sizeof(Publicacio));
    strcpy(nova_publicacio->text, text);
    nova_publicacio->seguent = usuari->publicacio.top;
    usuari->publicacio.top = nova_publicacio;

    // Dividir el texto en palabras y actualizar la tabla hash
    char copia_text[MAX_CHARACTERS + 1];
    strcpy(copia_text, text);
    char* token = strtok(copia_text, " ");
    while (token != NULL) {
        Paraula* existent = buscar_paraula(Taula, token);
        if (existent == NULL) {
            if (Taula->num_paraules < MAX_PARAULES) {
                afegir_paraula_nova(Taula, token);
            }
        }
        token = strtok(NULL, " ");
    }
}   //Emmagatzema les publicacions de cada usuari així com cada paraula en una pila.
void Timeline (User* usuari) {
    printf("Timeline de %s:\n", usuari -> nom);

    // Comença des del primer element de la pila
    Publicacio* publicacio_actual = usuari -> publicacio.top;

    // Recorre la pila de publicacions
    while (publicacio_actual != NULL) {
        printf("- %s\n", publicacio_actual -> text);
        publicacio_actual = publicacio_actual -> seguent;
    }

    printf("Fi del Timeline.\n");
}                               //Imprimeix tot el registre de publicacions de l'usuari


///--------------DICCIONARI---------------------------------
void swap (Paraula** a, Paraula** b) {
    Paraula* x = *a;
    *a = *b;
    *b = x;
}                       //Intercanvia el primer paràmetre pel segon paràmetre.
int  particio (Paraula** a, int bot, int top) {
    int i = bot - 1;
    Paraula* pivot = a[top];

    for(int j=bot; j<top; j++){
        if (a[j]->cont>pivot->cont){
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i+1], &a[top]);
    return i+1;
}              //Intercanvia els elements de la pila de més petit a més gran.
void quicksort (Paraula** a, int bot, int top) {
    if (bot<top){
        int pivot = particio(a, bot, top);
        quicksort(a, bot, pivot-1);
        quicksort(a, pivot+1, top);
    }
}             //Funció recursiva que organitza una pila.
void trending (st_Diccionari* diccionari) {
    if (diccionari->num_paraules==0){
        printf("Encara no s'ha realitzat ninguna publicacio");
        return;
    }
    quicksort(diccionari->paraules,0,diccionari->num_paraules-1);

    printf("Top paraules:\n");
    for(int i=0; i<diccionari->num_paraules && i<10; i++){
        printf("%s, s'ha utilitzat %d\n", diccionari->paraules[i]->paraula, diccionari->paraules[i]->cont);

    }
}                  //Imprimeix les 10 paraules més usades per tots els usuaris exsistents.
Paraula* buscar_paraula (st_Diccionari* Taula, char* word) {
    for (int i = 0; i < Taula->num_paraules; i++) {
        if (strcmp(Taula->paraules[i]->paraula, word) == 0) {
            Taula->paraules[i]->cont++;
            return Taula->paraules[i];
        }
    }
    return NULL;
} //Busca si una paraula ja està emmagatzemada en la pila.
void afegir_paraula_nova (st_Diccionari* Taula, char* word) {
    Paraula* new_paraula = (Paraula*) malloc(sizeof(Paraula));
    strcpy(new_paraula->paraula, word);
    new_paraula->cont = 1;
    Taula->paraules[Taula->num_paraules] = new_paraula;
    strcpy(Taula->paraules[Taula->num_paraules]->paraula, word);
    Taula->num_paraules++;
}//Afegeix una paraula a la pila.