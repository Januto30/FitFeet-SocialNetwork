#ifndef FITFEET_SOCIAL_H
#define FITFEET_SOCIAL_H
#include <stdio.h>
#include <stdbool.h>

#define MAX_LENGTH 50
#define MAX_AMICS 100
#define MAX_SOLICITUDS 100
#define MAX_PARAULES 1000
#define MAX_CHARACTERS 100


///--------------SOLICITUDS D'AMISTAT---------------------
int enviar_solicitud(user_list *Llista, User *usuari);
int aceptar_denegar_solicitudes(user_list *Llista, User *receptor);
void listar_amigos_aceptados(User* usuario);


#endif //FITFEET_SOCIAL_H
