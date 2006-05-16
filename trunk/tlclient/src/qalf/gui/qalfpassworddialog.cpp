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

#include "qalfpassworddialog.h"

QalfPasswordDialog::QalfPasswordDialog(QString &label, QWidget * parent) : QDialog(parent) {
	setWindowTitle(tr("Password")) ;
	passwordLabel = new QLabel(label) ;
	passwordValue = new QLineEdit() ;
	passwordValue->setEchoMode(QLineEdit::Password) ;
	
	okButton = new QPushButton(tr("Ok")) ;
	okButton->setAutoDefault(true) ;
	connect(okButton,SIGNAL(clicked()),this,SLOT(accept())) ;
	cancelButton = new QPushButton(tr("Cancel")) ;
	connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject())) ;
	buttonLayout = new QHBoxLayout() ;
	buttonLayout->addStretch() ;
	buttonLayout->addWidget(okButton) ;
	buttonLayout->addWidget(cancelButton) ;
	
	vlayout = new QVBoxLayout(this) ;
	vlayout->addWidget(passwordLabel) ;
	vlayout->addWidget(passwordValue) ;
	vlayout->addStretch() ;
	vlayout->addLayout(buttonLayout) ;
	setLayout(vlayout) ;
}

QString QalfPasswordDialog::getPassword() const {
	return passwordValue->text() ;
}
