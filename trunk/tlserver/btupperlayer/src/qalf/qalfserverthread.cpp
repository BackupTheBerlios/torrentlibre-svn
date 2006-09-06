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
#include "qalfhandler.h"

QalfServerThread::QalfServerThread(int socketDescriptor, QObject * parent) : QThread(parent), socketDescriptor(socketDescriptor) {

}

void QalfServerThread::run() {
	QTcpSocket tcpSocket;
	if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
			emit error(tcpSocket.error());
			return;
	}

	QByteArray packet = getPacket(tcpSocket) ;
	QByteArray answer = parse(packet) ;
	sendPacket(tcpSocket,answer) ;
	tcpSocket.waitForDisconnected(5000) ;
	tcpSocket.disconnectFromHost();
// 	tcpSocket.waitForDisconnected();
}

QByteArray QalfServerThread::getPacket(QTcpSocket &socket) {
	qDebug() << socket.peerAddress().toString() ;
	QByteArray packet ;
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

QByteArray QalfServerThread::parse(QByteArray &packet) {
	QDataStream in(&packet,QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_4_0);
	quint16 command ;
	in >> command ;
	
	QalfHandler handler ;
	QByteArray answer ;
	QDataStream out(&answer,QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	switch(command) {
		case (quint16)KEYSTATUS: {
			QString email ;
			in >> email ;
			int keyExists = handler.keyStatus(email) ;
			command = RESULTCODE ;
			out << command ;
			switch(keyExists) {
				case QalfHandler::KeyUntrusted:
					out << KEYUNTRUSTED ;
					break ;
				case QalfHandler::KeyTrusted:
					out << KEYTRUSTED ;
					break ;
				default:
				case QalfHandler::KeyUnknown:
					out << KEYUNKNOWN ;
					break ;
			}
			break ;
		}
		case (quint16)SENDKEY: {
			QString name, email, key ;
			in >> name >> email >> key ;
			int recordKey = handler.recordKey(name,email,key) ;
			command = RESULTCODE ;
			out << command ;
			out << recordKey ;
			break ;
		}
		case (quint16)GETLICENSES: {
			out << command ;
			QList<QString> licenses = handler.getLicenses() ;
			QString license ;
			foreach(license, licenses) {
				out << license ;
			}
			break ;
		}
		case (quint16)SENDTORRENT: {
			qDebug() << "sendTorrent" ;
			QString moderatorEmail, signature, title, authors, license, keywords, category ;
			QByteArray torrent ;
			in >> moderatorEmail >> signature >> title >> authors >> license >> keywords >> category >> torrent ;
			int error_code = handler.storeTorrent(moderatorEmail, signature, title, authors, license, keywords, category, torrent) ;
			qDebug() << "error code " << error_code ;
			command = RESULTCODE ;
			out << command ;
			out << error_code ;
			break ;
		}
		default:
			out << UNKNOWNCOMMAND ;
		break ;
	}
	return answer ;
}

bool QalfServerThread::sendPacket(QTcpSocket &socket, QByteArray &packet) {

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
