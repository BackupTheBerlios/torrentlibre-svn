/*******************************************************
** Copyright (C) 2006 Francois Gaudin.
**
** Torrentlibre is free software; you can redistribute
** it and/or modify it under the terms of the GNU
** Library General Public License as published by the
** Free Software Foundation; either version 2, or (at
** your option) any later version.
**
********************************************************/

#ifndef QalfDB_H
#define QalfDB_H
#include <QFileInfo>
#include <sqlite3.h>

// static int callback(void *NotUsed, int argc, char **argv, char **azColName){
//   int i;
//   for(i=0; i<argc; i++){
//     printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//   }
//   printf("\n");
//   return 0;
// }

class QalfDb : public QObject {
	Q_OBJECT
	
	public:
		QalfDb(const QString & dbFile) ;
		~QalfDb() ;
		bool open() ;
		
	protected:
		QString dbFile ;
		sqlite3 *db;
		
};

#endif // QalfDB_H
