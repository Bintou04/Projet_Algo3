#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include "database.h"
#include "support.h"
#include "list.h"

/* connexion SQLite globale */
sqlite3 *db;

/* tête de liste (définie dans list.c ou main.c) */
extern Element *tete;

/*
   Connexion à la base
 */
int connectDatabase() {
    int rc = sqlite3_open("support.db", &db);
    if (rc != SQLITE_OK) {
        printf("Erreur ouverture SQLite : %s\n", sqlite3_errmsg(db));
        return 0;
    }
    return 1;
}

/*
   Fermeture de la base
 */
void closeDatabase() {
    if (db != NULL) {
        sqlite3_close(db);
        db = NULL;
    }
}

/*
   Charger les supports
 */
int loadSupportsFromDB() {
    const char *sql = "SELECT * FROM support;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erreur SELECT : %s\n", sqlite3_errmsg(db));
        return 0;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Support s;

        s.id = sqlite3_column_int(stmt, 0);

        strcpy(s.titre,      (const char *)sqlite3_column_text(stmt, 1));
        strcpy(s.module,     (const char *)sqlite3_column_text(stmt, 2));
        strcpy(s.type,       (const char *)sqlite3_column_text(stmt, 3));
        strcpy(s.enseignant, (const char *)sqlite3_column_text(stmt, 4));
        strcpy(s.chemin,     (const char *)sqlite3_column_text(stmt, 5));

        /* ajout dans la liste */
        tete = ajouterSupport(tete, s);
    }

    sqlite3_finalize(stmt);
    return 1;
}

/*
   Insertion d'un support
 */
int insertSupportToDB(Support s) {
    const char *sql =
        "INSERT INTO support(titre, module, type, enseignant, chemin) "
        "VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Erreur INSERT : %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, s.titre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, s.module, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, s.type, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, s.enseignant, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, s.chemin, -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

/*
   Suppression d'un support
 */
int deleteSupportFromDB(int id) {
    const char *sql = "DELETE FROM support WHERE id = ?;";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}

/*
   Mise à jour d'un support
 */
int updateSupportInDB(Support s) {
    const char *sql =
        "UPDATE support SET titre=?, module=?, type=?, enseignant=?, chemin=? "
        "WHERE id=?;";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, s.titre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, s.module, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, s.type, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, s.enseignant, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, s.chemin, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, s.id);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE;
}
