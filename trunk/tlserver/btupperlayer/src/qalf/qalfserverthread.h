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

#ifndef QalfSERVERTHREAD_H
#define QalfSERVERTHREAD_H

#include <QtNetwork>
#include <QThread>
#include <QTcpSocket>
#include <QtDebug>

#define SENDKEY 1
#define KEYSTATUS 2

#define RESULTCODE       100
#define KEYUNKNOWN       101
#define KEYUNTRUSTED     102
#define KEYTRUSTED       103

class QalfServerThread : public QThread {
	Q_OBJECT

	public:
		QalfServerThread(int socketDescriptor, QObject * parent = 0) ;
		void run();

	signals:
		void error(QTcpSocket::SocketError socketError);

	protected:
		int socketDescriptor;
		QByteArray getPacket(QTcpSocket &socket) ;
		QByteArray parse(QByteArray &packet) ;
		bool sendPacket(QTcpSocket &socket, QByteArray &packet) ;
};

#endif // QalfSERVERTHREAD_H
