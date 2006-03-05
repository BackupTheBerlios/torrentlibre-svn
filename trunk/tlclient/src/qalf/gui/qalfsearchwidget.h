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

#ifndef QalfSEARCHWIDGET_H
#define QalfSEARCHWIDGET_H

#include <QtGui>

class QalfSearchWidget : public QWidget {
	Q_OBJECT
	
	public:
		QalfSearchWidget(QWidget * parent = 0) ;
	
	public slots:
		void activateMusicSearch(bool enabled) ;
		void activateImageSearch(bool enabled) ;
		void activateTextSearch(bool enabled) ;
	
	private:
		QWidget * gSearchBar ;
		QTableView * gSearchResults ;
		QWidget * gSearchControls ;
		QLabel * gSearchLabel ;
		QLabel * gSearchOnLabel ;
		QLabel * gMediaLabel ;
		QLabel * gAuthorLabel ;
		QLabel * gLicenseLabel ;
		
		QLineEdit * gSearchEdit ;
		QRadioButton * gOnComputerButton ;
		QRadioButton * gOnTLButton ;
		QCheckBox * gMediaMusic ;
		QCheckBox * gMediaImage ;
		QCheckBox * gMediaText ;
		QLineEdit * gAuthorEdit ;
		QCheckBox * gLicenseBy ;
		QCheckBox * gLicenseShare ;
		QCheckBox * gLicenseDerivs ;
		QCheckBox * gLicenseCommercial ;
		QCheckBox * gLicenseShareAlike ;
		
		QTabWidget * gTabMediaSearch ;
		QWidget * gMusicSearchTab ;
		QLabel * gMusicTitleLabel ;
		QLabel * gMusicBandLabel ;
		QLabel * gMusicAlbumLabel ;
		QLabel * gMusicStyleLabel ;
		QLineEdit * gMusicTitleEdit ;
		QLineEdit * gMusicBandEdit ;
		QLineEdit * gMusicAlbumEdit ;
		QComboBox * gMusicStyleEdit ;
		
		QWidget * gImageSearchTab ;
		QLabel * gImageTitleLabel ;
		QLabel * gImageSizeLabel ;
		QLabel * gImageFormatLabel ;
		QLabel * gImageCategoryLabel ;
		QLineEdit * gImageTitleEdit ;
		QSpinBox * gImageWidthEdit ;
		QSpinBox * gImageHeightEdit ;
		QLineEdit * gImageFormatEdit ;
		QComboBox * gImageCategoryEdit ;
		
		QWidget * gTextSearchTab ;
		QLabel * gTextTitleLabel ;
		QLabel * gTextCategoryLabel ;
		QLabel * gTextStyleLabel ;
		QLabel * gTextPagesLabel ;
		QLineEdit * gTextTitleEdit ;
		QComboBox * gTextCategoryEdit ;
		QComboBox * gTextStyleEdit ;
		QSpinBox * gTextPagesEdit ;
		
		
		QPushButton * gDownloadSelection ;
		QPushButton * gDownloadAll ;
};

#endif // QalfSEARCHWIDGET_H
