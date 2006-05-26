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

#include "qalfcrypto.h"
#include <QtDebug>
#include "qalfpassworddialog.h"

QalfCrypto::QalfCrypto() {
	gpgme_error_t result = gpgme_new(&context) ;
	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;
	result = gpgme_set_protocol(context,GPGME_PROTOCOL_OpenPGP) ;
	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;
	gpgme_set_armor(context,1) ;
	gpgme_set_textmode(context,1) ;
}

QalfCrypto::~QalfCrypto() {
	gpgme_release(context) ;
}

QString QalfCrypto::generateKeyPair(QString &username, QString &email,QString &passphrase) {
	gpgme_error_t result = gpgme_op_genkey(context,getKeyParams(username,email,passphrase).toUtf8(),NULL,NULL) ;
	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;
	gpgme_genkey_result_t keys = gpgme_op_genkey_result(context) ;
	return QString(keys->fpr) ;
}

bool QalfCrypto::checkKeyAuthorization(QString &key) {
	return false ;
}

QString QalfCrypto::sign(QString &message, QString &key) {
	gpgme_set_passphrase_cb(context,&passphrase_callback,NULL) ;
	gpgme_signers_clear(context) ;

	// retrieving key
	gpgme_key_t gpgkey ;
	gpgme_error_t result = gpgme_get_key(context, key.toLocal8Bit(),&gpgkey,true) ;
	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;
	Q_ASSERT(gpgkey != NULL) ;

	// signing
	result = gpgme_signers_add(context,gpgkey) ;
	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;
	gpgme_data_t signature ;
	result = gpgme_data_new(&signature);
	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;

	gpgme_data_t msg ;
	result = gpgme_data_new_from_mem(&msg,message.toLocal8Bit(),message.size(),0) ;
	
	
	result = gpgme_op_sign(context, msg,signature, GPGME_SIG_MODE_DETACH) ;
	Q_ASSERT(result == GPG_ERR_NO_ERROR || result == GPG_ERR_BAD_PASSPHRASE || result == GPG_ERR_CANCELED) ;

	QString signatureStr ;
	char  * buffer = (char *) calloc(1024,sizeof(char)) ;
	gpgme_data_rewind(signature) ;
// should be the following, but for a fucking mysterious reason, it doesn't want to work
// 	gpgme_data_seek(signature,0,SEEK_SET) ;
	gpgme_data_read(signature,buffer,1024) ;

	signatureStr += buffer ;

	gpgme_data_release(signature) ;
	gpgme_key_unref(gpgkey) ;
	gpgme_data_release(msg) ;
	return signatureStr ;
}

QString QalfCrypto::getKeyParams(QString &username, QString &email,QString &passphrase) {
	QString param = QString("<GnupgKeyParms format=\"internal\">\n"
								"Key-Type: DSA\n"
								"Key-Length: 1024\n"
								"Subkey-Type: ELG-E\n"
								"Subkey-Length: 1024\n"
								"Name-Real: %1\n"
								"Name-Comment: generated by torrentlibre\n"
								"Name-Email: %2\n"
								"Expire-Date: 0\n"
								"Passphrase: %3\n"
								"</GnupgKeyParms>").arg(username).arg(email).arg(passphrase) ;
	return param ;
}

gpgme_error_t passphrase_callback(void *hook, const char *uid_int, const char *passphrase_info, int prev_was_bad, int fd) {
	QString label(QObject::tr("Please enter your password :"));
	QalfPasswordDialog passwordBox(label) ;
	int result = passwordBox.exec() ;
	if(result == QDialog::Accepted) {
		QString password = passwordBox.getPassword() ;
		QFile file ;
		if(file.open(fd,QIODevice::WriteOnly | QIODevice::Text)) {
			QTextStream out(&file) ;
			out << password << "\n" ;
			return GPG_ERR_NO_ERROR ;
		}
	}
	return GPG_ERR_CANCELED ;
}
