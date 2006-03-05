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

#ifndef QalfTREEMODEL_H
#define QalfTREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "qalfdb.h"

class TreeItem;

class QalfTreeModel : public QAbstractItemModel {

	Q_OBJECT

	public:
		QalfTreeModel(QalfDb * database, QObject *parent = 0);
		~QalfTreeModel();

		QVariant data(const QModelIndex &index, int role) const;
		Qt::ItemFlags flags(const QModelIndex &index) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		virtual void loadData() = 0;
		
	protected:
		void setupModelData(const QStringList &lines, TreeItem *parent);
		
		QalfDb * db ;
		TreeItem *rootItem;
};

#endif // TREEMODEL_H
