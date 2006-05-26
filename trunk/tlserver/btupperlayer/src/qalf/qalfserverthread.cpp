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

#include "qalfserverthread.h"

QalfServerThread::QalfServerThread(int socketDescriptor, QObject * parent) : QThread(parent), socketDescriptor(socketDescriptor) {

}

void QalfServerThread::run() {
	QTcpSocket tcpSocket;
	if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
			emit error(tcpSocket.error());
			return;
	}

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << (quint16)0;
	out << "Hello";
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	tcpSocket.write(block);
	
	qDebug() << "incoming connection" ;

	tcpSocket.disconnectFromHost();
	tcpSocket.waitForDisconnected();
}
