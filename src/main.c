#include <stdio.h>
#include "support.h"
#include "list.h"
#include "pile.h"
#include "file.h"

int main() {
    Element *liste = NULL;
    ElementPile *historique = NULL;
    File notifications;

    initialiserFile(&notifications);

    Support s1 = {1, "Algorithmique", "Informatique", "PDF", "Mr Diallo", "/docs/algo.pdf"};
    Support s2 = {2, "Langage C", "Programmation", "PPT", "Mme Ndiaye", "/docs/c.ppt"};

    liste = ajouterSupport(liste, s1);
    empiler(&historique, s1);
    enfiler(&notifications, "Support Algorithmique ajoute");

    liste = ajouterSupport(liste, s2);
    empiler(&historique, s2);
    enfiler(&notifications, "Support Langage C ajoute");

    printf("\n--- LISTE DES SUPPORTS ---\n");
    afficherSupports(liste);

    printf("\n--- HISTORIQUE ---\n");
    afficherPile(historique);

    printf("\n--- NOTIFICATIONS ---\n");
    afficherFile(notifications);

    return 0;
}