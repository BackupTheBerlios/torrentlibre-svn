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

#ifndef QalfFILE_H
#define QalfFILE_H

#include <QObject>
#include <QStringList>

class QalfFile : public QObject {
	Q_OBJECT
	
	public:
		QalfFile() ;
		QalfFile(const QString & hash, const QString & torrentPath) ;
		~QalfFile() ;
		void setFilePath(QString & filePath) ;
		void setTorrentPath(QString & torrentPath) ;
		void setAuthors(QStringList & authors) ;
		void setLicense(QString & license) ;
		void setUsed(int used) ;
		QString getHash() const ;
		QString getFilePath() const ;
		QString getTorrentPath() const ;
		QStringList getAuthors() const ;
		QString getLicense() const ;
		int getUsed() const ;
		
	public slots:
		void incrementUsed() ;
		
	protected:
		QString hash ;
		QString filePath ;
		QString torrentPath ;
		QStringList authors ;
		QString license ;
		int used ;
};

#endif // QalfFILE_H
