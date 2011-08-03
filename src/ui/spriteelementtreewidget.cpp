/***************************************************************************
 *   Copyright (C) 2011  Paul-Christian Volkmer
 *   paul-christian.volkmer@mni.thm.de
 *
 *   This file is part of SpriteGenerator.
 *
 *   SpriteGenerator is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   SpriteGenerator is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with SpriteGenerator.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "spriteelementtreewidget.h"

SpriteElementTreeWidget::SpriteElementTreeWidget ( QWidget * parent )
        : QTreeWidget ( parent ) {
    this->_images = new CssSpriteElementImageList;
    this->invisibleRootItem()->setFlags ( Qt::NoItemFlags );
}

SpriteElementTreeWidget::~SpriteElementTreeWidget() {}

void SpriteElementTreeWidget::dropEvent ( QDropEvent* event ) {
    if ( this->selectedItems().count() == 1 ) {
        QTreeWidgetItem * item = this->selectedItems().at ( 0 );

        QString oldPath = this->fileName ( item );
        QTreeWidget::dropEvent ( event );
        this->setCurrentItem ( item );

        QString newPath = this->fileName ( item );
        if ( newPath.isEmpty() ) return;

        if (item->childCount() > 0) {
            QListIterator<CssSpriteElementImage> i ( * this->_images );

            while ( i.hasNext() ) {
                CssSpriteElementImage * image = ( CssSpriteElementImage * ) &i.next();
                if (image->fileName().startsWith(oldPath)) {
                    QString newFilePath = image->fileName().replace(oldPath, newPath);
                    image->setFileName(newFilePath);
                    image->setVirtual ( true );
                }
            }
            emit itemMoved();
            return;
        }

        CssSpriteElementImage * image = this->_images->find ( oldPath );

        if ( this->_images->find ( newPath ) ) {
            this->update ( this->_images );
            return;
        }
        image->setFileName ( newPath );
        if ( ! newPath.startsWith ( "/" ) ) image->setVirtual ( true );
        emit itemMoved();
    }
}

QString SpriteElementTreeWidget::fileName ( QTreeWidgetItem* item ) {
    QString fileName;

    QList<QString> pathParts;
    while ( item->parent() ) {
        pathParts.prepend ( item->text ( 0 ) );
        item = item->parent();
    }

    for ( int i=0; i < pathParts.size()-1; i++ ) {
        fileName.append ( pathParts.at ( i ) + "/" );
    }

    if ( pathParts.size() > 0 ) {
        fileName.append ( pathParts.at ( pathParts.size()-1 ) );
    }

    return fileName.replace("//","/");
}

void SpriteElementTreeWidget::update ( CssSpriteElementImageList * images ) {
    this->_images = images;
    this->clear();

    QTreeWidgetItem * topItem = new QTreeWidgetItem();
    QTreeWidgetItem * topVirtualItem = new QTreeWidgetItem();
    QTreeWidgetItem * item = new QTreeWidgetItem();
    QTreeWidgetItem * subItem;

    topItem->setText ( 0,"Filesystem" );
    topItem->setIcon ( 0,QIcon ( ":images/images/16x16/drive-harddisk.png" ) );
    topItem->setFlags ( Qt::ItemIsEnabled );
    topVirtualItem->setText ( 0,"Sprite file" );
    topVirtualItem->setIcon ( 0,QIcon ( ":images/images/16x16/image-stack.png" ) );
    topVirtualItem->setFlags ( Qt::ItemIsDropEnabled|Qt::ItemIsEnabled );
    this->addTopLevelItem ( topVirtualItem );
    this->addTopLevelItem ( topItem );
    foreach ( CssSpriteElementImage image, *this->_images ) {
        QString fileName = image.fileName();
        item = new QTreeWidgetItem();
        QList<QString> pathParts = QDir::fromNativeSeparators ( fileName ).split ( "/" );
        item = ( image.isVirtual() ) ? topVirtualItem : topItem;
        if ( QDir::fromNativeSeparators ( fileName ).startsWith ( "/" ) )
            pathParts.prepend ( "/" );
        foreach ( QString pathPart, pathParts ) {
            if ( pathPart.isEmpty() ) continue;
            for ( int childIndex = 0; childIndex < item->childCount(); childIndex++ ) {
                if ( item->child ( childIndex )->text ( 0 ) == pathPart ) {
                    item = item->child ( childIndex );
                    continue;
                }
            }
            if ( item->text ( 0 ) == pathPart ) continue;
            subItem = new QTreeWidgetItem();
            subItem->setText ( 0, pathPart.isEmpty() ? "/" : pathPart );
            item->addChild ( subItem );
            item = subItem;
            item->setIcon ( 0,QIcon ( ":images/images/16x16/folder-blue.png" ) );
            if ( image.fileState() == CssSpriteElementImage::FILE_VIRTUAL )
                item->setFlags ( Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsEnabled );
            else
                item->setFlags ( Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsEnabled );
        }
        item->setIcon ( 0,QIcon ( ":images/images/16x16/image-x-generic.png" ) );
        item->setFlags ( Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsEnabled );
    }
    this->sortItems ( 0,Qt::AscendingOrder );
    this->expandAll();
}
