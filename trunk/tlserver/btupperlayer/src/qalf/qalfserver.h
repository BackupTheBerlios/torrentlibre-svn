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

#ifndef QalfSERVER_H
#define QalfSERVER_H

#include <QtNetwork>
#include <QTcpServer>
// #include <QThread>

class QalfServer : public QTcpServer {
	Q_OBJECT

	public:
		QalfServer(QObject * parent = 0, int port=7200) ;
		~QalfServer() ;
// 		void run();

	protected:
		int port ;
		void incomingConnection(int socketDescriptor);
};

#endif // QalfSERVER_H
