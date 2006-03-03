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

#ifndef QalfCONFIG_H
#define QalfCONFIG_H
#include <QFileInfo>
#include <QDir>

#define TLVERSION 0.1

#ifdef Q_WS_X11
#define TL_DIR ".torrentlibre"
#endif

#ifdef Q_WS_WIN
#define TL_DIR "torrentlibre"
#endif

#ifdef Q_WS_X11
#define TL_DIR ".torrentlibre"
#endif

#define DBFILE "tl.db"

class QalfConfig : public QObject {
	Q_OBJECT
	
	public:
		QalfConfig() ;
		~QalfConfig() ;
		QString getConfigDir() const ;
		QString getDbFile() const ;
		
	protected:
		QString configDir ;
		QString dbFile ;
	
};

#endif // QalfCONFIG_H
