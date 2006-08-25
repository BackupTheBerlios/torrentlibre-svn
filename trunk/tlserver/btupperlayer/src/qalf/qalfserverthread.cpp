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

	QString packet = getPacket(tcpSocket) ;
	qDebug() << packet ;
	parse(packet) ;

	tcpSocket.disconnectFromHost();
	tcpSocket.waitForDisconnected();
}

QString QalfServerThread::getPacket(QTcpSocket &socket) {
	qDebug() << socket.peerAddress().toString() ;
	QString packet ;
	QDataStream in(&socket);
	in.setVersion(QDataStream::Qt_4_0);
	quint16 blockSize = 0 ;

	// waiting connection
	qDebug() << "waiting connection" ;
// 	if(!socket.waitForConnected(10000))
// 		return packet ;
	qDebug() << "state" << socket.state() ;
	// reading size of packet
	qDebug() << "reading size of packet" ;
	
	while (socket.bytesAvailable() < (int)sizeof(quint16)) {
		qDebug() << "bytes available" << socket.bytesAvailable() ;
		if (!socket.waitForReadyRead(1000)) {
			emit error(socket.error());
			return packet;
		}
	}
// 	while (socket.bytesAvailable() < (int)sizeof(quint16))
// 		return packet;
	in >> blockSize;
	qDebug() << "blocksize" << blockSize ;

	// looping until buffer is full
	qDebug() << "looping until buffer is full" ;
	while (socket.bytesAvailable() < blockSize) {
		if (!socket.waitForReadyRead(10000)) {
			emit error(socket.error());
			return packet;
		}
	}
	
	// reading the packet
	qDebug() << "reading the packet" ;
	in >> packet ;
	return packet ;
}

void QalfServerThread::parse(QString &packet) {

}
