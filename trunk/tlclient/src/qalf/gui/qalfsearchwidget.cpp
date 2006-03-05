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

	QSize iconSize(22, 22);
	// Init of search bar
	gSearchBar = new QWidget(this) ;
	QHBoxLayout * layout1 = new QHBoxLayout() ;
	gSearchLabel = new QLabel(tr("search (keywords) :")) ;
	gSearchEdit = new QLineEdit(gSearchBar) ;
	layout1->addWidget(gSearchLabel) ;
	layout1->addWidget(gSearchEdit) ;
	
	QHBoxLayout * layout2 = new QHBoxLayout() ;
	gSearchOnLabel = new QLabel(tr("on :")) ;
	gOnComputerButton = new QRadioButton(tr("my computer")) ;
	gOnTLButton = new QRadioButton(tr("torrentlibre network")) ;
	layout2->addWidget(gSearchOnLabel) ;
	layout2->addWidget(gOnComputerButton) ;
	layout2->addWidget(gOnTLButton) ;
	layout2->addStretch() ;
	
	QHBoxLayout * layout3 = new QHBoxLayout() ;
	gMediaLabel = new QLabel(tr("media :")) ;
	gMediaMusic = new QCheckBox(tr("music")) ;
	gMediaImage = new QCheckBox(tr("image")) ;
	gMediaText = new QCheckBox(tr("text")) ;
	layout3->addWidget(gMediaLabel) ;
	layout3->addWidget(gMediaMusic) ;
	layout3->addWidget(gMediaImage) ;
	layout3->addWidget(gMediaText) ;
	layout3->addStretch() ;
	
	QHBoxLayout * layout31 = new QHBoxLayout() ;
	gAuthorLabel = new QLabel(tr("authors :")) ;
	gAuthorEdit = new QLineEdit() ;
	layout31->addWidget(gAuthorLabel) ;
	layout31->addWidget(gAuthorEdit) ;
	layout31->addStretch() ;
	
	QHBoxLayout * layout32 = new QHBoxLayout() ;
	gLicenseLabel = new QLabel(tr("licenses :")) ;
	gLicenseBy = new QCheckBox(tr("attribution"));
	gLicenseShare = new QCheckBox(tr("redistribution")) ;
	gLicenseDerivs = new QCheckBox(tr("modification")) ;
	gLicenseCommercial = new QCheckBox(tr("commercial use")) ;
	gLicenseShareAlike = new QCheckBox(tr("share alike")) ;
	layout32->addWidget(gLicenseLabel) ;
	layout32->addWidget(gLicenseBy) ;
	layout32->addWidget(gLicenseShare) ;
	layout32->addWidget(gLicenseDerivs) ;
	layout32->addWidget(gLicenseCommercial) ;
	layout32->addWidget(gLicenseShareAlike) ;
	layout32->addStretch() ;
		
	gTabMediaSearch = new QTabWidget(gSearchBar) ;
	gMusicSearchTab = new QWidget() ;
	
	gMusicTitleLabel = new QLabel(tr("title :")) ;
	gMusicTitleEdit = new QLineEdit() ;
	QHBoxLayout * layout4 = new QHBoxLayout() ;
	layout4->addWidget(gMusicTitleLabel) ;
	layout4->addWidget(gMusicTitleEdit) ;
	
	gMusicBandLabel = new QLabel(tr("band :")) ;
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
	gridLayout->addLayout(layout5,0,2) ;
	gridLayout->addLayout(layout6,1,0) ;
	gridLayout->addLayout(layout7,1,2) ;
	gridLayout->setColumnMinimumWidth(1,25) ;
	gMusicSearchTab->setLayout(gridLayout) ;
	
	gImageSearchTab = new QWidget() ;
	gImageTitleLabel = new QLabel(tr("title :")) ;
	gImageTitleEdit = new QLineEdit() ;
	QHBoxLayout * layout8 = new QHBoxLayout() ;
	layout8->addWidget(gImageTitleLabel) ;
	layout8->addWidget(gImageTitleEdit,1) ;
	
	gImageSizeLabel = new QLabel(tr("dimensions :")) ;
	gImageWidthEdit = new QSpinBox() ;
// 	QSize size = gImageWidthEdit->minimumSizeHint() ;
// 	size.setWidth(40) ;
// 	gImageWidthEdit->setMaximumSize(size) ;
	gImageHeightEdit = new QSpinBox() ;
// 	size = gImageHeightEdit->minimumSizeHint() ;
// 	size.setWidth(40) ;
// 	gImageHeightEdit->setMaximumSize(size) ;
	QHBoxLayout * layout9 = new QHBoxLayout() ;
	layout9->addWidget(gImageSizeLabel) ;
	layout9->addWidget(gImageWidthEdit) ;
	layout9->addWidget(new QLabel("x")) ;
	layout9->addWidget(gImageHeightEdit) ;
	layout9->addStretch() ;
	
	gImageFormatLabel = new QLabel(tr("format :")) ;
	gImageFormatEdit = new QLineEdit() ;
	QSize size = gImageFormatEdit->minimumSizeHint() ;
	size.setWidth(40) ;
	gImageFormatEdit->setMaximumSize(size) ;
	QHBoxLayout * layout10 = new QHBoxLayout() ;
	layout10->addWidget(gImageFormatLabel) ;
	layout10->addWidget(gImageFormatEdit) ;
	layout10->addStretch() ;
	
	gImageCategoryLabel = new QLabel(tr("category :")) ;
	gImageCategoryEdit = new QComboBox() ;
	QHBoxLayout * layout11 = new QHBoxLayout() ;
	layout11->addWidget(gImageCategoryLabel) ;
	layout11->addWidget(gImageCategoryEdit) ;
	layout11->addStretch() ;
	
	QGridLayout * gridLayout2 = new QGridLayout() ;
	gridLayout2->addLayout(layout8,0,0) ;
	gridLayout2->addLayout(layout10,0,2) ;
	gridLayout2->addLayout(layout9,1,0) ;
	gridLayout2->addLayout(layout11,1,2) ;
	gridLayout2->setColumnMinimumWidth(1,25) ;
	gImageSearchTab->setLayout(gridLayout2) ;
	
	gTextSearchTab = new QWidget() ;
	gTextTitleLabel = new QLabel(tr("title :")) ;
	gTextTitleEdit = new QLineEdit() ;
	QHBoxLayout * layout12 = new QHBoxLayout() ;
	layout12->addWidget(gTextTitleLabel) ;
	layout12->addWidget(gTextTitleEdit) ;
	
	gTextCategoryLabel = new QLabel(tr("category :")) ;
	gTextCategoryEdit = new QComboBox() ;
	QHBoxLayout * layout13 = new QHBoxLayout() ;
	layout13->addWidget(gTextCategoryLabel) ;
	layout13->addWidget(gTextCategoryEdit) ;
	layout13->addStretch() ;
	
	gTextStyleLabel = new QLabel(tr("style :")) ;
	gTextStyleEdit = new QComboBox() ;
	QHBoxLayout * layout14 = new QHBoxLayout() ;
	layout14->addWidget(gTextStyleLabel) ;
	layout14->addWidget(gTextStyleEdit) ;
	layout14->addStretch() ;
	
	gTextPagesLabel = new QLabel(tr("pages :")) ;
	gTextPagesEdit = new QSpinBox() ;
	QHBoxLayout * layout15 = new QHBoxLayout() ;
	layout15->addWidget(gTextPagesLabel) ;
	layout15->addWidget(gTextPagesEdit) ;
	layout15->addStretch() ;
	
	QGridLayout * gridLayout3 = new QGridLayout() ;
	gridLayout3->addLayout(layout12,0,0,1,-1) ;
	gridLayout3->addLayout(layout13,1,0) ;
	gridLayout3->addLayout(layout14,1,2) ;
	gridLayout3->addLayout(layout15,1,4) ;
	gridLayout3->setColumnMinimumWidth(1,25) ;
	gridLayout3->setColumnMinimumWidth(3,25) ;
	gTextSearchTab->setLayout(gridLayout3) ;
	
	gTabMediaSearch->addTab(gMusicSearchTab,QIcon(":/icons/cd.png"),tr("music")) ;
	gTabMediaSearch->addTab(gImageSearchTab,QIcon(":/icons/imagegallery.png"),tr("image")) ;
	gTabMediaSearch->addTab(gTextSearchTab,QIcon(":/icons/toggle_log.png"),tr("text")) ;
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
	gDownloadSelection = new QPushButton(tr("Download selection")) ;
	gDownloadSelection->setIcon(QIcon(":/icons/1downarrow.png")) ;
	gDownloadSelection->setIconSize(iconSize) ;
	gDownloadAll = new QPushButton(tr("Download all")) ;
	gDownloadAll->setIcon(QIcon(":/icons/2downarrow.png")) ;
	gDownloadAll->setIconSize(iconSize) ;
	controlsLayout->addWidget(gDownloadSelection) ;
	controlsLayout->addWidget(gDownloadAll) ;
	controlsLayout->addStretch() ;
	gSearchControls->setLayout(controlsLayout) ;
	
	// setting layout of the whole widget
	QVBoxLayout * searchLayout = new QVBoxLayout() ;
	searchLayout->addWidget(gSearchBar) ;
	searchLayout->addWidget(gSearchResults,1) ;
	searchLayout->addWidget(gSearchControls) ;
	this->setLayout(searchLayout) ;
	
	QObject::connect(gMediaMusic,SIGNAL(toggled(bool)),this,SLOT(activateMusicSearch(bool))) ;
	QObject::connect(gMediaImage,SIGNAL(toggled(bool)),this,SLOT(activateImageSearch(bool))) ;
	QObject::connect(gMediaText,SIGNAL(toggled(bool)),this,SLOT(activateTextSearch(bool))) ;
}

void QalfSearchWidget::activateMusicSearch(bool enabled) {
	gMusicSearchTab->setEnabled(enabled) ;
	if(enabled) gTabMediaSearch->setCurrentWidget(gMusicSearchTab) ;
}

void QalfSearchWidget::activateImageSearch(bool enabled) {
	gImageSearchTab->setEnabled(enabled) ;
	if(enabled) gTabMediaSearch->setCurrentWidget(gImageSearchTab) ;
}

void QalfSearchWidget::activateTextSearch(bool enabled) {
	gTextSearchTab->setEnabled(enabled) ;
	if(enabled) gTabMediaSearch->setCurrentWidget(gTextSearchTab) ;
}
