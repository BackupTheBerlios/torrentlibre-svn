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

QalfModeratorDialog::QalfModeratorDialog(QWidget * parent) : QDialog(parent) {
	usernameLabel = new QLabel(tr("Username : ")) ;
	usernameValue = new QLineEdit() ;
	usernameLayout = new QHBoxLayout() ;
	usernameLayout->addWidget(usernameLabel) ;
	usernameLayout->addWidget(usernameValue) ;
	
	okButton = new QPushButton(tr("Ok")) ;
	connect(okButton,SIGNAL(clicked()),this,SLOT(savePref())) ;
	cancelButton = new QPushButton(tr("Cancel")) ;
	connect(cancelButton,SIGNAL(clicked()),this,SLOT(close())) ;
	buttonLayout = new QHBoxLayout() ;
	buttonLayout->addStretch() ;
	buttonLayout->addWidget(okButton) ;
	buttonLayout->addWidget(cancelButton) ;
	
	vlayout = new QVBoxLayout(this) ;
	vlayout->addLayout(usernameLayout) ;
	vlayout->addStretch() ;
	vlayout->addLayout(buttonLayout) ;
	setLayout(vlayout) ;
}

void QalfModeratorDialog::savePref() {
	QalfConfig * configObject = QalfConfig::getConfigObject() ;
	QString username = usernameValue->text() ;
	QString usernameKey("username") ;
	configObject->setProperty(usernameKey,username) ;
	configObject->save() ;
	qDebug() << "saved" ;
}
