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

#include "qalfserver.h"
#include "qalfserverthread.h"

QalfServer::QalfServer(QObject * parent, int port) : QTcpServer(parent), port(port) {
	this->listen(QHostAddress::Any,port) ;
}

QalfServer::~QalfServer() {

}

// void QalfServer::run() {
// 	listen(QHostAddress::Any,port) ;
// 	while(isListening()) {
// 		qDebug() << "waitForNewConnection()" ;
// 		waitForNewConnection(10000) ;
// 	}
// }

void QalfServer::incomingConnection(int socketDescriptor) {
	qDebug() << "incomingConnection" ;
	QalfServerThread *thread = new QalfServerThread(socketDescriptor, dynamic_cast<QThread*>(this));
	QThread::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}
