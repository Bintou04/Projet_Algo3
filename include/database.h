#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>
#include "support.h"
#include "list.h"

/* connexion a la base de donnees */
int connectDatabase();
void closeDatabase();

/* Operations sur la base de donneesda */
int loadSupportsFromDB(Node **head);
int insertSupportToDB(Support s);
int deleteSupportFromDB(int id);
int updateSupportInDB(Support s);

#endif
