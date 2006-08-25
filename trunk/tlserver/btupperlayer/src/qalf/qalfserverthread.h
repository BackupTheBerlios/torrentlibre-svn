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

class QalfServerThread : public QThread {
	Q_OBJECT

	public:
		QalfServerThread(int socketDescriptor, QObject * parent = 0) ;
		void run();

	signals:
		void error(QTcpSocket::SocketError socketError);

	protected:
		int socketDescriptor;
		QString getPacket(QTcpSocket &socket) ;
		void parse(QString &packet) ;
};

#endif // QalfSERVERTHREAD_H