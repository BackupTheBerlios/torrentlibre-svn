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

#include "qalfdb.h"
#include "qalfconfig.h"

QalfDb * QalfDb::dbObject(0) ;

QalfDb * QalfDb::getDbObject() {
	if(!dbObject) {
		dbObject = new QalfDb() ;
	}
	return dbObject ;
}

QalfDb::QalfDb() {
	db = QSqlDatabase::addDatabase("QSQLITE");
	QalfConfig * config = QalfConfig::getConfigObject() ;
	db.setDatabaseName(config->getDbFile());
	bool ok = db.open();
	bool creation = create() ;
	qDebug() << "opening database :" << ok ;
}

QalfDb::~QalfDb() {
	
}

bool QalfDb::create() {
	QSqlQuery query;
	query.exec("CREATE TABLE license (acronym TEXT PRIMARY KEY, name TEXT)") ;
	query.exec("CREATE TABLE file (hash TEXT PRIMARY KEY, path TEXT UNIQUE, torrent TEXT UNIQUE, authors TEXT, license TEXT, used INT)") ;
	query.exec("CREATE TABLE music (hash TEXT PRIMARY KEY, title TEXT, band TEXT, album TEXT, style TEXT, duration INT)") ;
	query.exec("CREATE TABLE text (hash TEXT PRIMARY KEY, title TEXT, category TEXT, style TEXT, pages INT)") ;
	query.exec("CREATE TABLE image (hash TEXT PRIMARY KEY, title TEXT, size TEXT, format TEXT, category TEXT)") ;

	return true ;
}

// void QalfDb::run() {
// 	qDebug("Db thread started") ;
// 	exec() ;
// }

QList<QHash<QString,QString> *> * QalfDb::selectAllByMedia(QString & media) {
	QString sqlRequest = QString("select * from ")+media+QString(" m join file f on m.hash=f.hash ;") ;
	QSqlQuery query(sqlRequest) ;
	QSqlRecord record = query.record() ;
	int columnCount = record.count() ;

	QList<QHash<QString,QString> *> * resultList = new QList<QHash<QString,QString> *>() ;
	qDebug() << "result list initialized" ;

	while(query.next()) {
		QHash<QString,QString> * oneRow = new QHash<QString,QString>() ;
		for(int col=0;col < columnCount;++col) {
			QString fieldName(record.fieldName(col)) ;
			(*oneRow)[fieldName] = query.value(col).toString() ;
		}
		(*resultList) += oneRow ;
	}
	
	return resultList ;
}

void QalfDb::close() {
	db.close();
}

