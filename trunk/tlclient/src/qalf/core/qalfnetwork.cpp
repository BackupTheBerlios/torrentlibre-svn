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

#include "qalfnetwork.h"
#include <QtDebug>
#include <QtNetwork>
// #include <QtTest>

QalfNetwork::QalfNetwork() {

}

QalfNetwork::~QalfNetwork() {

}

bool QalfNetwork::sendKey(QString &username, QString &email, QString &publicKey) {
	QByteArray packet ;
	quint16 command(SENDKEY) ;
	QDataStream out(&packet,QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << command ;
	out << username ;
	out << email ;
	out << publicKey ;
	QByteArray answer = sendPacket(packet) ;
	return true ;
}

bool QalfNetwork::sendTorrent(QString &torrent,QString &signature, QString &title, QStringList &authors, QString &licence, QStringList &keywords, QString &category) {
	return false ;
}

QalfNetwork::ResultCode QalfNetwork::checkKeyStatus(QString& email, QString &key) {
	QByteArray packet ;
	quint16 command(KEYSTATUS) ;
	QDataStream out(&packet,QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << command ;
	out << email ;
	QByteArray answer = sendPacket(packet) ;
	QDataStream in(&answer,QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_4_0);
	in >> command ;
	int result ;
	if(command != RESULTCODE) {
		result = KeyUnknown ;
	} else {
		in >> result ;
		qDebug() << result ;
	}
	return ResultCode(result) ;
}

// bool QalfNetwork::checkKeyKnown(QString& email, QString &key) {
// 	QByteArray packet ;
// 	quint16 command(ASKFORKEY) ;
// 	QDataStream out(&packet,QIODevice::WriteOnly);
// 	out.setVersion(QDataStream::Qt_4_0);
// 	out << command ;
// 	out << email ;
// 	QByteArray answer = sendPacket(packet) ;
// 	QDataStream in(&answer,QIODevice::ReadOnly);
// 	in.setVersion(QDataStream::Qt_4_0);
// 	in >> command ;
// 	if(command != RESULTCODE) {
// 		return false ;
// 	} else {
// 		int result ;
// 		in >> result ;
// 		qDebug() << result ;
// 		switch(result) {
// 			case KeyUnknown:
// 				return false ;
// 				break ;
// 			case KeyUntrusted:
// 				return true ;
// 				break ;
// 		}
// 	}
// 	return false ;
// }
// 
// bool QalfNetwork::checkKeyAuthorization(QString& email, QString &key) {
// 	QByteArray packet ;
// 	quint16 command(ISKEYAUTHORIZED) ;
// 	QDataStream out(&packet,QIODevice::WriteOnly);
// 	out.setVersion(QDataStream::Qt_4_0);
// 	out << command ;
// 	out << email ;
// 	QByteArray answer = sendPacket(packet) ;
// 	QDataStream in(&answer,QIODevice::ReadOnly);
// 	in.setVersion(QDataStream::Qt_4_0);
// 	in >> command ;
// 	if(command != RESULTCODE) {
// 		return false ;
// 	} else {
// 		int result ;
// 		in >> result ;
// 		switch(result) {
// 			case KeyUntrusted:
// 				return false ;
// 				break ;
// 			case KeyTrusted:
// 				return true ;
// 				break ;
// 		}
// 	}
// 	return false ;
// }

QByteArray QalfNetwork::sendPacket(QByteArray &packet) {
	QString serverName("127.0.0.1") ;
	quint16 serverPort = 7200;

	QTcpSocket socket;
	socket.connectToHost(serverName, serverPort);

	if (!socket.waitForConnected(10000)) {
		return false ;
	}

	QByteArray block;
	QDataStream out(&block,QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << (quint16)(packet.size());
	out << packet ;
	
	// write data to socket
	if(socket.waitForConnected(10000))
	qint64 read = socket.write(block);
	while(socket.bytesToWrite()) {
		qDebug() << "BytesToWrite" ;
		socket.waitForBytesWritten(1000) ;
	}
	qDebug() << "read : " << read ;
	
	// read answer
	QByteArray answer = readPacket(socket) ;
// 	parse(answer) ;
// 	socket.disconnectFromHost();
	return answer ;
}

QByteArray QalfNetwork::readPacket(QTcpSocket &socket) {
	qDebug() << socket.peerAddress().toString() ;
	QByteArray packet ;
	QDataStream in(&socket);
	in.setVersion(QDataStream::Qt_4_0);
	quint16 blockSize = 0 ;

	while (socket.bytesAvailable() < (int)sizeof(quint16)) {
		qDebug() << "bytes available" << socket.bytesAvailable() ;
		if (!socket.waitForReadyRead(1000)) {
			qDebug() << socket.errorString() ;
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
