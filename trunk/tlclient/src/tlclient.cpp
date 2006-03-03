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

#include <QApplication>
#include <QtDebug>
#include "qalfconfig.h"
#include "qalfdb.h"
#include "qalfmainwindow.h"

int main(int argc, char *argv[])
{
	// check config files and create them if they don't exist
	QalfConfig * config = new QalfConfig ;
	
	// load or create database
	QalfDb * db = new QalfDb(config->getDbFile()) ;
	db->open() ;
	
	QApplication app(argc, argv);
	QalfMainWindow mainWin;
	mainWin.show();
	return app.exec();
}

