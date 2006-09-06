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

// bool QalfCrypto::checkKeyAuthorization(QString &key) {
// 	return false ;
// }

QString QalfCrypto::getPublicKey(QString &key) {
	
	// exporting public key
	gpgme_data_t keyData ;
	gpgme_error_t result = gpgme_data_new(&keyData);
	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;

	result = gpgme_op_export(context,key.toLocal8Bit(),0,keyData) ;
	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;
	
	QString publicKeyStr ;
	char  * buffer = (char *) calloc(4096,sizeof(char)) ;
// 	gpgme_data_rewind(keyData) ;
	gpgme_data_seek(keyData,0,SEEK_SET) ;
	gpgme_data_read(keyData,buffer,4096) ;

	publicKeyStr += buffer ;
	return publicKeyStr ;
}

QString QalfCrypto::sign(QString &message, QString &key) {
	gpgme_key_t gpgkey ;
	gpgme_data_t signature ;
	gpgme_data_t msg ;
	gpgme_verify_result_t verification ;
	gpgme_signature_t signatures ;
 	gpgme_error_t result  ;
	char  * buffer ;
		
	gpgme_set_passphrase_cb(context,&passphrase_callback,NULL) ;
	result = gpgme_set_protocol(context,GPGME_PROTOCOL_OpenPGP) ;
	Q_ASSERT(gpgme_err_code(result) == GPG_ERR_NO_ERROR) ;
	gpgme_set_armor(context,1) ;
	gpgme_set_textmode(context,1) ;

	gpgme_signers_clear(context) ;
	result = gpgme_set_keylist_mode(context,GPGME_KEYLIST_MODE_LOCAL) ;

	// retrieving key
	result = gpgme_get_key(context, key.toAscii().data(),&gpgkey,1) ;
	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;
	Q_ASSERT(gpgkey != 0) ;

	// signing
	result = gpgme_signers_add(context,gpgkey) ;
	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;
	
	result = gpgme_data_new(&signature);
	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;

	int message_length = message.toAscii().size() ;
	char * message_char = (char *) calloc(message_length+1,sizeof(char)) ;
	memcpy(message_char,message.toAscii().data(),message_length) ;
// 	printf("memcmp : %d\n",memcmp(message_char,"1fc36e1d41a93c1d79f6872198f426129320d287",message_length+1)) ;
	result = gpgme_data_new_from_mem(&msg,message_char,message_length,0) ;
	
	gpgme_data_seek(signature,0,SEEK_SET) ;
	gpgme_data_seek(msg,0,SEEK_SET) ;
	
	result = gpgme_op_sign(context, msg,signature, GPGME_SIG_MODE_DETACH) ;
	Q_ASSERT(gpgme_err_code(result) == GPG_ERR_NO_ERROR || gpgme_err_code(result) == GPG_ERR_BAD_PASSPHRASE || gpgme_err_code(result) == GPG_ERR_CANCELED) ;
	
// 	gpgme_data_seek(signature,0,SEEK_SET) ;
// 	gpgme_data_seek(msg,0,SEEK_SET) ;
// 	
// 	result = gpgme_op_verify (context, signature, msg , 0) ;
// 	Q_ASSERT(gpgme_err_code(result) != GPG_ERR_INV_VALUE) ;
// 	Q_ASSERT(gpgme_err_code(result) != GPG_ERR_NO_DATA) ;
// 	Q_ASSERT(result == GPG_ERR_NO_ERROR) ;
// 	
// 	verification = gpgme_op_verify_result(context) ;
// 	Q_ASSERT(verification != 0) ;
// 	
// 	signatures = verification->signatures ;
// 	Q_ASSERT(verification->signatures != 0) ;
// 	result = signatures->status ;
// 	printf("status : %d\n",gpgme_err_code(result)) ;
// 	printf("signature summary : %d\n",signatures->summary) ;
// 	Q_ASSERT(signatures->summary == GPGME_SIGSUM_VALID | GPGME_SIGSUM_GREEN) ;
// 	
	QString signatureStr ;
	buffer = (char *) calloc(2048,sizeof(char)) ;
	gpgme_data_seek(signature,0,SEEK_SET) ;
	gpgme_data_read(signature,buffer,2048) ;

	signatureStr += buffer ;

	qDebug() << "signature" << signatureStr ;
	
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
			out << password << '\n' ;
			return GPG_ERR_NO_ERROR ;
		}
	}
	return GPG_ERR_CANCELED ;
}
