#ifndef   FITFEET_USUARI_H
#define   FITFEET_USUARI_H
#include  <stdio.h>
#include  <stdbool.h>

/// ---------------- FUNCIONS ELEMENTALS ----------------
void guardar_usuaris_en_arxiu(user_list* Llista);
void llegir_usuaris_desde_arxiu(user_list* Llista);
void emmagatzema_dades(User *usuari, user_list *Llista);


/// ---------------- PUBLICACIÓ ----------------
void fer_publicacio(User* usuari, st_Diccionari* Taula);
void Timeline(User* usuari);


/// ---------------- DICCIONARI ----------------
void swap(Paraula** a, Paraula** b);
int particio(Paraula** a, int bot, int top);
void quicksort(Paraula** a, int bot, int top);
void trending(st_Diccionari* diccionari);
Paraula* buscar_paraula(st_Diccionari* Taula, char* word);
void afegir_paraula_nova(st_Diccionari* Taula, char* word);


#endif //FITFEET_USUARI_H
