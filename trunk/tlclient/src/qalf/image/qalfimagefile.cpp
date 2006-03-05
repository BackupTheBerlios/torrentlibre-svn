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

#include "qalfimagefile.h"

QalfImageFile::QalfImageFile() : QalfFile(),title(""),format(""),category("") {

}

QalfImageFile::QalfImageFile(const QString & hash, const QString & torrentPath) : QalfFile(hash,torrentPath),title(""),format(""),category("") {

}

QalfImageFile::~QalfImageFile() {

}

QalfImageFile::QalfImageFile(const QalfImageFile& imageFile) : QalfFile(imageFile.getHash(),imageFile.getTorrentPath()) {
	this->title = imageFile.getTitle() ;
	this->size = imageFile.getSize() ;
	this->format = imageFile.getFormat() ;
	this->category = imageFile.getCategory() ;
	this->filePath = imageFile.getFilePath() ;
	this->authors = imageFile.getAuthors() ;
	this->license = imageFile.getLicense() ;
	this->used = imageFile.getUsed() ;
}

void QalfImageFile::setTitle(QString & title) {
	this->title = title ;
}

void QalfImageFile::setSize(QSize & size) {
 this->size = size ;
}

void QalfImageFile::setFormat(QString & format) {
	this->format = format ;
}

void QalfImageFile::setCategory(QString & category) {
	this->category = category ;
}

QString QalfImageFile::getTitle() const {
	return this->title ;
}

QSize QalfImageFile::getSize() const {
	return this->size ;
}

QString QalfImageFile::getFormat() const {
	return this->format ;
}

QString QalfImageFile::getCategory() const {
	return this->category ;
}
