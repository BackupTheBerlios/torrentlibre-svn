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
