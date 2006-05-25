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

#ifndef QalfMODERATORWIDGET_H
#define QalfMODERATORWIDGET_H

#include <QtGui>
#include "qalfimageinfowidget.h"

class QalfModeratorWidget : public QWidget {
	Q_OBJECT
	
	public:
		QalfModeratorWidget(QWidget * parent = 0) ;
	
	public slots:
		void checkKey() ;

	protected slots:
		void openFile() ;
		void sendTorrent() ;

	protected:
		QLabel * noKeySetLabel ;
		QLabel * fileLabel ;
		QLineEdit * fileValue ;
		QPushButton * openFileButton ;
		QHBoxLayout * fileLayout ;
		
		QLabel * titleLabel ;
		QLineEdit * titleValue ;
		QLabel * authorsLabel ;
		QLineEdit * authorsValue ;
		QLabel * licenseLabel ;
		QComboBox * licenseValue ;
		QLabel * keywordsLabel ;
		QLineEdit * keywordsValue ;

		QStackedWidget * mediumInfo ;
		
		QPushButton * sendButton ;

		QHBoxLayout * buttonLayout ;
		QVBoxLayout * vlayout ;
};

#endif // QalfMODERATORWIDGET_H
