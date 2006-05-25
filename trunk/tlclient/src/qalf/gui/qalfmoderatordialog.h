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

#ifndef QalfMODERATORDIALOG_H
#define QalfMODERATORDIALOG_H

#include <QtGui>

class QalfModeratorDialog : public QDialog {
	Q_OBJECT
	
	public:
		QalfModeratorDialog(QWidget * parent = 0) ;
	
	protected slots:
		void generateKeys() ;
		void savePref() ;

	signals:
		void keyCreated() ;

	protected:
		QLabel * usernameLabel ;
		QLabel * emailLabel ;
		QLabel * keyLabel ;
		QLabel * keyStatusLabel ;
		QLineEdit * usernameValue ;
		QLineEdit * emailValue ;
		QLabel * keyValue ;
		QLabel * keyStatusValue ;
		QGridLayout * infoLayout ;
		QPushButton * generateKeyButton ;
		QPushButton * exportKeyButton ;
		QPushButton * deleteKeyButton ;
		QPushButton * okButton ;
		QPushButton * cancelButton ;
		QHBoxLayout * buttonLayout ;
		QVBoxLayout * vlayout ;

		void switchTo() ;
		void switchToGenerateKey() ;
		void switchToExportKey() ;
		void switchToDeleteKey() ;
		void switchToNoKey() ;
};

#endif // QalfMODERATORDIALOG_H
