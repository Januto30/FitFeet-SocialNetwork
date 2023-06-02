#ifndef FITFEET_MENU_H
#define FITFEET_MENU_H
#include <stdio.h>
#include <stdbool.h>
#define MAX_LENGTH 50
#define MAX_AMICS 100
#define MAX_SOLICITUDS 100
#define MAX_PARAULES 1000
#define MAX_CHARACTERS 100

///--------------STRUCT---------------------
typedef struct{
    char paraula[MAX_CHARACTERS];
    int cont;
}Paraula;
typedef struct{
    Paraula* paraules[MAX_PARAULES];
    int num_paraules;
}st_Diccionari;
typedef struct Publicacio {
    char text[MAX_CHARACTERS + 1];
    struct Publicacio* seguent;
} Publicacio;
typedef struct {
    Publicacio* top;  // Apunta a l'element superior de la pila
} PilaPublicacions;
typedef struct User{
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
    //ASDADS

    int num_amics;                  //Així cada usuari té una pròpia llista d'amics i una llista de solicituds
    struct User* amics[MAX_AMICS];
    int num_solicituds;
    struct User* solicituds[MAX_SOLICITUDS];
    struct Publicacio* publicacions;
    PilaPublicacions publicacio;  // Pila de publicacions de l'usuari
} User;
typedef struct {                    // Linked list
    User* head;                     // apunta al primer element de la llista
    int num_persones;               // nombre de persones a la llista
} user_list;


///--------------MENU---------------------
void menu();
int select_option();
int print_option(int option, user_list *Llista, st_Diccionari* TaulaHash);


///--------------OPCIONS DE MENÚ---------------------
void afegir_usuari(user_list* llista, User* usuari);
void print_users(user_list *Llista);
void opcio3(user_list *Llista, st_Diccionari* TaulaHash);
void printf_menu();


///--------------AUXILIARS---------------------
bool comprovar_correu(User *usuari, char *correu);
bool comprovar_usuari(user_list* llista, char* nom);
int resp_bol();
int checkPassword(User *usuari);
int resp_bol();


#endif //FITFEET_MENU_H