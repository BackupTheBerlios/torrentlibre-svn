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

#include "qalfmainwindow.h"

QalfMainWindow::QalfMainWindow() {
	QSplitter * centralWidget = new QSplitter(this) ;
	
	gLibrary = new QToolBox(centralWidget) ;
	gMusicTree = new QTreeView(gLibrary) ;
	gLibrary->addItem(gMusicTree,tr("Musique")) ;
	gImageTree = new QTreeView(gLibrary) ;
	gLibrary->addItem(gImageTree,tr("Images")) ;
	gTextTree = new QTreeView(gLibrary) ;
	gLibrary->addItem(gTextTree,tr("Textes")) ;
	
	gTabActions = new QTabWidget(centralWidget) ;
	searchTab = new QalfSearchWidget() ;
	gTabActions->addTab(searchTab,tr("Rechercher")) ;
	
	centralWidget->addWidget(gLibrary) ;
	centralWidget->addWidget(gTabActions) ;
	
	this->setCentralWidget(centralWidget) ;
}
