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
#include <QtGui>
#include "qalfconfig.h"
#include "qalfdb.h"
#include "qalfimagetreemodel.h"
#include "qalfmainwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	// showing splashscreen while loading
	QPixmap pixmap(":/icons/splash.png");
	QSplashScreen *splash = new QSplashScreen(pixmap);
	splash->show();
	
	splash->showMessage(QObject::tr("Initializing main window"));
	app.processEvents();
	QalfMainWindow mainWin;
// 	for(int i =0 ; i < 1000000000;i++) {
// 		float a = 1324234.234234/132424.234 ;
// 	}
	// check config files and create them if they don't exist
	splash->showMessage(QObject::tr("Loading configuration"));
	app.processEvents();
	QalfConfig * config = new QalfConfig ;
// 	for(int i =0 ; i < 1000000000;i++) {
// 		float a = 1324234.234234/132424.234 ;
// 	}
	
	// load or create database
	splash->showMessage(QObject::tr("Loading database"));
	app.processEvents();
	QalfDb * db = new QalfDb(config->getDbFile()) ;
	db->open() ;
	db->start() ;
	
	// load images data
	QalfImageTreeModel * imageTreeModel = new QalfImageTreeModel(db) ;
	qDebug() << "imageTreeModel->loadData()" ;
	imageTreeModel->loadData() ;
	qDebug() << "mainWin.setImageModel(imageTreeModel)" ;
	mainWin.setImageModel(imageTreeModel) ;
	
// 	for(int i =0 ; i < 1000000000;i++) {
// 		float a = 1324234.234234/132424.234 ;
// 	}
	
	mainWin.show();
	splash->finish(&mainWin);
	delete splash;
	
	int appReturn = app.exec() ;
	db->closeAndExit() ;
	
	return appReturn;
}

