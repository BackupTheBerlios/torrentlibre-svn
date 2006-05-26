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

int main(int argc, char *argv[])
{
	QalfServer server ;
	server.listen() ;
	qDebug() << "port:" << server.serverPort() ;
	
	int i = 0 ;
	while(i < 10) {
		server.waitForNewConnection(30000) ;
		++i ;
	}
}
