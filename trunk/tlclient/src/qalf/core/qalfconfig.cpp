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
	if(!configObject) {
		configObject = new QalfConfig() ;
		configObject->load() ;
	}
	return configObject ;
}

QalfConfig::QalfConfig() {
	QDir current_dir = QDir::home() ;
	QString tlDirProperty("tlDir") ;
	QString tlDir = current_dir.canonicalPath()+QString(QDir::separator())+QString(TL_DIR) ;
	setProperty(tlDirProperty,tlDir) ;
	QString torrentDirProperty("torrentDir") ;
	QString torrentDir = tlDir+QString(QDir::separator())+QString(TORRENT_DIR) ;
	setProperty(torrentDirProperty,torrentDir) ;

	if(!current_dir.exists(tlDir)) {
		current_dir.mkdir(tlDir) ;
	}
	current_dir.cd(tlDir) ;
	if(!current_dir.exists(torrentDir)) {
		current_dir.mkdir(torrentDir) ;
	}
	current_dir.cdUp() ;
	
	if(!current_dir.exists(TL_CONF_DIR)) {
		current_dir.mkdir(TL_CONF_DIR) ;
	}
	current_dir.cd(TL_CONF_DIR) ;
	this->configDir = current_dir.canonicalPath() ;
	this->dbFile = current_dir.absoluteFilePath(DB_FILE) ;
	this->confFile = current_dir.absoluteFilePath(CONF_FILE) ;
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
	qDebug() << "asking for lock read" ;
	lock.lockForRead() ;
	qDebug() << "got lock" ;
	QString value("") ;
	if(properties.contains(key)) {
		value = properties.value(key) ;
	}
	qDebug() << "releasing lock" ;
	lock.unlock() ;
	qDebug() << "lock released" ;
	return value ;
}

void QalfConfig::setProperty(QString &key, QString &value) {
	QString keyCopy(key) ;
	QString valueCopy(value) ;
	qDebug() << "asking for lock write" ;
	lock.lockForWrite() ;
	qDebug() << "lock got" ;
	properties[keyCopy] = valueCopy ;
	qDebug() << "releasing lock" ;
	lock.unlock() ;
}

void QalfConfig::save() {
	QFile file(confFile);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream out(&file);
	out << "<torrentlibre>\n";

	QString key ;
	qDebug() << "asking for lock read" ;
	lock.lockForRead() ;
	qDebug() << "lock got" ;
	QList<QString> keyList = properties.keys() ;
	foreach(key,keyList) {
		out << "\t<" << key << ">" << properties.value(key) << "</" << key << ">\n" ;
	}
	qDebug() << "releasing lock" ;
	lock.unlock() ;
	qDebug() << "lock released" ;
	out << "</torrentlibre>\n";
	file.close() ;
}

void QalfConfig::load() {
	qDebug() << "load file" ;
	QFile * file = new QFile(confFile);
	
	QXmlSimpleReader xmlReader;
	QXmlInputSource *source = new QXmlInputSource(file);

	QalfXmlConfigHandler *handler = new QalfXmlConfigHandler(this);
	xmlReader.setContentHandler(handler);
	xmlReader.setErrorHandler(handler);

	bool ok = xmlReader.parse(source);

	if (!ok)
		qDebug() << "Parsing failed." ;
}

QalfConfig::QalfXmlConfigHandler::QalfXmlConfigHandler(QalfConfig * configObject) : QXmlDefaultHandler(), currentProp("") {
	this->configObject = configObject ;
}

bool QalfConfig::QalfXmlConfigHandler::startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts) {
	Q_UNUSED(namespaceURI) ;
	Q_UNUSED(qName) ;
	Q_UNUSED(atts) ;
	if(localName != "torrentlibre") currentProp = localName ;
	return true ;
}

bool QalfConfig::QalfXmlConfigHandler::characters(const QString & ch) {
	if(currentProp != "") {
		QString value(ch) ;
		configObject->setProperty(currentProp,value) ;
		currentProp = "" ;
	}
	return true ;
}
