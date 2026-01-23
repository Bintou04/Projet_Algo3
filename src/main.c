#include <stdio.h>
#include "support.h"
#include "list.h"
#include "pile.h"
#include "file.h"

int main() {
    Element *liste = NULL;
    int choix;
    Support s;
    int idRecherche;

    do {
        printf("\n====================================== MENU ===================================================\n");
        printf("1. Ajouter un support\n");
        printf("2. Supprimer un support\n");
        printf("3. Rechercher un support\n");
        printf("4. Afficher les supports\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {

        case 1:
            printf("ID : ");
            scanf("%d", &s.id);
            printf("Titre : ");
            scanf(" %[^\n]", s.titre);
            printf("Module : ");
            scanf(" %[^\n]", s.module);

            liste = ajouterSupport(liste, s);
            printf("Support ajoute.\n");
            break;

        case 2:
            printf("ID du support a supprimer : ");
            scanf("%d", &idRecherche);
            liste = supprimerSupport(liste, idRecherche);
            break;

        case 3: {
            Element *resultat;
            printf("ID du support a rechercher : ");
            scanf("%d", &idRecherche);
            resultat = rechercherSupport(liste, idRecherche);

            if (resultat != NULL) {
                printf("Support trouve : %s - %s\n",
                       resultat->support.titre,
                       resultat->support.module);
            } else {
                printf("Support non trouve.\n");
            }
            break;
        }

        case 4:
            afficherSupports(liste);
            break;

        case 0:
            printf("Au revoir !\n");
            break;

        default:
            printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}

// executable
// gcc src/main.c src/list.c src/pile.c src/file.c -Iinclude -o test_algo
// 0