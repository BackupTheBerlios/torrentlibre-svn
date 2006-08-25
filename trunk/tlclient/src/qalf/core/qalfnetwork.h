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

#ifndef QalfNETWORK_H
#define QalfNETWORK_H

#include <QStringList>

class QalfNetwork : public QObject {
	Q_OBJECT

	public:
		QalfNetwork() ;
		~QalfNetwork() ;
		bool sendKey(QString &username, QString &email, QString &publicKey) ;
		bool sendTorrent(QString &torrent,QString &signature, QString &title, QStringList &authors, QString &licence, QStringList &keywords, QString &category) ;

	protected:
		bool sendPacket(QByteArray &packet) ;
};

#endif // QalfNETWORK_H
