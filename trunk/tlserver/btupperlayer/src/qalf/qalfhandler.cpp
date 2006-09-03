/*******************************************************
** Copyright (C) 2006 Francois Gaudin.
**
** BtUpperLayer is free software; you can redistribute
** it and/or modify it under the terms of the GNU
** Library General Public License as published by the
** Free Software Foundation; either version 2, or (at
** your option) any later version.
**
********************************************************/

#include "qalfhandler.h"
#include "qalfdb.h"

QalfHandler::QalfHandler() : QObject() {

}

bool QalfHandler::recordKey(QString& name, QString& email, QString& key) {
	QalfDb * db = QalfDb::getDbObject() ;
	return db->insertKey(email,name,key) ;
	
}

QalfHandler::KeyStatus QalfHandler::keyStatus(QString &email) {
	QalfDb * db = QalfDb::getDbObject() ;
	qDebug() << "checking key for :"<< email ;
	QHash<QString,QString> keyInfo = db->getKeyInfo(email) ;
	if(keyInfo.isEmpty()) {
		return KeyUnknown ;
	} else {
		if(keyInfo["trusted"] == "0") {
			return KeyUntrusted ;
		} else {
			return KeyTrusted ;
		}
	}
}
