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

QalfDb::QalfDb(const QString & dbFile) {
	this->dbFile = dbFile ;
}

bool QalfDb::open() {
	// open or create database
	int rc = sqlite3_open(this->dbFile.toLocal8Bit().data(), &(this->db));
	if( rc ){
		qWarning("Can't open database") ;
		sqlite3_close(this->db);
		return false ;
	}
	
	// try to create tables if they don't already exist
	char * create_table = "CREATE TABLE license (acronym TEXT PRIMARY KEY, name TEXT) ; \
		CREATE TABLE file (hash TEXT PRIMARY KEY, path TEXT UNIQUE, torrent TEXT UNIQUE, authors TEXT, license TEXT, used INT) ; \
		CREATE TABLE music (hash TEXT PRIMARY KEY, title TEXT, band TEXT, album TEXT, style TEXT, duration INT) ; \
		CREATE TABLE text (hash TEXT PRIMARY KEY, title TEXT, category TEXT, style TEXT, pages INT) ; \
		CREATE TABLE image (hash TEXT PRIMARY KEY, title TEXT, size TEXT, format TEXT, category TEXT) ;" ;
	char *errMsg = 0;
	rc = sqlite3_exec(this->db, create_table, NULL, 0, &errMsg);

	return true ;
}

QalfDb::~QalfDb() {
	sqlite3_close(this->db);
}
