#ifndef   FITFEET_SOCIAL_H
#define   FITFEET_SOCIAL_H
#include  <stdio.h>
#include  <stdbool.h>


///--------------SOLICITUDS D'AMISTAT-----------------------
int  enviar_solicitud (user_list *Llista, User *usuari);
int  aceptar_denegar_solicitudes (User *receptor);
void listar_amigos_aceptados (User* usuario);


#endif //FITFEET_SOCIAL_H