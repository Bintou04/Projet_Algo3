#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include "support.h"

/* connexion */
int connectDatabase(void);
void closeDatabase(void);

/* operations CRUD */
int loadSupportsFromDB(void);
int insertSupportToDB(Support s);
int deleteSupportFromDB(int id);
int updateSupportInDB(Support s);

#endif
