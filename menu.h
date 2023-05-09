#ifndef FITFEET_MENU_H
#define FITFEET_MENU_H
#include <stdio.h>
#define MAX_LENGTH 200

typedef struct {
    char nom[MAX_LENGTH];
    char password[MAX_LENGTH];
    char cognom1[MAX_LENGTH];
    char cognom2[MAX_LENGTH];
    int edat;
    char correu[MAX_LENGTH];
    char ubi[MAX_LENGTH];
    char gust1[MAX_LENGTH];
    char gust2[MAX_LENGTH];
    char gust3[MAX_LENGTH];
    char gust4[MAX_LENGTH];
    char gust5[MAX_LENGTH];
    struct User* next;              // Com que volem que la llista tingui més d'un usuari, connectem els nodes entre ells
}User;

typedef struct user_list {          // Linked list
    User* head;                     // apunta al primer element de la llista
    int num_persones;               // nombre de persones a la llista
} user_list;

void menu();

int select_option();

int print_option(int option, user_list *Llista);

void emmagatzema_dades(User *usuari);

void print_users(user_list *llista_usuaris);

void afegir_usuari(user_list* llista, User* usuari);

int checkPassword(User *usuari);

void guardar_usuaris_en_arxiu(user_list* lista_usuarios);

void llegir_usuaris_desde_arxiu(user_list* Llista);
#endif //FITFEET_MENU_H
