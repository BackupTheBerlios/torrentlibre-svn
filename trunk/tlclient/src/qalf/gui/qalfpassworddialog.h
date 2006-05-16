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

#ifndef QalfPASSWORDDIALOG_H
#define QalfPASSWORDDIALOG_H

#include <QtGui>

class QalfPasswordDialog : public QDialog {
	Q_OBJECT
	
	public:
		QalfPasswordDialog(QString &label, QWidget * parent = 0) ;
		QString getPassword() const ;
	
	protected:
		QLabel * passwordLabel ;
		QLineEdit * passwordValue ;
		QPushButton * okButton ;
		QPushButton * cancelButton ;
		QHBoxLayout * buttonLayout ;
		QVBoxLayout * vlayout ;
};

#endif // QalfPASSWORDDIALOG_H
