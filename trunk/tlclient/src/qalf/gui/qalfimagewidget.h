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

#ifndef QalfIMAGEWIDGET_H
#define QalfIMAGEHWIDGET_H

#include <QtGui>

class QalfImageWidget : public QWidget {
	Q_OBJECT
	
	public:
		QalfImageWidget(QWidget * parent = 0) ;
	
	public slots:
		void setImage(const QString & imagePath) ;
		void fit() ;
		void originalSize() ;
		void zoom() ;
		void unzoom() ;
	
	private:
		void doZoom(float ratio) ;
	
		QScrollArea * gImageDisplay ;
		QWidget * gImageControls ;
		QLabel * gImageContainer ;
		
		QPushButton * gViewFit ;
		QPushButton * gViewOriginal ;
		QPushButton * gViewZoom ;
		QPushButton * gViewUnzoom ;
		
		QString imagePath ;
};

#endif // QalfIMAGEWIDGET_H
