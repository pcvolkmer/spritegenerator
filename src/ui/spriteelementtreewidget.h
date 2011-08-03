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

#ifndef SPRITEELEMENTTREEWIDGET_H
#define SPRITEELEMENTTREEWIDGET_H

#include <QtGui>
#include <QtCore>
#include "cssspriteelementimage.h"
#include "cssspriteelementimagelist.h"

/**
 * @brief The class SpriteElementTreeWidget extends a QTreeWidget to perform special operation on a CssSpriteElementImageList.
 **/
class SpriteElementTreeWidget : public QTreeWidget {
    Q_OBJECT

public:
    SpriteElementTreeWidget ( QWidget * parent = 0 );
    ~SpriteElementTreeWidget();
    /**
     * @brief Updates the tree widget with image list.
     *
     * @param images List of images to be shown in tree widget.
     **/
    void update ( CssSpriteElementImageList * images );
    /**
     * @brief Selects filename related to item
     *
     * @param item QTreeWidgetItem to fetch filename from
     * @return Fetched file name from item
     **/
    QString fileName ( QTreeWidgetItem * item );

private:
    CssSpriteElementImageList * _images;
    void dropEvent ( QDropEvent * event );
    void updateItem(CssSpriteElementImage image, QTreeWidgetItem * item);

signals:
    /**
     * @brief This signal is sent if an item was moved in tree widget.
     **/
    void itemMoved();
    /**
     * @brief This signal is sent if an error occured during moving an image.
     **/
    void itemMoveError();
};

#endif
