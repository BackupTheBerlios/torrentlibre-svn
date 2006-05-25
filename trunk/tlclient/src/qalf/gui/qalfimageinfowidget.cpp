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

#include "qalfimageinfowidget.h"

QalfImageInfoWidget::QalfImageInfoWidget(QWidget * parent) : QWidget(parent) {
	layout = new QGridLayout() ;
	categoryLabel = new QLabel(tr("category :")) ;
	categoryValue = new QComboBox() ;
	categoryValue->setEditable(true) ;
	layout->addWidget(categoryLabel,0,0) ;
	layout->addWidget(categoryValue,0,1) ;
	layout->setColumnStretch(0,0) ;
	layout->setColumnStretch(1,1) ;
	layout->setColumnStretch(2,2) ;
	setLayout(layout) ;
}

