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

QalfServer::QalfServer(QObject * parent) : QTcpServer(parent) {

}

QalfServer::~QalfServer() {

}

void QalfServer::incomingConnection(int socketDescriptor) {
	QalfServerThread *thread = new QalfServerThread(socketDescriptor, this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}
