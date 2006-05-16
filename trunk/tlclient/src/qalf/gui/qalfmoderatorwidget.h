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

class QalfModeratorWidget : public QWidget {
	Q_OBJECT
	
	public:
		QalfModeratorWidget(QWidget * parent = 0) ;
	
	protected:
		QLabel * noKeySetLabel ;
		
		QVBoxLayout * vlayout ;
};

#endif // QalfMODERATORWIDGET_H
