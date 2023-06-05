#ifndef   FITFEET_SOCIAL_H
#define   FITFEET_SOCIAL_H
#include  <stdio.h>
#include  <stdbool.h>


/// ---------------- SOL·LICITUDS D'AMISTAT ----------------
int enviar_solicitud(user_list *Llista, User *usuari);
int acceptar_denegar_solicituds(User *receptor);
void llistar_amics_acceptats(User* usuario);


#endif //FITFEET_SOCIAL_H