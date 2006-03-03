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

#include "qalfsearchwidget.h"

QalfSearchWidget::QalfSearchWidget(QWidget * parent) : QWidget(parent) {

	// Init of search bar
	gSearchBar = new QWidget(this) ;
	QHBoxLayout * layout1 = new QHBoxLayout() ;
	gSearchLabel = new QLabel(tr("rechercher (mots-clés) :")) ;
	gSearchEdit = new QLineEdit(gSearchBar) ;
	layout1->addWidget(gSearchLabel) ;
	layout1->addWidget(gSearchEdit) ;
	
	QHBoxLayout * layout2 = new QHBoxLayout() ;
	gSearchOnLabel = new QLabel(tr("sur :")) ;
	gOnComputerButton = new QRadioButton(tr("mon ordinateur")) ;
	gOnTLButton = new QRadioButton(tr("le réseau torrentlibre")) ;
	layout2->addWidget(gSearchOnLabel) ;
	layout2->addWidget(gOnComputerButton) ;
	layout2->addWidget(gOnTLButton) ;
	layout2->addStretch() ;
	
	QHBoxLayout * layout3 = new QHBoxLayout() ;
	gMediaLabel = new QLabel(tr("media :")) ;
	gMediaMusic = new QCheckBox(tr("musique")) ;
	gMediaImage = new QCheckBox(tr("image")) ;
	gMediaText = new QCheckBox(tr("texte")) ;
	layout3->addWidget(gMediaLabel) ;
	layout3->addWidget(gMediaMusic) ;
	layout3->addWidget(gMediaImage) ;
	layout3->addWidget(gMediaText) ;
	layout3->addStretch() ;
	
	QHBoxLayout * layout31 = new QHBoxLayout() ;
	gAuthorLabel = new QLabel(tr("auteurs :")) ;
	gAuthorEdit = new QLineEdit() ;
	layout31->addWidget(gAuthorLabel) ;
	layout31->addWidget(gAuthorEdit) ;
	layout31->addStretch() ;
	
	QHBoxLayout * layout32 = new QHBoxLayout() ;
	gLicenseLabel = new QLabel(tr("licences :")) ;
	gLicenseBy = new QCheckBox(tr("attribution"));
	gLicenseShare = new QCheckBox(tr("redistribution")) ;
	gLicenseDerivs = new QCheckBox(tr("modification")) ;
	gLicenseCommercial = new QCheckBox(tr("utilisation commerciale")) ;
	gLicenseShareAlike = new QCheckBox(tr("licence virale")) ;
	layout32->addWidget(gLicenseLabel) ;
	layout32->addWidget(gLicenseBy) ;
	layout32->addWidget(gLicenseShare) ;
	layout32->addWidget(gLicenseDerivs) ;
	layout32->addWidget(gLicenseCommercial) ;
	layout32->addWidget(gLicenseShareAlike) ;
	layout32->addStretch() ;
		
	gTabMediaSearch = new QTabWidget(gSearchBar) ;
	gMusicSearchTab = new QWidget() ;
	
	gMusicTitleLabel = new QLabel(tr("titre :")) ;
	gMusicTitleEdit = new QLineEdit() ;
	QHBoxLayout * layout4 = new QHBoxLayout() ;
	layout4->addWidget(gMusicTitleLabel) ;
	layout4->addWidget(gMusicTitleEdit) ;
	
	gMusicBandLabel = new QLabel(tr("groupe :")) ;
	gMusicBandEdit = new QLineEdit() ;
	QHBoxLayout * layout5 = new QHBoxLayout() ;
	layout5->addWidget(gMusicBandLabel) ;
	layout5->addWidget(gMusicBandEdit) ;
	
	gMusicAlbumLabel = new QLabel(tr("album :")) ;
	gMusicAlbumEdit = new QLineEdit() ;
	QHBoxLayout * layout6 = new QHBoxLayout() ;
	layout6->addWidget(gMusicAlbumLabel) ;
	layout6->addWidget(gMusicAlbumEdit) ;
	
	gMusicStyleLabel = new QLabel(tr("style :")) ;
	gMusicStyleEdit = new QComboBox() ;
	QHBoxLayout * layout7 = new QHBoxLayout() ;
	layout7->addWidget(gMusicStyleLabel) ;
	layout7->addWidget(gMusicStyleEdit) ;
	layout7->addStretch() ;
	
	QGridLayout * gridLayout = new QGridLayout() ;
	gridLayout->addLayout(layout4,0,0) ;
	gridLayout->addLayout(layout5,0,1) ;
	gridLayout->addLayout(layout6,1,0) ;
	gridLayout->addLayout(layout7,1,1) ;
	
	gMusicSearchTab->setLayout(gridLayout) ;
	
	gImageSearchTab = new QWidget() ;
	gTextSearchTab = new QWidget() ;
	
	gTabMediaSearch->addTab(gMusicSearchTab,tr("musique")) ;
	gTabMediaSearch->addTab(gImageSearchTab,tr("image")) ;
	gTabMediaSearch->addTab(gTextSearchTab,tr("texte")) ;
	gMusicSearchTab->setEnabled(false) ;
	gImageSearchTab->setEnabled(false) ;
	gTextSearchTab->setEnabled(false) ;
	
	QVBoxLayout * searchBarLayout = new QVBoxLayout() ;
	searchBarLayout->addLayout(layout1) ;
	searchBarLayout->addLayout(layout2) ;
	searchBarLayout->addLayout(layout31) ;
	searchBarLayout->addLayout(layout32) ;
	searchBarLayout->addLayout(layout3) ;
	searchBarLayout->addWidget(gTabMediaSearch) ;

	gSearchBar->setLayout(searchBarLayout) ;
	
	// Init of search results	
	gSearchResults = new QTableView(this);
	
	// Init of controls
	gSearchControls = new QWidget(this) ;
	QHBoxLayout * controlsLayout = new QHBoxLayout() ;
	gDownloadSelection = new QPushButton(tr("Télécharger la sélection")) ;
	controlsLayout->addWidget(gDownloadSelection) ;
	controlsLayout->addStretch() ;
	gSearchControls->setLayout(controlsLayout) ;
	
	// setting layout of the whole widget
	QVBoxLayout * searchLayout = new QVBoxLayout() ;
	searchLayout->addWidget(gSearchBar) ;
	searchLayout->addWidget(gSearchResults,1) ;
	searchLayout->addWidget(gSearchControls) ;
	this->setLayout(searchLayout) ;
	
	QObject::connect(gMediaMusic,SIGNAL(toggled(bool)),gMusicSearchTab,SLOT(setEnabled(bool))) ;
	QObject::connect(gMediaImage,SIGNAL(toggled(bool)),gImageSearchTab,SLOT(setEnabled(bool))) ;
	QObject::connect(gMediaText,SIGNAL(toggled(bool)),gTextSearchTab,SLOT(setEnabled(bool))) ;
}
