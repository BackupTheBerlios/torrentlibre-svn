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
#include <QMessageBox>

QalfModeratorDialog::QalfModeratorDialog(QWidget * parent) : QDialog(parent),generateKeyButton(0) {
	QalfConfig * configObject = QalfConfig::getConfigObject() ;
	QString keyProperty("moderatorKey") ;
	QString key = configObject->getProperty(keyProperty) ;

	setMinimumSize(QSize(300,100)) ;
	setWindowTitle(tr("Moderator configuration")) ;
	usernameLabel = new QLabel(tr("Username : ")) ;
	QString usernameProperty("username") ;
	usernameValue = new QLineEdit(configObject->getProperty(usernameProperty)) ;
	if(key != "") {
		usernameValue->setReadOnly(true) ;
		usernameValue->setEnabled(false) ;
	}
	emailLabel = new QLabel(tr("Email : ")) ;
	QString emailProperty("email") ;
	emailValue = new QLineEdit(configObject->getProperty(emailProperty)) ;
	if(key != "") {
		emailValue->setReadOnly(true) ;
		emailValue->setEnabled(false) ;
		keyLabel = new QLabel(tr("Key : ")) ;
		keyValue = new QLabel(key) ;
		keyStatusLabel = new QLabel(tr("Key status : ")) ;
		keyStatusValue = new QLabel() ;
	}
	infoLayout = new QGridLayout() ;
	infoLayout->addWidget(usernameLabel,0,0,1,1,Qt::AlignRight) ;
	infoLayout->addWidget(usernameValue,0,1) ;
	infoLayout->addWidget(emailLabel,1,0,1,1,Qt::AlignRight) ;
	infoLayout->addWidget(emailValue,1,1) ;
	if(key != "") {
		infoLayout->addWidget(keyLabel,2,0,1,1,Qt::AlignRight) ;
		infoLayout->addWidget(keyValue,2,1) ;
		infoLayout->addWidget(keyStatusLabel,3,0,1,1,Qt::AlignRight) ;
		infoLayout->addWidget(keyStatusValue,3,1) ;
	}

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
	
	vlayout = new QVBoxLayout(this) ;
	vlayout->addLayout(infoLayout) ;
	if(key == "") {
		generateKeyButton = new QPushButton(tr("Generate keys")) ;
		connect(generateKeyButton,SIGNAL(clicked()),this,SLOT(generateKeys())) ;
		vlayout->addWidget(generateKeyButton) ;
	} else {
		QalfCrypto crypto ;
		if(crypto.checkKeyAuthorization(key)) {
			QPalette palette = keyStatusValue->palette() ;
			palette.setColor(QPalette::WindowText,Qt::green) ;
			keyStatusValue->setPalette(palette) ;
			keyStatusValue->setText(tr("Key accepted")) ;
		} else {
			QPalette palette = keyStatusValue->palette() ;
			palette.setColor(QPalette::WindowText,Qt::red) ;
			keyStatusValue->setPalette(palette) ;
			keyStatusValue->setText(tr("Key not trusted")) ;
			exportKeyButton = new QPushButton(tr("Send key to server")) ;
			vlayout->addWidget(exportKeyButton) ;
		}
	}
	vlayout->addStretch() ;
	vlayout->addLayout(buttonLayout) ;
	setLayout(vlayout) ;
}

void QalfModeratorDialog::generateKeys() {
	QalfConfig * configObject = QalfConfig::getConfigObject() ;

	QString username = usernameValue->text() ;
	if(username == "") {
		QMessageBox::warning(this,tr("Username missing !"), tr("Please fill the username field")) ;
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
				vlayout->removeWidget(generateKeyButton) ;
			}
		}
	}
	
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
