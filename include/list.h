#ifndef LISTE_H
#define LISTE_H

#include "support.h"

typedef struct Element {
    Support support;
    struct Element *suivant;
} Element;

Element* ajouterSupport(Element *tete, Support s);
Element* supprimerSupport(Element *tete, int id);
Element* rechercherSupport(Element *tete, int id);
void afficherSupports(Element *tete);

#endif