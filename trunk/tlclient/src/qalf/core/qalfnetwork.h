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
#include <QTcpSocket>

#define SENDKEY          1
#define KEYSTATUS        2

#define RESULTCODE       100

class QalfNetwork : public QObject {
	Q_OBJECT

	public:
		enum ResultCode {
				KeyUnknown = 101,
				KeyUntrusted = 102,
				KeyTrusted = 103
		};
	
		QalfNetwork() ;
		~QalfNetwork() ;
		bool sendKey(QString &username, QString &email, QString &publicKey) ;
		bool sendTorrent(QString &torrent,QString &signature, QString &title, QStringList &authors, QString &licence, QStringList &keywords, QString &category) ;
		ResultCode checkKeyStatus(QString& email, QString &key) ;
// 		bool checkKeyKnown(QString& email, QString &key) ;
// 		bool checkKeyAuthorization(QString& email, QString &key) ;

	signals:
		void error(QTcpSocket::SocketError socketError);
		void keyUnknown() ;
		void keyUntrusted() ;
		void keyTrusted() ;

	protected:
		QByteArray sendPacket(QByteArray &packet) ;
		QByteArray readPacket(QTcpSocket &socket) ;
};

#endif // QalfNETWORK_H
