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

#include "qalfmoderatorwidget.h"
#include "qalfconfig.h"
#include "qalfcrypto.h"
#include <QFileDialog>
#include "qalftorrentmaker.h"
#include "qalfnetwork.h"

QalfModeratorWidget::QalfModeratorWidget(QWidget * parent) : QWidget(parent) {
	vlayout = new QVBoxLayout(this) ;

	noKeySetLabel = new QLabel(tr("The moderator preferences have not been completely set. Please go to \"Configuration->Moderator preferences\" menu (or press Ctrl+L) to generate and export a key.")) ;
	noKeySetLabel->setWordWrap(true) ;
	vlayout->addWidget(noKeySetLabel) ;

	// file path
	fileLabel = new QLabel(tr("File :")) ;
	fileValue = new QLineEdit(QString("/home/alf/226.png")) ;
	openFileButton = new QPushButton(QIcon(":/icons/folder_open.png"),QString()) ;
	connect(openFileButton,SIGNAL(clicked()),this,SLOT(openFile())) ;
	fileLayout = new QHBoxLayout() ;
	fileLayout->addWidget(fileLabel) ;
	fileLayout->addWidget(fileValue) ;
	fileLayout->addWidget(openFileButton) ;

	vlayout->addLayout(fileLayout) ;

	// general informations
	QGroupBox * infoBox = new QGroupBox(tr("Informations about file")) ;
	QGridLayout *  infoLayout = new QGridLayout() ;
	titleLabel = new QLabel(tr("title :")) ;
	titleValue = new QLineEdit() ;
	authorsLabel = new QLabel(tr("authors :")) ;
	authorsValue = new QLineEdit() ;
	licenseLabel = new QLabel(tr("license :")) ;
	licenseValue = new QComboBox() ;
	keywordsLabel = new QLabel(tr("keywords :")) ;
	keywordsValue = new QLineEdit() ;
	infoLayout->addWidget(titleLabel,0,0) ;
	infoLayout->addWidget(titleValue,0,1) ;
	infoLayout->addWidget(authorsLabel,1,0) ;
	infoLayout->addWidget(authorsValue,1,1) ;
	infoLayout->addWidget(licenseLabel,0,3) ;
	infoLayout->addWidget(licenseValue,0,4) ;
	infoLayout->addWidget(keywordsLabel,1,3) ;
	infoLayout->addWidget(keywordsValue,1,4) ;
	infoLayout->setColumnMinimumWidth(2,25) ;
	infoLayout->setRowStretch(2,1) ;
	infoLayout->setColumnStretch(0,0) ;
	infoLayout->setColumnStretch(1,2) ;
	infoLayout->setColumnStretch(2,0) ;
	infoLayout->setColumnStretch(3,0) ;
	infoLayout->setColumnStretch(4,1) ;
	infoBox->setLayout(infoLayout);
	vlayout->addWidget(infoBox) ;

	// medium specific
	QGroupBox * mediumBox = new QGroupBox(tr("Informations specific to medium")) ;
	QVBoxLayout * mediumLayout = new QVBoxLayout() ;
	
	mediumInfo = new QStackedWidget() ;
	mediumInfo->addWidget(new QalfImageInfoWidget()) ;
	mediumLayout->addWidget(mediumInfo) ;

	mediumBox->setLayout(mediumLayout) ;
	
	vlayout->addWidget(mediumBox) ;

	vlayout->addStretch(1) ;

	QSize iconSize(22,22) ;
	sendButton = new QPushButton(tr("Send torrent")) ;
	sendButton->setIcon(QIcon(":/icons/vcs_add.png")) ;
	sendButton->setIconSize(iconSize) ;
	connect(sendButton,SIGNAL(clicked()),this,SLOT(sendTorrent())) ;
	buttonLayout = new QHBoxLayout() ;
	buttonLayout->addStretch() ;
	buttonLayout->addWidget(sendButton) ;
	vlayout->addLayout(buttonLayout) ;
	setLayout(vlayout) ;
	checkKey() ;
}

void QalfModeratorWidget::checkKey() {
	QalfConfig *configObject = QalfConfig::getConfigObject() ;
	QString keyProperty("moderatorKey") ;
	if(configObject->getProperty(keyProperty) == "") {
		noKeySetLabel->setVisible(true) ;
		fileLabel->setVisible(false) ;
		fileValue->setVisible(false) ;
		openFileButton->setVisible(false) ;
	} else {
		noKeySetLabel->setVisible(false) ;
		fileLabel->setVisible(true) ;
		fileValue->setVisible(true) ;
		openFileButton->setVisible(true) ;
	}
}

void QalfModeratorWidget::openFile() {
	QString path = QFileDialog::getOpenFileName(this,"Choose a file","/home","Images (*.png)");
	fileValue->setText(path) ;
}

void QalfModeratorWidget::sendTorrent() {
	QString filepath = fileValue->text() ;
	if(filepath == "") {
		QMessageBox::warning(this,tr("File missing !"), tr("Please choose a file to send")) ;
	} else {
		QString title = titleValue->text() ;
		if(title == "") {
			QMessageBox::warning(this,tr("Title missing !"), tr("Please fill the title field")) ;
		} else {
			QString license = licenseValue->currentText() ;
			if(license == "") {
				QMessageBox::warning(this,tr("License missing !"), tr("Please choose a license")) ;
			} else {
				QString tracker("http://127.0.0.1") ;
			
				QalfConfig * config = QalfConfig::getConfigObject() ;
				QString torrentDirProp("torrentDir") ;
				QFileInfo fileInfo(filepath) ;
				QString torrentFilename = config->getProperty(torrentDirProp)+QString(QDir::separator())+fileInfo.fileName()+".torrent" ;
			
				QalfTorrentMaker torrentMaker ;
				QString hash = torrentMaker.createTorrent(filepath,torrentFilename,tracker) ;
				QFile filename(torrentFilename) ;
				QFileInfo info(filename) ;
				filename.rename(info.absolutePath()+QString(QDir::separator())+hash+".torrent") ;
				QString keyProp("moderatorKey") ;
				QalfCrypto crypto ;
				QString key = config->getProperty(keyProp) ;
				QString signature = crypto.sign(hash,key) ;
				if(signature != "") {
					QalfNetwork network ;
		// 			network.sendTorrent(hash,signature,
				}
			}
		}
	}
}