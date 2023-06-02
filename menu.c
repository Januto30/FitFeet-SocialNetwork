#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
//Asd
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

int print_option(int option, user_list *Llista, TaulaHash* TaulaHash) {
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
        opcio3(Llista, TaulaHash);
        return 0;

    } else if (option == 4) {
        return 1;
    }
}

void emmagatzema_dades(User *usuari, user_list *Llista) {         // canviar ordre de preguntes

    while(1) {
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
        if (comprovar_correu(usuari, usuari -> correu) == true) {       // funció per validar que el correu està ben escrit
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

bool comprovar_correu(User *usuari, char *correu) {
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

int enviar_solicitud(user_list* Llista, User *usuari) {
    User* current = usuari;
    User* iterar_llista = Llista -> head;
    char receptor[MAX_LENGTH];
    printf("A qui vols enviar una sol.licitud?");
    scanf("%s", receptor);

    // Cerquem al receptor en la llista
    int index = -1;
    for (int i = 0; i < Llista -> num_persones; i++) {
        if (strcmp(iterar_llista -> nom, receptor) == 0) {
            index = i;
            break;
        }
        iterar_llista = iterar_llista -> next;
    }
    User* receptor_user = iterar_llista;

    // Mirem que els paràmetres no estiguin buits
    if (current == NULL || receptor_user == NULL) {
        return -1;
    }

    // Comprovam que l'emissor i el receptor no siguin els mateixos
    if (current == receptor_user) {
        printf("No et pots enviar una sol.licitud a tu mateix\n");
        return -1;
    }

    // Mirem si l'emissor ja té al receptor com amic
    for (int i = 0; i < current -> num_amics; i++) {
        if (current -> amics[i] == receptor_user) {
            printf("Ja sou amics\n");
            return -1;
        }
    }

    // Mirem si el receptor ja té a l'emissor com amic
    for (int i = 0; i < receptor_user -> num_amics; i++) {
        if (receptor_user -> amics[i] == current) {
            printf("Ja sou amics\n");
            return -1;
        }
    }

    // Comprovam que l'emissor no hagi enviat ja una sol.licitud d'amistat al receptor
    for (int i = 0; i < current -> num_solicituds; i++) {
        if (current -> solicituds[i] == receptor_user) {
            printf("Ja has enviat una sol.licitud a aquest usuari\n");
            return -1;
        }
    }

    // Mirem que el receptor no hagi rebut ja una sol.licitud de l'emissor
    for (int i = 0; i < receptor_user -> num_solicituds; i++) {
        if (receptor_user -> solicituds[i] == current) {
            printf("Ja has enviat una sol.licitud a aquest usuari\n");
            return -1;
        }
    }

    if (index == -1) {
        printf("El receptor no existeix a la llista.\n");
        return -1;
    }

    // Si no hi ha errors, afegim la sol.licitud a la llista del receptor
    receptor_user -> solicituds[receptor_user -> num_solicituds] = current;
    receptor_user -> num_solicituds++;
    printf("Sol.licitud enviada amb exit.\n");

    return 0;
}

int aceptar_denegar_solicitudes(user_list *Llista, User *receptor) {
    if (receptor->num_solicituds == 0) {
        printf("No tens sol.icituds pendents.\n");
        return -1;
    }

    printf("Sol.licituds pendents:\n");
    for (int i = 0; i < receptor->num_solicituds; i++) {
        printf("%d. %s\n", i + 1, receptor->solicituds[i]->nom);
    }

    int opcion;
    printf("Nombre de solicitud que vulgui gestionar (0 per sortir): ");
    scanf("%d", &opcion);

    if (opcion == 0) {
        return 0;  // Salir sin gestionar solicitudes
    } else if (opcion >= 1 && opcion <= receptor->num_solicituds) {
        // Gestionar solicitud específica
        User *solicitant = receptor->solicituds[opcion - 1];

        printf("1. Aceptar solicitud\n");
        printf("2. Denegar solicitud\n");
        int opcio2;
        printf("Posa el numero que vulguis accionar: ");
        scanf("%d", &opcio2);

        if (opcio2 == 1) {
            if (receptor->num_amics < MAX_AMICS) {
                // Afegir el amic
                receptor->amics[receptor->num_amics] = solicitant;
                receptor->num_amics++;
                solicitant->num_amics++;
                printf("Sol.licitud aceptada. Ara ets amic de %s.\n", solicitant->nom);

                // Eliminar solicitud aceptada de la lista de solicitudes
                for (int i = opcion - 1; i < receptor->num_solicituds - 1; i++) {
                    receptor->solicituds[i] = receptor->solicituds[i + 1];
                }
                receptor->num_solicituds--;

                return 0;
            } else {
                printf("No s'ha pogut acceptar la sol.licitud. La llista d'amics esta plena.\n");
                return -1;  // Error: Lista de amigos llena
            }
        } else if (opcio2 == 2) {
            printf("Sol.licitud denegada. No ets amic de %s.\n", solicitant->nom);

            // Eliminar solicitud denegada de la lista de solicitudes
            for (int i = opcion - 1; i < receptor->num_solicituds - 1; i++) {
                receptor->solicituds[i] = receptor->solicituds[i + 1];
            }
            receptor->num_solicituds--;

            return 0;
        } else {
            printf("Opcio invalida.\n");
            return -1;
        }
    } else {
        printf("Opcio invalida.\n");
        return -1;
    }
}

void listar_amigos_aceptados(User* usuario) {
    printf("Amigos aceptados de %s:\n", usuario->nom);

    if (usuario->num_amics == 0) {
        printf("No tienes amigos aceptados.\n");
        return;
    }

    for (int i = 0; i < usuario->num_amics; i++) {
        printf("%d. %s\n", i + 1, usuario->amics[i]->nom);
    }
    sleep(1.5);
}




void opcio3(user_list *Llista, TaulaHash* TaulaHash) {
    char usuari[MAX_LENGTH];                        // guarda el nom del usuari
    int opcio3, permis;

    printf("\n---Quin usuari ets?---\n");
    print_users(Llista);

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
    while (current != NULL) {                       // mentres no s'hagi arribat al final de la llista...
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
            printf_menu();
            printf("Tria l'opcio desitjada: ");
            scanf("%d", &opcio3);
            if (opcio3 == 1) {
                while (opcio3 == 1){
                    char option_3[10];
                    printf("\n");
                    printf("==========================\n");
                    printf("|     Dades personals    |\n");
                    printf("|========================|\n");
                    printf("| Nom:      %s\n", current -> nom);
                    printf("| Cognom:   %s\n", current -> cognom1);
                    printf("| 2n Cognom: %s\n", current -> cognom2);
                    printf("| Edat:     %d\n", current -> edat);
                    printf("| Correu:   %s\n", current -> correu);
                    printf("| Ubicacio: %s\n", current -> ubi);
                    printf("|========================|\n");
                    printf("|         Gustos         |\n");
                    printf("|========================|\n");
                    printf("| Gust 1:   %s\n", current -> gust1);
                    printf("| Gust 2:   %s\n", current -> gust2);
                    printf("| Gust 3:   %s\n", current -> gust3);
                    printf("| Gust 4:   %s\n", current -> gust4);
                    printf("| Gust 5:   %s\n", current -> gust5);
                    printf("==========================\n");

                    if (resp_bol() == 1) {
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
                    } else {
                        break;
                    }
                }

            } else if (opcio3 == 2) {
                enviar_solicitud(Llista, current);
                current = Llista -> head;

            } else if (opcio3 == 3) {
                if (current -> num_solicituds == 0){
                    printf("No tens sol.licituds d'amistat pendents.\n");
                }
                else{
                    aceptar_denegar_solicitudes(Llista, current);
                }

            } else if (opcio3 == 4) {
                //Aqui hem de llistar els nostres amics
                listar_amigos_aceptados(current);
                sleep(1.5);
            } else if (opcio3 == 5) {
                fer_publicacio(current, TaulaHash);
            } else if (opcio3 == 6){
                Timeline(current);
            } else if (opcio3 == 7){
                trending(TaulaHash);
            }else if(opcio3 == 8){
                break;
            }
        }
    }
}

void guardar_usuaris_en_arxiu(user_list* Llista) {
    FILE* arxiu = fopen("../PERFIL.txt", "w");

    if (arxiu == NULL) {
        printf("No s'ha pogut obrir el fitxer.\n");
        return;
    }

    User* current = Llista->head;
    while (current != NULL) {
        fprintf(arxiu, "%s %s %s %s %d %s %s %s %s %s %s %s %d %d\n", current->nom, current->password, current->cognom1, current->cognom2, current->edat, current->correu, current->ubi, current->gust1, current->gust2, current->gust3, current->gust4, current->gust5, current->num_solicituds, current->num_amics);
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

void printf_menu(){
    printf("\n");
    printf("---| 1. Perfil                          |---\n");
    printf("---| 2. Enviar sol.licituds d'amistat   |---\n");
    printf("---| 3. Acceptar/denegar sol.licituds   |---\n");
    printf("---| 4. Llista d'amics                    |---\n");
    printf("---| 5. Realitzar una publicacio        |---\n");
    printf("---| 6. Llistar les publicacions        |---\n");
    printf("---| 7. Llistar paraules TOP            |---\n");
    printf("---| 8. Sortir                          |---\n");
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
    return 0;
}

void fer_publicacio(User* usuari, TaulaHash* Taula) {
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
        } if (existent != NULL){
            if (Taula->num_paraules < MAX_PARAULES) {
                existent->cont++;
                Taula->num_paraules++;
            }
        }
        token = strtok(NULL, " ");
    }
}

void Timeline(User* usuari) {
    printf("Timeline de %s:\n", usuari -> nom);

    // Comença des del primer element de la pila
    Publicacio* publicacio_actual = usuari -> publicacio.top;

    // Recorre la pila de publicacions
    while (publicacio_actual != NULL) {
        printf("- %s\n", publicacio_actual -> text);
        publicacio_actual = publicacio_actual -> seguent;
    }

    printf("Fi del Timeline.\n");
}

void swap(Paraula** a, Paraula** b){
    Paraula* x = *a;
    *a = *b;
    *b = x;
}

int particio (Paraula** a, int bot, int top){
    int i = bot - 1;
    int pivot = a[top]->cont;

    for(int j=bot; j<top; j++){
        if (a[j]->cont>pivot){
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i+1], &a[top]);
    return i+1;
}

void quicksort (Paraula** a, int bot, int top){
    if (bot<top){
        int pivot = particio(a, bot, top);
        quicksort(a, bot, pivot-1);
        quicksort(a, pivot+1, top);
    }
}

void trending (TaulaHash* diccionari){
    if (diccionari->num_paraules==0){
        printf("Encara no s'ha realitzat ninguna publicacio");
        return;
    }

    printf("Top paraules:\n");
    for(int i=0; i<diccionari->num_paraules && i<10; i++){
        printf("%s, s'ha utilitzat %d\n", diccionari->paraules[i]->paraula, diccionari->paraules[i]->cont);

    }
}

Paraula* buscar_paraula(TaulaHash* Taula, char* word) {
    for (int i = 0; i < Taula->num_paraules; i++) {
        if (strcmp(Taula->paraules[i]->paraula, word) == 0) {
            return Taula->paraules[i];
        }
    }
    return NULL;
}

void afegir_paraula_nova(TaulaHash* Taula, char* word) {
    Paraula* new_paraula = (Paraula*) malloc(sizeof(Paraula));
    strcpy(new_paraula->paraula, word);
    new_paraula->cont = 1;
    Taula->paraules[Taula->num_paraules] = new_paraula;
    strcpy(Taula->paraules[Taula->num_paraules]->paraula, word);
    Taula->num_paraules++;

}

