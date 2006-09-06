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

#ifndef QalfCRYPTO_H
#define QalfCRYPTO_H

#include <gpgme.h>
#include <QObject>
#include <QStringList>

// gpgme_error_t passphrase_callback(void *hook, const char *uid_int, const char *passphrase_info, int prev_was_bad, int fd) ;

class QalfCrypto : public QObject {
	Q_OBJECT

	public:
		QalfCrypto() ;
		~QalfCrypto() ;
		QString importKey(QString &key) ;
		bool verify(QString &signature, QString &signedMessage, QString &key) ;

	protected:
		gpgme_ctx_t context ;

		QString getKeyParams(QString &username, QString &email,QString &passphrase) ;
};

#endif // QalfCRYPTO_H
