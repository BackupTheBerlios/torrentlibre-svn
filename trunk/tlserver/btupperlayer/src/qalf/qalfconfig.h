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
#include <QReadWriteLock>
#include <QHash>
#include <QtXml>

#define TLVERSION 0.1
#define TL_DIR "tlserver"
#define TORRENT_DIR "torrent"

#ifdef Q_WS_X11
#define TL_CONF_DIR ".btupperlayer"
#endif

#ifdef Q_WS_WIN
#define TL_CONF_DIR "btupperlayer"
#endif

#ifdef Q_WS_X11
#define TL_CONF_DIR ".btupperlayer"
#endif

#define DB_FILE "tl.db"
#define CONF_FILE "tl.conf"

class QalfConfig : public QObject {
	Q_OBJECT
	
	public:
		static QalfConfig * getConfigObject() ;
		QString getConfigDir() const ;
		QString getDbFile() const ;
		QString getProperty(QString &key) ;
		void setProperty(QString &key, QString &value) ;
		
	public slots:
		void save() ;
		void load() ;

	protected:
		static QalfConfig * configObject ;
		QalfConfig() ;
		~QalfConfig() ;
		QString configDir ;
		QString confFile ;
		QString dbFile ;
		QHash<QString,QString> properties ;
		QReadWriteLock lock;
		
		class QalfXmlConfigHandler ;
		friend class QalfXmlConfigHandler ;
		class QalfXmlConfigHandler : public QXmlDefaultHandler {
			public:
				QalfXmlConfigHandler(QalfConfig * configObject) ;
				bool startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts) ;
				bool characters(const QString & ch) ;

			private :
				QalfConfig *configObject ;
				QString currentProp ;
		};
};

#endif // QalfCONFIG_H
