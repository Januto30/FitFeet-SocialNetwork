#include "menu.h"
#include "SOCIAL.h"
#include "USUARI.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

///--------------SOLICITUDS D'AMISTAT---------------------
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

    printf("\nSol.licituds pendents:\n");
    for (int i = 0; i < receptor->num_solicituds; i++) {
        printf("%d. %s\n", i + 1, receptor->solicituds[i]->nom);
    }

    int opcion;
    while(1) {
        printf("\nNombre de solicitud que vulgui gestionar (0 per sortir): ");
        scanf("%d", &opcion);

        if (opcion == 0) {
            return 0;  // Salir sin gestionar solicitudes

        } else if (opcion >= 1 && opcion <= receptor->num_solicituds) {
            // Gestionar solicitud específica
            User *solicitant = receptor->solicituds[opcion - 1];

            int opcio2;
            printf("\n1. Aceptar solicitud\n");
            printf("2. Denegar solicitud\n");

            while(1) {
                printf("Posa el numero que vulguis accionar: ");
                scanf("%d", &opcio2);

                if (opcio2 == 1) {
                    if (receptor->num_amics < MAX_AMICS) {
                        // Afegir el amic
                        receptor->amics[receptor->num_amics] = solicitant;
                        receptor->num_amics++;
                        solicitant->num_amics++;
                        printf("\nSol.licitud aceptada. Ara ets amic de %s.\n", solicitant->nom);

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
                    printf("Opcio invalida. Torna a intentar-ho\n");
                }
            }
        } else {
            printf("Opcio invalida. Torna a intentar-ho\n");
        }
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