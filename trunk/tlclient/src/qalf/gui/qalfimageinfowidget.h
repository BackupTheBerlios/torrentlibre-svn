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

#ifndef QalfIMAGEINFOWIDGET_H
#define QalfIMAGEINFOWIDGET_H

#include <QtGui>

class QalfImageInfoWidget : public QWidget {
	Q_OBJECT
	
	public:
		QalfImageInfoWidget(QWidget * parent = 0) ;
	
	private:
		QLabel * categoryLabel ;
		QComboBox * categoryValue ;
		
		QGridLayout * layout ;
};

#endif // QalfIMAGEINFOWIDGET_H
