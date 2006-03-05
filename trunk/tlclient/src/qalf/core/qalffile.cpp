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

#include "qalffile.h"

QalfFile::QalfFile() : hash(""), filePath(""),torrentPath(""), license(""), used(0)  {

}

QalfFile::QalfFile(const QString & hash, const QString & torrentPath) : filePath(""), license(""), used(0) {
	this->hash = hash ;
	this->torrentPath = torrentPath ;
}

QalfFile::~QalfFile() {
	
}

void QalfFile::setFilePath(QString & filePath) {
	this->filePath = filePath ;
}

void QalfFile::setTorrentPath(QString & torrentPath) {
	this->torrentPath = torrentPath ;
}

void QalfFile::setAuthors(QStringList & authors) {
	this->authors = authors ;
}

void QalfFile::setLicense(QString & license) {
	this->license = license ;
}

void QalfFile::setUsed(int used) {
	this->used = used ;
}

QString QalfFile::getHash() const {
	return this->hash ;
}

QString QalfFile::getFilePath() const {
	return this->filePath ;
}

QString QalfFile::getTorrentPath() const {
	return this->torrentPath ;
}

QStringList QalfFile::getAuthors() const {
	return QStringList(this->authors) ;
}

QString QalfFile::getLicense() const {
	return this->license ;
}

int QalfFile::getUsed() const {
	return this->used ;
}

void QalfFile::incrementUsed() {
 ++(this->used) ;
}
