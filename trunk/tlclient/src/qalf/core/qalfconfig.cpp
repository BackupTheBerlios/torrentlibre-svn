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

#include "qalfconfig.h"
#include <QDir>
#include <QtDebug>

QalfConfig * QalfConfig::configObject(0) ;

QalfConfig * QalfConfig::getConfigObject() {
	if(!configObject) configObject = new QalfConfig() ;
	return configObject ;
}

QalfConfig::QalfConfig() {
	QDir current_dir = QDir::home() ;
	if(!current_dir.exists(TL_DIR)) {
		current_dir.mkdir(TL_DIR) ;
	}
	current_dir.cd(TL_DIR) ;
	this->configDir = current_dir.canonicalPath() ;
	this->dbFile = current_dir.absoluteFilePath(DBFILE) ;
}

QalfConfig::~QalfConfig() {
	
}

QString QalfConfig::getConfigDir() const {
	return QString(this->configDir) ;
}

QString QalfConfig::getDbFile() const {
	return QString(this->dbFile) ;
}

QString QalfConfig::getProperty(QString &key) {
	lock.lockForRead() ;
	if(properties.contains(key)) {
		return properties.value(key) ;
	} else {
		return QString("") ;
	}
	lock.unlock() ;
}

void QalfConfig::setProperty(QString &key, QString &value) {
	QString keyCopy(key) ;
	QString valueCopy(value) ;
	lock.lockForWrite() ;
	properties[keyCopy] = valueCopy ;
	lock.unlock() ;
}

void QalfConfig::save() {
	lock.lockForWrite() ;
	for(QHash<QString, QString>::const_iterator i = properties.constBegin();i < properties.constEnd();++i) {
		qDebug() << "<" << i.key() << ">" << i.value() << "</" << i.key() << ">" ;
	}
	lock.unlock() ;
}

void QalfConfig::load() {

}
