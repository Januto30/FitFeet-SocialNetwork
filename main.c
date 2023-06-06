#include  "menu.h"
#include  "USUARI.h"

#include  <stdio.h>
#include  <stdlib.h>


int main () {
    int a = 1;
    user_list Llista;                       //Inicialitzem la llista d'usuaris.
    Llista.head = NULL;                     //Inicialitzem el head de la llista com a NULL.
    Llista.num_persones = 0;                //Declarem el número d'usuaris com a 0.
    llegir_usuaris_desde_arxiu(&Llista);    //Si hi ha algun usuari ja registrat s'ingresa en la llista d'usuaris.
    st_Diccionari* Diccionari = (st_Diccionari*) malloc(sizeof(st_Diccionari)); //Inicialitzem el Diccionari que emmagatzemarà les paraules de cada publicació.
    Diccionari->num_paraules = 0;           //Declarem el número de paraules del diccionari com a 0.

    while (a != 0) {
        int option1;
        menu();
        option1 = select_option();

        if (print_option(option1, &Llista, Diccionari) ==1) {
            guardar_usuaris_en_arxiu(&Llista);  //Tots els usuaris registrats queden guardats en un FILE per tal de no perdre el seu perfil.
            break;
        }
    }
    return 0;
}