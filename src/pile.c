#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

void empiler(ElementPile **sommet, Support s) {
    ElementPile *nouveau = malloc(sizeof(ElementPile));
    nouveau->support = s;
    nouveau->suivant = *sommet;
    *sommet = nouveau;
}

void depiler(ElementPile **sommet) {
    if (*sommet == NULL) return;

    ElementPile *temp = *sommet;
    *sommet = temp->suivant;
    free(temp);
}

void afficherPile(ElementPile *sommet) {
    while (sommet != NULL) {
        printf("Historique : %s\n", sommet->support.titre);
        sommet = sommet->suivant;
    }
}