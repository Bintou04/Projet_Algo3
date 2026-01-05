#ifndef PILE_H
#define PILE_H

#include "support.h"

typedef struct ElementPile {
    Support support;
    struct ElementPile *suivant;
} ElementPile;

void empiler(ElementPile **sommet, Support s);
void depiler(ElementPile **sommet);
void afficherPile(ElementPile *sommet);

#endif