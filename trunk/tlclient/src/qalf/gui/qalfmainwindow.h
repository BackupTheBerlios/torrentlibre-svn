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

#ifndef QalfMAINWINDOW_H
#define QalfMAINWINDOW_H

#include <QtGui>
#include "qalfsearchwidget.h"
#include "qalfimagewidget.h"
#include "qalfimagetreemodel.h"

class QalfMainWindow : public QMainWindow {
	Q_OBJECT
	
	public:
		QalfMainWindow() ;
		void setImageModel(QalfImageTreeModel * imageTreeModel) ;
	
	signals:
		void imageChanged(const QString & imagePath) ;
	
	private slots:
		void showModeratorDialog() ;
		void openImage(const QModelIndex & index) ;
		void saveModeratorMode() ;
		void aboutTl() ;

	private:
		void createMenu() ;

	private:
		QToolBox * gLibrary ;
		QTabWidget * gTabActions ;
		QalfSearchWidget * gSearchTab ;
		QalfImageWidget * gImageTab ;
		
		QTreeView * gMusicTree ;
		QTreeView * gImageTree ;
		QTreeView * gTextTree ;

		QMenu * appMenu ;
		QAction * quitAction ;

		QMenu * configMenu ;
		QAction * prefAction ;
		QAction * moderatorModeAction ;
		QAction * moderatorDialogAction ;

		QMenu *helpMenu ;
		QAction *aboutTlAction ;
		QAction *aboutQtAction ;
};

#endif // QalfMAINWINDOW_H
