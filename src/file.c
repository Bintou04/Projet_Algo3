#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

void initialiserFile(File *f) {
    f->debut = NULL;
    f->fin = NULL;
}

void enfiler(File *f, const char *message) {
    ElementFile *nouveau = malloc(sizeof(ElementFile));
    strcpy(nouveau->message, message);
    nouveau->suivant = NULL;

    if (f->fin == NULL) {
        f->debut = f->fin = nouveau;
    } else {
        f->fin->suivant = nouveau;
        f->fin = nouveau;
    }
}

void defiler(File *f) {
    if (f->debut == NULL) return;

    ElementFile *temp = f->debut;
    f->debut = temp->suivant;
    free(temp);
}

void afficherFile(File f) {
    printf("\n**********************************************************************************************************\n");
    printf("\n                     NOTIFICATION                                                                         \n");
    printf("\n**********************************************************************************************************\n");

    while (f.debut != NULL) {
        printf("Notification : %s\n", f.debut->message);
        f.debut = f.debut->suivant;
    }
}