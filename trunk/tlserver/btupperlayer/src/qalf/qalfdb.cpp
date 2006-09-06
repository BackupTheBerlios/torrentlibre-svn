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

// QalfDb * QalfDb::dbObject(0) ;
QHash<Qt::HANDLE,QalfDb *> QalfDb::connections = QHash<Qt::HANDLE,QalfDb *>() ;

QalfDb * QalfDb::getDbObject() {
	Qt::HANDLE threadId = QThread::currentThreadId() ;
	qDebug() << "threadId" << threadId ;
	QalfDb * dbObject ;
	if(connections.contains(threadId)) {
		dbObject = connections[threadId] ;
	} else {
		QString id = QString::number(threadId) ;
		dbObject = new QalfDb(id) ;
		if(connections.isEmpty()) {
			bool creation = dbObject->create() ;
		}
		connections[threadId] = dbObject ;
	}
// 	if(!dbObject) {
// 		dbObject = new QalfDb() ;
// 	}
	return dbObject ;
}

QalfDb::QalfDb(QString &connectionName) {
	qDebug() << "addDatabase" ;
	db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
	qDebug() << "loading config" ;
	QalfConfig * config = QalfConfig::getConfigObject() ;
	qDebug() << "setDbname" ;
	db.setDatabaseName(config->getDbFile());
	qDebug() << "opening db" ;
	bool ok = db.open();
	qDebug() << "opening database :" << ok ;
}

QalfDb::~QalfDb() {
	
}

bool QalfDb::create() {
	QSqlQuery query;
	query = db.exec("CREATE TABLE key (email TEXT PRIMARY KEY, name TEXT UNIQUE, key BLOB, trusted INTEGER default 0)") ;
	query = db.exec("CREATE TABLE licenses (license TEXT PRIMARY KEY, attribution INTEGER default 0, redistribution INTEGER default 0, modification INTEGER default 0, commercial_use INTEGER default 0, share_alike INTEGER default 0)") ;
	query = db.exec("CREATE TABLE file (hash TEXT PRIMARY KEY, torrent TEXT UNIQUE, license TEXT)") ;
	query = db.exec("CREATE TABLE music (hash TEXT PRIMARY KEY, title TEXT, band TEXT, album TEXT, style TEXT, duration INT)") ;
	query = db.exec("CREATE TABLE text (hash TEXT PRIMARY KEY, title TEXT, category TEXT, style TEXT, pages INT)") ;
	query = db.exec("CREATE TABLE image (hash TEXT PRIMARY KEY, title TEXT, size TEXT, format TEXT, category TEXT)") ;
	query = db.exec("CREATE TABLE author (hash TEXT, author TEXT, PRIMARY KEY(hash,author))") ;
	query = db.exec("CREATE TABLE keyword (hash TEXT, keyword TEXT, PRIMARY KEY(hash,keyword))") ;

	return true ;
}

bool QalfDb::insertKey(QString& email,QString& name, QString& key) {
	QSqlQuery query(db);
	query.prepare("INSERT INTO key (email, name, key) VALUES (?,?,?)");
	query.addBindValue(email) ;
	query.addBindValue(name) ;
	query.addBindValue(key) ;
	query.exec() ;
	qDebug() << "sql lastquery :" << query.lastQuery() ;
	qDebug() << "sql lasterror :" << query.lastError() ; 
	return true ;
}

QHash<QString,QString> QalfDb::getKeyInfo(QString& email) {
	QSqlQuery query(db) ;
	query.prepare("SELECT name,key,trusted FROM key WHERE email = ?") ;
	query.addBindValue(email) ;
	query.exec() ;
	qDebug() << "sql lastquery :" << query.executedQuery() ;
	qDebug() << "sql lasterror :" << query.lastError() ; 
	
	QHash<QString,QString> result ;
	
	if(query.next()) {
		qDebug() << "key from request :" << query.value(0).toString() ;
		result["name"] = query.value(0).toString() ;
		result["key"] = query.value(1).toString() ;
		result["trusted"] = query.value(2).toString() ;
		qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() ;
	}
	return result ;	
}

QList<QString> QalfDb::getLicenses() {
	QSqlQuery query(db) ;
	query.exec("SELECT license FROM licenses") ;
	qDebug() << "sql lastquery :" << query.executedQuery() ;
	qDebug() << "sql lasterror :" << query.lastError() ; 
	
	QList<QString> result ;
	
	while(query.next()) {
		result << query.value(0).toString() ;
	}
	return result ;
}

void QalfDb::close() {
	db.close();
}

