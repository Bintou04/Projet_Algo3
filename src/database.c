#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

/* Connexion globale Mysql */
MYSQL *conn;

/* Connexion sur la base de donne Mysql */
int connectDatabase() {
    conn = mysql_init(NULL);

    if (conn == NULL) {
        printf("MySQL initialization failed\n");
        return 0;
    }

    if (mysql_real_connect(
            conn,
            "localhost",
            "root",
            "",
            "cours_supports",
            0,
            NULL,
            0) == NULL) {

        printf("Database connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    printf("Connected to database successfully\n");
    return 1;
}

/* fermeture de la connexion */
void closeDatabase() {
    if (conn != NULL) {
        mysql_close(conn);
        conn = NULL;
    }
}

/* changer le support de la base de donner dans la liste lier */
int loadSupportsFromDB(Node **head) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM support")) {
        printf("SELECT failed: %s\n", mysql_error(conn));
        return 0;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        printf("Result error: %s\n", mysql_error(conn));
        return 0;
    }

    while ((row = mysql_fetch_row(res))) {
        Support s;

        s.id = atoi(row[0]);
        strcpy(s.title, row[1]);
        strcpy(s.module, row[2]);
        strcpy(s.type, row[3]);
        strcpy(s.teacher, row[4]);
        strcpy(s.path, row[5]);
        strcpy(s.date_added, row[6]);

        insertAtEnd(head, s);  // fonction  a partir de  list.c
    }

    mysql_free_result(res);
    return 1;
}

/* Inserer un support dans la base de donne */
int insertSupportToDB(Support s) {
    char query[1024];

    sprintf(query,
        "INSERT INTO support (title, module, type, teacher, path, date_added) "
        "VALUES ('%s', '%s', '%s', '%s', '%s', '%s')",
        s.title, s.module, s.type, s.teacher, s.path, s.date_added
    );

    if (mysql_query(conn, query)) {
        printf("Insert failed: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}

/* supprimer un support de la base de donnees */
int deleteSupportFromDB(int id) {
    char query[256];

    sprintf(query, "DELETE FROM support WHERE id=%d", id);

    if (mysql_query(conn, query)) {
        printf("Delete failed: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}

/* mis a jour d'un support dans la base de donnees */
int updateSupportInDB(Support s) {
    char query[1024];

    sprintf(query,
        "UPDATE support SET title='%s', module='%s', type='%s', "
        "teacher='%s', path='%s', date_added='%s' WHERE id=%d",
        s.title, s.module, s.type,
        s.teacher, s.path, s.date_added, s.id
    );

    if (mysql_query(conn, query)) {
        printf("Update failed: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}
