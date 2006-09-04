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
		void sendKey(QString &username, QString &email, QString &publicKey) ;
		void sendTorrent(QString &torrent,QString &signature, QString &title, QStringList &authors, QString &licence, QStringList &keywords, QString &category) ;
		ResultCode checkKeyStatus(QString& email, QString &key) ;
// 		bool checkKeyKnown(QString& email, QString &key) ;
// 		bool checkKeyAuthorization(QString& email, QString &key) ;

	signals:
		void error(QTcpSocket::SocketError socketError);
		void keyUnknown() ;
		void keyUntrusted() ;
		void keyTrusted() ;

	protected slots:
		void errorHandler(QAbstractSocket::SocketError socketError) ;

	protected:
		QByteArray sendPacket(QByteArray &packet) ;
		QByteArray readPacket() ;
		QTcpSocket socket ;
};

class QalfNetworkException {
	public:
		QalfNetworkException(int code ,QString msg) : error_code(code), msg(msg) {} ;
		QalfNetworkException(const QalfNetworkException &exception) : error_code(exception.error_code), msg(exception.msg) {} ;
		
		QString message() {return msg ; }
		int code() {return error_code ; }
		
	protected:
		int error_code ;
		QString msg ;
} ;

#endif // QalfNETWORK_H
