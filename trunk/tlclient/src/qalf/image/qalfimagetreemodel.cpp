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

#include "qalfimagetreemodel.h"
#include "treeitem.h"
#include <QIcon>

QalfImageTreeModel::QalfImageTreeModel(QalfDb * database) : QalfTreeModel(database) {

}

void QalfImageTreeModel::loadData() {

	// loading data from database
	QString media = "image" ;
	QList<QHash<QString,QString> *> * resultList = this->db->selectAllByMedia(media) ;
	
	QList<QHash<QString,QString> *>::iterator row ;
	QHash<QString,TreeItem*> parents;
	QStringList categories ;
	
	for(row = resultList->begin();row != resultList->end();++row) {
		QalfImageFile * image = new QalfImageFile((**row)["hash"],(**row)["torrent"]) ;
		image->setTitle((**row)["title"]) ;
		image->setFormat((**row)["format"]) ;
		image->setCategory((**row)["category"]) ;
		image->setFilePath((**row)["path"]) ;
		image->setLicense((**row)["license"]) ;
		image->setUsed((**row)["used"].toInt()) ;
		
		QString category = image->getCategory() ;
		if(!categories.contains(category)) {
			categories << category ;
			QList<QVariant> newCat ;
			newCat << category ;
			TreeItem * newCatItem = new TreeItem(newCat, this->rootItem) ;
			parents[category] = newCatItem ;
			this->rootItem->appendChild(newCatItem);
		}
		
		QList<QVariant> newImage ;
		newImage << QVariant::fromValue(image) ;
		TreeItem * newItem = new TreeItem(newImage, parents[category]) ;
		parents[category]->appendChild(newItem);
	}
}

QVariant QalfImageTreeModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid())
		return QVariant();
	if(role == Qt::DisplayRole) {
		TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
		QVariant data = item->data(index.column());
		qDebug() << "item->data(index.column())" ;
		qDebug() << data.typeName() ;
		if(QString(data.typeName()) == "QString") {
			// it's a category
			qDebug() << data.toString() ;
			return data ;
		} else {
			// it's an image
			return QVariant(data.value<QalfImageFile *>()->getTitle()) ;
		}
	} else if(role == Qt::DecorationRole) {
		TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
		QVariant data = item->data(index.column());
		if(QString(data.typeName()) == "QString") {
			// it's a category
			return QIcon(":/icons/imagegallery.png") ;
		} else {
			// it's an image
			return QIcon(":/icons/imagegallery.png") ;
		}
	} else {
		return QVariant();
	}
}
