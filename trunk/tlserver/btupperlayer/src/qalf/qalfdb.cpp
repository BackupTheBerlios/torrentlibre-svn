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
	query = db.exec("CREATE TABLE key (email TEXT PRIMARY KEY, name TEXT, key BLOB, trusted INTEGER default 0)") ;

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

void QalfDb::close() {
	db.close();
}

