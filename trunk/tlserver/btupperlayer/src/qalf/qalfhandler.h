/*******************************************************
** Copyright (C) 2006 Francois Gaudin.
**
** BtUpperLayer is free software; you can redistribute
** it and/or modify it under the terms of the GNU
** Library General Public License as published by the
** Free Software Foundation; either version 2, or (at
** your option) any later version.
**
********************************************************/

#ifndef QalfHANDLER_H
#define QalfHANDLER_H

#include <QtDebug>
#include <QObject>

#define NO_ERROR         0
#define USERNOTTRUSTED   1
#define BADSIGNATURE     2
#define CANNOTSTORETORRENT 3

class QalfHandler : public QObject {
	Q_OBJECT

	public:
		enum KeyStatus {
			KeyUnknown,
			KeyUntrusted,
			KeyTrusted
		};
		
		QalfHandler() ;
		bool recordKey(QString& name, QString& email, QString& key) ;
		KeyStatus keyStatus(QString& email) ;
		QList<QString> getLicenses() ;
		int storeTorrent(QString &moderatorEmail, QString &signature, QString &title, QString &authors, QString &license, QString &keywords, QString &category, QByteArray &torrentData) ;
};

#endif // QalfHANDLER_H
