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
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "signal.h"

QalfServer server ;

void daemonize() {
	int pid ;
	int i ;
	int fd ;
	char str[12] ;

	pid = fork() ;
	if(pid < 0) {
		perror("Fork failed") ;
	}
	if(pid > 0) {
		exit(EXIT_SUCCESS) ;
	}
	setsid() ;

	pid = fork() ;
	if(pid < 0) {
		perror("Fork failed") ;
	}
	if(pid > 0) {
		exit(EXIT_SUCCESS) ;
	}

	for(i = getdtablesize();i>=0;--i)
		close(i) ;

	i = open("/dev/null", O_RDWR) ;
	dup(i) ;
	dup(i) ;

	umask(022) ;
	chdir("/tmp") ;

	fd = open("/tmp/btupperlayer.lock",O_RDWR | O_CREAT, 0640) ;
	if(fd < 0)
		exit(EXIT_FAILURE) ;
	if(lockf(fd,F_TLOCK,0) < 0)
		exit(EXIT_SUCCESS) ;
	snprintf(str,12,"%d\n",getpid()) ;
	write(fd,str,strlen(str)) ;
}

void sigterm_handler(int i) {
	server.close() ;
}

int main(int argc, char *argv[])
{
// 	daemonize() ;
	int port = 7200 ;
	signal(SIGTERM,sigterm_handler) ;
	server.listen(QHostAddress::Any,port) ;
	while(server.isListening()) {
		qDebug() << "waitForNewConnection()" ;
		server.waitForNewConnection(10000) ;
	}
}
