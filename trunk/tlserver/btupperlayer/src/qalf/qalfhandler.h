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

#ifndef QalfHANDLER_H
#define QalfHANDLER_H

#include <QtDebug>
#include <QObject>

class QalfHandler : public QObject {
	Q_OBJECT

	public:
		enum KeyStatus {
			KeyUnknown,
			KeyUntrusted,
			KeyTrusted
		};
		
		QalfHandler() ;
		bool recordKey(QString& name, QString& email, QString& key) ;
		KeyStatus keyStatus(QString& email) ;
};

#endif // QalfHANDLER_H
