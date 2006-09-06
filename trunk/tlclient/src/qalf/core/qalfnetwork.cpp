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
#include "qalfconfig.h"
// #include <QtTest>

QalfNetwork::QalfNetwork() : QObject() {

}

QalfNetwork::~QalfNetwork() {

}

void QalfNetwork::errorHandler(QAbstractSocket::SocketError error) {
	throw QalfNetworkException(error,socket.errorString()) ;
// 	qDebug() << error << socket.errorString() ;
}

void QalfNetwork::sendKey(QString &username, QString &email, QString &publicKey) {
	QByteArray packet ;
	quint16 command(SENDKEY) ;
	QDataStream out(&packet,QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << command ;
	out << username ;
	out << email ;
	out << publicKey ;
	try {
		QByteArray answer = sendPacket(packet) ;
	}
	catch(...) {
		throw ;
	}
}

void QalfNetwork::sendTorrent(QString &moderatorEmail, QString &torrent,QString &signature, QString &title, QString &authors, QString &license, QString &keywords, QString &category) {
	qDebug() << "sendTorrent" ;
	QByteArray packet ;
	quint16 command(SENDTORRENT) ;
	QDataStream out(&packet,QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << command ;
	out << moderatorEmail ;
	out << signature ;
	out << title ;
	out << authors ;
	out << license ;
	out << keywords ;
	out << category ;
	QalfConfig * config = QalfConfig::getConfigObject() ;
	QString torrentDirProp("torrentDir") ;
	QString torrentDir = config->getProperty(torrentDirProp) ;
	QFile file(torrentDir+QDir::separator()+torrent+".torrent");
	qDebug() << "opening" << torrentDir+QDir::separator()+torrent+".torrent" ;
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "can't open file" ;
		return;
	}
	
	QByteArray torrentData = file.readAll();
	out << torrentData ;
	try {
		QByteArray answer = sendPacket(packet) ;
	}
	catch(...) {
		throw ;
	}
}

QList<QString> QalfNetwork::getLicenses() {
	qDebug() << "getLicenses" ;
	QByteArray packet ;
	quint16 command(GETLICENSES) ;
	QDataStream out(&packet,QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << command ;
	QList<QString> licenses ;
	try {
		QByteArray answer = sendPacket(packet) ;
		QDataStream in(&answer,QIODevice::ReadOnly);
		in.setVersion(QDataStream::Qt_4_0);
		in >> command ;
		QString license ;
		while(!in.atEnd()) {
			in >> license ;
			licenses << license ;
		}
	}
	catch(...) {
		throw ;
	}
	return licenses ;
}

QalfNetwork::ResultCode QalfNetwork::checkKeyStatus(QString& email, QString &key) {
	qDebug() << "check key status" ;
	QByteArray packet ;
	quint16 command(KEYSTATUS) ;
	QDataStream out(&packet,QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << command ;
	out << email ;
	int result ;
	try {
		QByteArray answer = sendPacket(packet) ;
		QDataStream in(&answer,QIODevice::ReadOnly);
		in.setVersion(QDataStream::Qt_4_0);
		in >> command ;
		
		if(command != RESULTCODE) {
			result = KeyUnknown ;
		} else {
			in >> result ;
			qDebug() << result ;
		}
	}
	catch(...) {
		throw ;
	}
	return ResultCode(result) ;
}

QByteArray QalfNetwork::sendPacket(QByteArray &packet) {
	QString serverName("127.0.0.1") ;
	quint16 serverPort = 7200;
	qDebug() << "sendPacket" ;
	
	connect(&socket,SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorHandler(QAbstractSocket::SocketError))) ;
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
	QByteArray answer = readPacket() ;
	int command ;
	QDataStream in(&answer,QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_4_0);
	in >> command ;
	if(command == UNKNOWNCOMMAND) {
		throw QalfNetworkException(UNKNOWNCOMMAND,tr("Unknown server command")) ;
	}
// 	parse(answer) ;
	socket.disconnectFromHost();
	return answer ;
}

QByteArray QalfNetwork::readPacket() {
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
