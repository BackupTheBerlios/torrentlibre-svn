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

#include "qalfimagewidget.h"

QalfImageWidget::QalfImageWidget(QWidget * parent) : QWidget(parent) {
	gImageDisplay = new QScrollArea() ;
	gImageDisplay->setWidgetResizable(true) ;
	gImageContainer = new QLabel() ;
	gImageContainer->setMargin(0) ;
	gImageContainer->setBackgroundRole(QPalette::Dark) ;
	gImageContainer->setAlignment(Qt::AlignCenter) ;
	gImageDisplay->setBackgroundRole(QPalette::Dark);
	gImageDisplay->setWidget(gImageContainer);
	
	gImageControls = new QWidget() ;
	
	QSize iconSize = QSize(22,22) ;
	
	gViewFit = new QPushButton(QIcon(":/icons/viewmagfit.png"),tr("Fit to window")) ;
	gViewFit->setIconSize(iconSize) ;
	gViewOriginal = new QPushButton(QIcon(":/icons/viewmag1.png"),tr("Original size")) ;
	gViewOriginal->setIconSize(iconSize) ;
	gViewZoom = new QPushButton(QIcon(":/icons/viewmag+.png"),tr("Zoom")) ;
	gViewZoom->setIconSize(iconSize) ;
	gViewUnzoom = new QPushButton(QIcon(":/icons/viewmag-.png"),tr("Unzoom")) ;
	gViewUnzoom->setIconSize(iconSize) ;
	
	connect(gViewFit,SIGNAL(clicked()),this,SLOT(fit())) ;
	connect(gViewOriginal,SIGNAL(clicked()),this,SLOT(originalSize())) ;
	connect(gViewZoom,SIGNAL(clicked()),this,SLOT(zoom())) ;
	connect(gViewUnzoom,SIGNAL(clicked()),this,SLOT(unzoom())) ;
	
	QHBoxLayout * controlsLayout = new QHBoxLayout() ;
	controlsLayout->setMargin(0) ;
	controlsLayout->setSpacing(2) ;
	controlsLayout->addWidget(gViewFit) ;
	controlsLayout->addWidget(gViewOriginal) ;
	controlsLayout->addWidget(gViewZoom) ;
	controlsLayout->addWidget(gViewUnzoom) ;
	controlsLayout->addStretch() ;
	gImageControls->setLayout(controlsLayout) ;
	
	QVBoxLayout * layout = new QVBoxLayout() ;
	layout->addWidget(gImageDisplay,1) ;
	layout->addWidget(gImageControls) ;
	this->setLayout(layout) ;
}

void QalfImageWidget::setImage(const QString & imagePath) {
	qDebug() << "setImage called : " << imagePath ;
	this->imagePath = imagePath ;
// 	QPixmap newImage(imagePath) ;
// 	gImageContainer->setPixmap(newImage);
	fit() ;
}

void QalfImageWidget::fit() {
// 	const QPixmap * image = gImageContainer->pixmap() ;
	QPixmap image = QPixmap(this->imagePath) ;
	int width = gImageDisplay->size().width() ;
	int height = gImageDisplay->size().height() ;
	qDebug() << "viewport : " << width << "x" << height ;
	int imageWidth = image.size().width() ;
	int imageHeight = image.size().height() ;
	qDebug() << "image size : " << imageWidth << "x" << imageHeight ;
	float widthRatio ;
	float heightRatio ;
	QPixmap newImage ;
	
	if(imageWidth > width || imageHeight > height) {
		widthRatio = static_cast<float>(imageWidth)/static_cast<float>(width) ;
		heightRatio = static_cast<float>(imageHeight)/static_cast<float>(height) ;
		qDebug() << "ratio : " << widthRatio << "x" << heightRatio ;
		
		// I don't like these 4 pixels I need to remove to fit in viewport. I didn't find where they come from
		if(widthRatio > heightRatio) {
			newImage = image.scaledToWidth(width-4) ;
		} else {
			newImage = image.scaledToHeight(height-4) ;
		}
		
		QSize newSize(newImage.size()) ;
		gImageContainer->setPixmap(newImage);
		gImageContainer->resize(newSize) ;
	}
}

void QalfImageWidget::originalSize() {
// 	const QPixmap * image = gImageContainer->pixmap() ;
	QPixmap image = QPixmap(this->imagePath) ;
	QSize newSize(image.size()) ;
	gImageContainer->setPixmap(image);
	gImageContainer->resize(newSize) ;
}

void QalfImageWidget::doZoom(float ratio) {
	const QPixmap * image = gImageContainer->pixmap() ;
	QPixmap newImage = QPixmap(this->imagePath) ;
	int imageWidth = image->size().width() ;
	float newWidth = imageWidth*ratio ;
	
	newImage = newImage.scaledToWidth(static_cast<int>(newWidth)) ;
		
	QSize newSize(newImage.size()) ;
	gImageContainer->setPixmap(newImage);
	gImageContainer->resize(newSize) ;
}

void QalfImageWidget::zoom() {
	this->doZoom(1.2) ;
}

void QalfImageWidget::unzoom() {
	this->doZoom(0.8) ;
}
