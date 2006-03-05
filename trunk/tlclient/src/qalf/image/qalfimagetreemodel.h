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

#ifndef QalfIMAGETREEMODEL_H
#define QalfIMAGETREEMODEL_H

#include "qalftreemodel.h"
#include "qalfimagefile.h"
#include <QStringList>

class TreeItem ;

class QalfImageTreeModel : public QalfTreeModel {

	Q_OBJECT

	public:
		QalfImageTreeModel(QalfDb * database) ;
		QVariant data(const QModelIndex &index, int role) const ;
		void loadData() ;
};

Q_DECLARE_METATYPE(QalfImageFile *)

#endif // QalfIMAGETREEMODEL_H
