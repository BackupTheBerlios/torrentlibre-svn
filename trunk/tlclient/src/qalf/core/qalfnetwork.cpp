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
#include <QTcpSocket>
// #include <QtTest>

QalfNetwork::QalfNetwork() {

}

QalfNetwork::~QalfNetwork() {

}

bool QalfNetwork::sendKey(QString &username, QString &email, QString &publicKey) {
	QByteArray packet ;
	packet += username ;
	packet += "," ;
	packet += email ;
	packet += "," ;
	packet += publicKey ;
	return sendPacket(packet) ;
}

bool QalfNetwork::sendTorrent(QString &torrent,QString &signature, QString &title, QStringList &authors, QString &licence, QStringList &keywords, QString &category) {
	return false ;
}

bool QalfNetwork::sendPacket(QByteArray &packet) {
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
	
	QDataStream in(&block,QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_4_0);
	quint16 size ;
	QByteArray message ;
// 	in.device()->seek(0);
	in >> size ;
	in >> message ;
	qDebug() << "size" << size ;
	qDebug() << "message : " << QString(message) ;
	if(socket.waitForConnected(10000))
	qint64 read = socket.write(block);
	while(socket.bytesToWrite()) {
		qDebug() << "BytesToWrite" ;
		socket.waitForBytesWritten(1000) ;
	}
// 	else
// 		return false ;
	qDebug() << "read : " << read ;
// 	socket.disconnectFromHost();
	return true ;
}
