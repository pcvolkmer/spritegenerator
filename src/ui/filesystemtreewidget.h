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

#ifndef FILESYSTEMTREEWIDGET_H
#define FILESYSTEMTREEWIDGET_H

#include <QtGui>
#include <QtCore>
#include "cssspriteelementimage.h"
#include "cssspriteelementimagelist.h"

class FileSystemTreeWidget : public QTreeWidget {
    Q_OBJECT

public:
    FileSystemTreeWidget ( QWidget * parent = 0 );
    ~FileSystemTreeWidget();
    void update ( CssSpriteElementImageList * images );

private:
    CssSpriteElementImageList * _images;

    void dropEvent ( QDropEvent * event );
    QString fileName ( QTreeWidgetItem * item );

signals:
    void itemMoved();
    void itemMoveError();
};

#endif
