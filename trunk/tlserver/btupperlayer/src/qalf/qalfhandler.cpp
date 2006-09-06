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
#include "qalftorrent.h"
#include "qalfcrypto.h"
#include "qalfconfig.h"

QalfHandler::QalfHandler() : QObject() {

}

bool QalfHandler::recordKey(QString& name, QString& email, QString& key) {
	QalfCrypto crypto ;
	QString fingerPrint = crypto.importKey(key) ;
	qDebug() << "fingerprint is " << fingerPrint ;
	QalfDb * db = QalfDb::getDbObject() ;
	return db->insertKey(email,name,fingerPrint) ;
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

QList<QString> QalfHandler::getLicenses() {
	QalfDb * db = QalfDb::getDbObject() ;
	return db->getLicenses() ;
}

int QalfHandler::storeTorrent(QString &moderatorEmail, QString &signature, QString &title, QString &authors, QString &license, QString &keywords, QString &category, QByteArray &torrentData) {
	// loading torrent in torrent structure
	QalfTorrent torrent(torrentData) ;
	
	// getting hash and key
	QString hash = torrent.hashToStr() ;
	QalfDb * db = QalfDb::getDbObject() ;
	
	QHash<QString,QString> keyInfo = db->getKeyInfo(moderatorEmail) ;
	if(!keyInfo.isEmpty() && keyInfo["trusted"] == "1") {
		// verifying signature
		QalfCrypto crypto ;
		qDebug() << "keyInfo" << keyInfo["key"] ;
		bool verification = crypto.verify(signature, hash, keyInfo["key"]) ;
		if(verification) {
			// storing on hd
			QalfConfig * config = QalfConfig::getConfigObject() ;
			QString torrentDirProp("torrentDir") ;
			QString torrentFilename = config->getProperty(torrentDirProp)+QString(QDir::separator())+hash+".torrent" ;
		
			QFile file(torrentFilename) ;
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
				return CANNOTSTORETORRENT;

			QTextStream out(&file);
			out << torrentData ;
			
			// storing meta information in db
		
			return NO_ERROR ;
		} else {
			return BADSIGNATURE ;
		}
	} else {
		return USERNOTTRUSTED ;
	}
}
