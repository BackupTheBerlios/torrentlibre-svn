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

	noKeySetLabel = new QLabel() ;
	noKeySetLabel->setWordWrap(true) ;
	vlayout->addWidget(noKeySetLabel) ;

	// file path
	fileLabel = new QLabel(tr("File :")) ;
	fileValue = new QLineEdit(QString("/home/alf/alf.png")) ;
	openFileButton = new QPushButton(QIcon(":/icons/folder_open.png"),QString()) ;
	connect(openFileButton,SIGNAL(clicked()),this,SLOT(openFile())) ;
	fileLayout = new QHBoxLayout() ;
	fileLayout->addWidget(fileLabel) ;
	fileLayout->addWidget(fileValue) ;
	fileLayout->addWidget(openFileButton) ;

	vlayout->addLayout(fileLayout) ;

	// general informations
	infoBox = new QGroupBox(tr("Informations about file")) ;
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
	mediumBox = new QGroupBox(tr("Informations specific to medium")) ;
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
	switchToNokey() ;
	checkKey() ;
}

void QalfModeratorWidget::checkKey() {
	qDebug() << "checkKey" ;
	QalfConfig *configObject = QalfConfig::getConfigObject() ;
	QString keyProperty("moderatorKey") ;
	QString key = configObject->getProperty(keyProperty) ;
	if(key == "") {
		switchToNokey() ;
	} else {
		QString emailProperty("email") ;
		QString email = configObject->getProperty(emailProperty) ;
		QalfNetwork client ;
		try {
			QalfNetwork::ResultCode keyStatus = client.checkKeyStatus(email,key) ;
		
			// key not sent
			if(keyStatus == QalfNetwork::KeyUnknown) {
				switchToKeyUnknown() ;
			} else {
				// key not trusted
				if(keyStatus == QalfNetwork::KeyUntrusted) {
					switchToKeyUntrusted() ;
				} else {
					switchToKeyTrusted() ;
				}
			}
		} catch(QalfNetworkException &exception) {
			QMessageBox::critical(this, tr("Server error"), tr("Error %1 : ").arg(exception.code())+exception.message(), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton) ;
		}
	}
}

void QalfModeratorWidget::switchToNokey() {
	noKeySetLabel->setText(tr("You have not yet generated a moderator key. Please go to \"Configuration->Moderator preferences\" menu (or press Ctrl+L) to generate and export a key.")) ;
	noKeySetLabel->setVisible(true) ;
	fileLabel->setVisible(false) ;
	fileValue->setVisible(false) ;
	openFileButton->setVisible(false) ;
	infoBox->setVisible(false) ;
	mediumBox->setVisible(false) ;
}

void QalfModeratorWidget::switchToKeyUnknown() {
	qDebug() << "slot keyUnknown" ;
	noKeySetLabel->setText(tr("You have not yet exported your moderator key. Please go to \"Configuration->Moderator preferences\" menu (or press Ctrl+L) to export your key.")) ;
	noKeySetLabel->setVisible(true) ;
	fileLabel->setVisible(false) ;
	fileValue->setVisible(false) ;
	openFileButton->setVisible(false) ;
	infoBox->setVisible(false) ;
	mediumBox->setVisible(false) ;
}

void QalfModeratorWidget::switchToKeyUntrusted() {
	qDebug() << "slot keyUntrusted" ;
	noKeySetLabel->setText(tr("Your moderator key has not yet been approved by the server. Please wait until a server owner validate it.")) ;
	noKeySetLabel->setVisible(true) ;
	fileLabel->setVisible(false) ;
	fileValue->setVisible(false) ;
	openFileButton->setVisible(false) ;
	infoBox->setVisible(false) ;
	mediumBox->setVisible(false) ;
}

void QalfModeratorWidget::switchToKeyTrusted() {
	qDebug() << "slot keyTrusted" ;
	noKeySetLabel->setVisible(false) ;
	fileLabel->setVisible(true) ;
	fileValue->setVisible(true) ;
	openFileButton->setVisible(true) ;
	infoBox->setVisible(true) ;
	mediumBox->setVisible(true) ;
	QList<QString> licenses ;
	QalfNetwork client ;
	try {
		licenses = client.getLicenses() ;
	} catch(QalfNetworkException &exception) {
		QMessageBox::critical(this, tr("Server error"), tr("Error %1 : ").arg(exception.code())+exception.message(), QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton) ;
	}
	licenseValue->clear() ;
	licenseValue->addItem("") ;
	QString license ;
	foreach(license,licenses) {
		licenseValue->addItem(license) ;
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
				QString newPath(info.absolutePath()+QString(QDir::separator())+hash+".torrent") ;
				if(QFile::exists(newPath)) {
					QFile::remove(newPath) ;
				}
				filename.rename(newPath) ;
				QString keyProp("moderatorKey") ;
				QalfCrypto crypto ;
				QString key = config->getProperty(keyProp) ;
				QString signature = crypto.sign(hash,key) ;
				if(signature != "") {
					QString emailProp("email") ;
					QString email = config->getProperty(emailProp) ;
					QString authors = authorsValue->text() ;
					QString keywords = keywordsValue->text() ;
					QString category("concert") ;
					QalfNetwork client ;
					client.sendTorrent(email,hash,signature, title, authors, license, keywords, category) ;
				}
			}
		}
	}
}
