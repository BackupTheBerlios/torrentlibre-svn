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

class QalfMainWindow : public QMainWindow {
	Q_OBJECT
	
	public:
		QalfMainWindow() ;
	
	private:
		QToolBox * gLibrary ;
		QTabWidget * gTabActions ;
		QalfSearchWidget * searchTab ;
		
		QTreeView * gMusicTree ;
		QTreeView * gImageTree ;
		QTreeView * gTextTree ;
};

#endif // QalfMAINWINDOW_H
