#ifndef FILE_H
#define FILE_H

typedef struct ElementFile {
    char message[100];
    struct ElementFile *suivant;
} ElementFile;

typedef struct {
    ElementFile *debut;
    ElementFile *fin;
} File;

void initialiserFile(File *f);
void enfiler(File *f, const char *message);
void defiler(File *f);
void afficherFile(File f);

#endif