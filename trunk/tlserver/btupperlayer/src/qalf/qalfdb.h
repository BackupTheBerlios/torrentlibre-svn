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
// #include <QThread>
#include <QtDebug>
// #include <sqlite3.h>
#include <QHash>
#include <QtSql>
#include <QList>

class QalfDb : public QObject {
	Q_OBJECT
	
	public:
		static QalfDb * getDbObject() ;
// 		void run();
		bool create() ;
		
		QList<QHash<QString,QString> *> * selectAllByMedia(QString & media) ;
		
	public slots:
		void close() ;
	
	protected:
		static QalfDb * dbObject ;
		QSqlDatabase db ;

		QalfDb() ;
		~QalfDb() ;
		
};

#endif // QalfDB_H
