#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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

Element* chercherSupport(Element *tete, int id) {
    while (tete != NULL) {
        if (tete->support.id == id)
            return tete;
        tete = tete->suivant;
    }
    return NULL;
}

void afficherSupports(Element *tete) {
    while (tete != NULL) {
        printf("ID: %d | %s | %s\n",
               tete->support.id,
               tete->support.titre,
               tete->support.module);
        tete = tete->suivant;
    }
}