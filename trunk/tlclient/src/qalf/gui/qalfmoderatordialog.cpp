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

#include "qalfmoderatordialog.h"
#include "qalfconfig.h"
#include "qalfcrypto.h"
#include "qalfpassworddialog.h"
#include "qalfnetwork.h"
#include <QMessageBox>

QalfModeratorDialog::QalfModeratorDialog(QWidget * parent) : QDialog(parent),generateKeyButton(0) {
	QalfConfig * configObject = QalfConfig::getConfigObject() ;
	QString keyProperty("moderatorKey") ;
	QString key = configObject->getProperty(keyProperty) ;

	setMinimumSize(QSize(300,150)) ;
	setWindowTitle(tr("Moderator configuration")) ;
	usernameLabel = new QLabel(tr("Name : ")) ;
	QString usernameProperty("username") ;
	usernameValue = new QLineEdit(configObject->getProperty(usernameProperty)) ;

	emailLabel = new QLabel(tr("Email : ")) ;
	QString emailProperty("email") ;
	emailValue = new QLineEdit(configObject->getProperty(emailProperty)) ;

	keyLabel = new QLabel(tr("Key : ")) ;
	keyValue = new QLabel(key) ;
	keyStatusLabel = new QLabel(tr("Key status : ")) ;
	keyStatusValue = new QLabel() ;
	infoLayout = new QGridLayout() ;
	infoLayout->addWidget(usernameLabel,0,0,1,1,Qt::AlignRight) ;
	infoLayout->addWidget(usernameValue,0,1) ;
	infoLayout->addWidget(emailLabel,1,0,1,1,Qt::AlignRight) ;
	infoLayout->addWidget(emailValue,1,1) ;
	infoLayout->addWidget(keyLabel,2,0,1,1,Qt::AlignRight) ;
	infoLayout->addWidget(keyValue,2,1) ;
	infoLayout->addWidget(keyStatusLabel,3,0,1,1,Qt::AlignRight) ;
	infoLayout->addWidget(keyStatusValue,3,1) ;

	vlayout = new QVBoxLayout(this) ;
	vlayout->addLayout(infoLayout) ;
	generateKeyButton = new QPushButton(tr("Generate keys")) ;
	connect(generateKeyButton,SIGNAL(clicked()),this,SLOT(savePref())) ;
	connect(generateKeyButton,SIGNAL(clicked()),this,SLOT(generateKeys())) ;
	vlayout->addWidget(generateKeyButton) ;

	exportKeyButton = new QPushButton(tr("Send key to server")) ;
	connect(exportKeyButton,SIGNAL(clicked()),this,SLOT(sendKey())) ;
	vlayout->addWidget(exportKeyButton) ;
	deleteKeyButton = new QPushButton(tr("Delete key")) ;
	vlayout->addWidget(deleteKeyButton) ;
	vlayout->addStretch() ;

	okButton = new QPushButton(tr("Ok")) ;
	okButton->setAutoDefault(true) ;
	connect(okButton,SIGNAL(clicked()),this,SLOT(savePref())) ;
	connect(okButton,SIGNAL(clicked()),this,SLOT(accept())) ;
	cancelButton = new QPushButton(tr("Cancel")) ;
	connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject())) ;
	buttonLayout = new QHBoxLayout() ;
	buttonLayout->addStretch() ;
	buttonLayout->addWidget(okButton) ;
	buttonLayout->addWidget(cancelButton) ;
	vlayout->addLayout(buttonLayout) ;
	setLayout(vlayout) ;

// 	switchTo() ;
}

void QalfModeratorDialog::generateKeys() {
	QalfConfig * configObject = QalfConfig::getConfigObject() ;

	QString username = usernameValue->text() ;
	if(username == "") {
		QMessageBox::warning(this,tr("Name missing !"), tr("Please fill the name field")) ;
	} else {
		QString email = emailValue->text() ;
		if(email == "") {
			QMessageBox::warning(this,tr("Email missing !"), tr("Please fill the email field")) ;
		} else {
			QString label(tr("Please enter a password :"));
			QalfPasswordDialog passwordBox(label,this) ;
			int result = passwordBox.exec() ;
			if(result == QDialog::Accepted) {
				QString password = passwordBox.getPassword() ;
				QalfCrypto crypto ;
				QString key = crypto.generateKeyPair(username,email,password) ;
				QString keyProperty("moderatorKey") ;
				configObject->setProperty(keyProperty,key) ;
				configObject->save() ;
				keyValue->setText(key) ;
				switchTo() ;
			}
		}
	}
	
}

void QalfModeratorDialog::sendKey() {
	QalfConfig * config = QalfConfig::getConfigObject() ;

	QString username = usernameValue->text() ;
	QString email = emailValue->text() ;
	QString keyProp("moderatorKey") ;
	QString key = config->getProperty(keyProp) ;
	QalfCrypto crypto ;
	QString pubKey = crypto.getPublicKey(key) ;
	QalfNetwork client ;
	bool sent = client.sendKey(username,email,pubKey) ;
	switchTo() ;
}

void QalfModeratorDialog::savePref() {
	QalfConfig * configObject = QalfConfig::getConfigObject() ;
	QString username = usernameValue->text() ;
	QString usernameKey("username") ;
	configObject->setProperty(usernameKey,username) ;
	QString email = emailValue->text() ;
	QString emailKey("email") ;
	configObject->setProperty(emailKey,email) ;
	configObject->save() ;
}

void QalfModeratorDialog::switchTo() {
	QalfConfig * configObject = QalfConfig::getConfigObject() ;
	QString keyProperty("moderatorKey") ;
	QString emailProperty("email") ;
	QString key = configObject->getProperty(keyProperty) ;
	QString email = configObject->getProperty(emailProperty) ;

	if(key == "") {
		switchToGenerateKey() ;
	} else {
		QalfNetwork client ;
		QalfNetwork::ResultCode keyStatus = client.checkKeyStatus(email,key) ;
		switch(keyStatus) {
			case QalfNetwork::KeyUntrusted:
				emit keyUntrusted() ;
				qDebug() << "emit keyUntrusted" ;
				switchToReExportKey() ;
				break ;
			case QalfNetwork::KeyTrusted:
				emit keyTrusted() ;
				qDebug() << "emit keyTrusted" ;
				switchToDeleteKey() ;
				break ;
			case QalfNetwork::KeyUnknown:
			default:
				qDebug() << "emit keyUnknown" ;
				emit keyUnknown() ;
				switchToExportKey() ;
				break ;
		}
	}
}

void QalfModeratorDialog::switchToGenerateKey() {
	usernameValue->setReadOnly(false) ;
	usernameValue->setEnabled(true) ;
	emailValue->setReadOnly(false) ;
	emailValue->setEnabled(true) ;
	keyLabel->setVisible(false) ;
	keyValue->setVisible(false) ;
	keyStatusLabel->setVisible(false) ;
	keyStatusValue->setVisible(false) ;
	generateKeyButton->setVisible(true) ;
	exportKeyButton->setVisible(false) ;
	deleteKeyButton->setVisible(false) ;
}

void QalfModeratorDialog::switchToExportKey() {
	usernameValue->setReadOnly(true) ;
	usernameValue->setEnabled(false) ;
	emailValue->setReadOnly(true) ;
	emailValue->setEnabled(false) ;
	keyLabel->setVisible(true) ;
	keyValue->setVisible(true) ;
	keyStatusLabel->setVisible(true) ;
	keyStatusValue->setVisible(true) ;
	generateKeyButton->setVisible(false) ;
	exportKeyButton->setText("Export key") ;
	exportKeyButton->setVisible(true) ;
	deleteKeyButton->setVisible(false) ;
	QPalette palette = keyStatusValue->palette() ;
	palette.setColor(QPalette::WindowText,Qt::red) ;
	keyStatusValue->setPalette(palette) ;
	keyStatusValue->setText(tr("Key not exported")) ;
}

void QalfModeratorDialog::switchToReExportKey() {
	usernameValue->setReadOnly(true) ;
	usernameValue->setEnabled(false) ;
	emailValue->setReadOnly(true) ;
	emailValue->setEnabled(false) ;
	keyLabel->setVisible(true) ;
	keyValue->setVisible(true) ;
	keyStatusLabel->setVisible(true) ;
	keyStatusValue->setVisible(true) ;
	generateKeyButton->setVisible(false) ;
	exportKeyButton->setText("Reexport key") ;
	exportKeyButton->setVisible(true) ;
	deleteKeyButton->setVisible(false) ;
	QPalette palette = keyStatusValue->palette() ;
	palette.setColor(QPalette::WindowText,Qt::red) ;
	keyStatusValue->setPalette(palette) ;
	keyStatusValue->setText(tr("Key not trusted")) ;
}

void QalfModeratorDialog::switchToDeleteKey() {
	usernameValue->setReadOnly(true) ;
	usernameValue->setEnabled(false) ;
	emailValue->setReadOnly(true) ;
	emailValue->setEnabled(false) ;
	keyLabel->setVisible(true) ;
	keyValue->setVisible(true) ;
	keyStatusLabel->setVisible(true) ;
	keyStatusValue->setVisible(true) ;
	generateKeyButton->setVisible(false) ;
	exportKeyButton->setVisible(false) ;
	deleteKeyButton->setVisible(true) ;
	QPalette palette = keyStatusValue->palette() ;
	palette.setColor(QPalette::WindowText,Qt::green) ;
	keyStatusValue->setPalette(palette) ;
	keyStatusValue->setText(tr("Key trusted")) ;
}
