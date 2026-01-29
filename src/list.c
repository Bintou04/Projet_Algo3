#include <stdio.h>
#include <stdlib.h>
#include "list.h"
Element *tete = NULL;

Element* ajouterSupport(Element *tete, Support s) {
    Element *nouveau = malloc(sizeof(Element));
    nouveau->support = s;
    nouveau->suivant = tete;
    return nouveau;
}

Element* supprimerSupport(Element *tete, int id) {
    Element *courant = tete;
    Element *precedent = NULL;

    while (courant != NULL) {
        if (courant->support.id == id) {
            if (precedent == NULL)
                tete = courant->suivant;
            else
                precedent->suivant = courant->suivant;

            free(courant);
            return tete;
        }
        precedent = courant;
        courant = courant->suivant;
    }
    return tete;
}

Element* rechercherSupport(Element *tete, int id) {
    while (tete != NULL) {
        if (tete->support.id == id)
            return tete;
        tete = tete->suivant;
    }
    return NULL;
}

void afficherSupports(Element *tete) {
    printf("\n**********************************************************************************************************\n");
    printf("\n                     LIste des supports                                                                   \n");
    printf("\n**********************************************************************************************************\n");


    while (tete != NULL) {
        printf("ID: %d\n",tete->support.id);
        printf("Titre: %s\n",tete->support.titre);
        printf("Module: %s\n",tete->support.module);
        printf("Type: %s\n",tete->support.type);
        printf("Enseignant: %s\n",tete->support.enseignant);
        printf("********************************************************************************************************\n");      
        tete = tete->suivant;
    }
}