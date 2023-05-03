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
    struct User* next;
}User;

typedef struct user_list {
    User* head;
    int num_persones;
} user_list;

void menu();

int select_option();

int print_option(int option, user_list *Llista);

void emmagatzema_dades(User *usuari);

void afegir_usuari(user_list* llista, User* usuari);



#endif //FITFEET_MENU_H
