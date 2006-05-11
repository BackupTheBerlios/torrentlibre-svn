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
#include "treeitem.h"
#include "qalfmoderatordialog.h"

QalfMainWindow::QalfMainWindow() {
	createMenu() ;
	QSplitter * centralWidget = new QSplitter(this) ;
	
	gLibrary = new QToolBox(centralWidget) ;
	gMusicTree = new QTreeView(gLibrary) ;
	gLibrary->addItem(gMusicTree,QIcon(":/icons/cd.png"),tr("Music")) ;
	gImageTree = new QTreeView(gLibrary) ;
	gImageTree->header()->hide() ;
	gLibrary->addItem(gImageTree,QIcon(":/icons/imagegallery.png"),tr("Images")) ;
	gTextTree = new QTreeView(gLibrary) ;
	gLibrary->addItem(gTextTree,QIcon(":/icons/toggle_log.png"),tr("Texts")) ;
	
	gTabActions = new QTabWidget(centralWidget) ;
	gSearchTab = new QalfSearchWidget() ;
	gTabActions->addTab(gSearchTab,QIcon(":/icons/viewmag.png"),tr("Search")) ;
	gImageTab = new QalfImageWidget() ;
	gTabActions->addTab(gImageTab,QIcon(":/icons/imagegallery.png"),tr("Look")) ;
	
	centralWidget->addWidget(gLibrary) ;
	centralWidget->addWidget(gTabActions) ;
	
	this->setCentralWidget(centralWidget) ;
	
	connect(gImageTree,SIGNAL(clicked(QModelIndex)),this,SLOT(openImage(QModelIndex))) ;
	connect(this,SIGNAL(imageChanged(QString)),gImageTab,SLOT(setImage(QString))) ;
}

void QalfMainWindow::createMenu() {
	quitAction = new QAction(tr("&Quit"), this);
	quitAction->setShortcut(tr("Ctrl+Q"));
	quitAction->setStatusTip(tr("Quit torrentlibre"));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

	appMenu = this->menuBar()->addMenu(tr("&File"));
	appMenu->addAction(quitAction) ;

	prefAction = new QAction(tr("&Preferences"), this);
	prefAction->setShortcut(tr("Ctrl+P"));
	prefAction->setStatusTip(tr("Edit preferences"));
// 	connect(prefAction, SIGNAL(triggered()), this, SLOT(close()));
	
	moderatorModeAction = new QAction(tr("&Moderator mode"), this);
	moderatorModeAction->setShortcut(tr("Ctrl+M"));
	moderatorModeAction->setStatusTip(tr("Set moderator mode"));
	moderatorModeAction->setCheckable(true) ;

	moderatorDialogAction = new QAction(tr("Mo&derator preferences"), this);
	moderatorDialogAction->setShortcut(tr("Ctrl+L"));
	moderatorDialogAction->setStatusTip(tr("Edit moderator preferences"));
	moderatorDialogAction->setVisible(false) ;
	connect(moderatorModeAction, SIGNAL(toggled(bool)), moderatorDialogAction, SLOT(setVisible(bool)));
	connect(moderatorDialogAction, SIGNAL(triggered()), this, SLOT(showModeratorDialog()));

	configMenu = this->menuBar()->addMenu(tr("&Configuration"));
	configMenu->addAction(prefAction) ;
	configMenu->addAction(moderatorModeAction) ;
	configMenu->addAction(moderatorDialogAction) ;
}

void QalfMainWindow::setImageModel(QalfImageTreeModel * imageTreeModel) {
	gImageTree->setModel(imageTreeModel) ;
}

void QalfMainWindow::showModeratorDialog() {
	QalfModeratorDialog dialogBox ;
	dialogBox.exec() ;
}

void QalfMainWindow::openImage(const QModelIndex & index) {
	qDebug() << "openImage called" ;
	TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
	QVariant data = item->data(index.column());
	if(QString(data.typeName()) != "QString") {
		qDebug() << "file path : " << data.value<QalfImageFile *>()->getFilePath() ;
		emit imageChanged(data.value<QalfImageFile *>()->getFilePath()) ;
	}
}
