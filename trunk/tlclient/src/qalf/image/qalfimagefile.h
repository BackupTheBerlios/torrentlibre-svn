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

#ifndef QalfIMAGEFILE_H
#define QalfIMAGEFILE_H

#include "qalffile.h"
#include <QSize>

class QalfImageFile : public QalfFile {
	Q_OBJECT
	
	public:
		QalfImageFile() ;
		QalfImageFile(const QString & hash, const QString & torrentPath) ;
		~QalfImageFile() ;
		QalfImageFile(const QalfImageFile& imageFile) ;
		void setTitle(QString & title) ;
		void setSize(QSize & size) ;
		void setFormat(QString & format) ;
		void setCategory(QString & category) ;
		QString getTitle() const ;
		QSize getSize() const ;
		QString getFormat() const ;
		QString getCategory() const ;
		
	protected:
		QString title ;
		QSize size ;
		QString format ;
		QString category ;
};

#endif // QalfIMAGEFILE_H
