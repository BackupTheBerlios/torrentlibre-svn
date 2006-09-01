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
	qDebug() << "addDatabase" ;
	db = QSqlDatabase::addDatabase("QSQLITE");
	qDebug() << "loading config" ;
	QalfConfig * config = QalfConfig::getConfigObject() ;
	qDebug() << "setDbname" ;
	db.setDatabaseName(config->getDbFile());
	qDebug() << "opening db" ;
	bool ok = db.open();
	bool creation = create() ;
	qDebug() << "opening database :" << ok ;
}

QalfDb::~QalfDb() {
	
}

bool QalfDb::create() {
	QSqlQuery query;
	query.exec("CREATE TABLE key (email TEXT PRIMARY KEY, name TEXT, key TEXT)") ;

	return true ;
}

bool QalfDb::insertKey(QString& email,QString& name, QString& key) {
	QSqlQuery query;
	QString request = "INSERT INTO key (email,name,key) values(\""+email+"\",\""+name+"\",\""+key+"\")" ;
	query.exec(request) ;
	return true ;
}

void QalfDb::close() {
	db.close();
}

