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

#include "qalfmoderatorwidget.h"
#include "qalfconfig.h"

QalfModeratorWidget::QalfModeratorWidget(QWidget * parent) : QWidget(parent) {
	QalfConfig *configObject = QalfConfig::getConfigObject() ;
	QString keyProperty("moderatorKey") ;
	
	vlayout = new QVBoxLayout(this) ;

	if(configObject->getProperty(keyProperty) == "") {
		noKeySetLabel = new QLabel(tr("The moderator preferences have not been completely set. Please go to \"Configuration->Moderator preferences\" menu (or press Ctrl+L) to generate and export a key.")) ;
		noKeySetLabel->setWordWrap(true) ;
		vlayout->addWidget(noKeySetLabel) ;
	}

	setLayout(vlayout) ;
}
