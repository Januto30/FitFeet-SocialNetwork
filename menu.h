#ifndef FITFEET_MENU_H
#define FITFEET_MENU_H
#include <stdio.h>
#define MAX_LENGTH 200
#define MAX_AMICS 500
#define MAX_SOLICITUDS 500

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

    int num_amics;                  //Així cada usuari té una pròpia llista d'amics i una llista de solicituds
    struct User* amics[MAX_AMICS];
    struct User* num_solicituds;
    char* solicituds[MAX_SOLICITUDS];
}User;


typedef struct user_list {          // Linked list
    User* head;                     // apunta al primer element de la llista
    int num_persones;               // nombre de persones a la llista
} user_list;

void menu();

int select_option();

int print_option(int option, user_list *Llista);

void emmagatzema_dades(User *usuari);

void comprovar_correu(User *usuari, char *correu);

void print_users(user_list *llista_usuaris);

void afegir_usuari(user_list* llista, User* usuari);

int checkPassword(User *usuari);

//void enviar_solicitud(User *emisor, User *receptor);


void llegir_usuaris_desde_arxiu(user_list* Llista);

void guardar_usuaris_en_arxiu(user_list* Llista);

void opcio3(user_list *Llista);

void printf_menu();
#endif //FITFEET_MENU_H
