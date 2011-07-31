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
 *   along with DataSetEditor.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef SPRITEWIDGET_H
#define SPRITEWIDGET_H

#include <QtGui>
#include <QtCore>
#include <QtXml>
#include <cmath>
#include "cssspriteelementdescription.h"
#include "cssspriteelementimage.h"
#include "cssspriteelementimagelist.h"

class SpriteWidget : public QWidget {
    Q_OBJECT

public:
    enum Layout {
        LAYOUT_BESTFILESIZE,
        LAYOUT_BESTFIT,
        LAYOUT_HORIZONTAL,
        LAYOUT_VERTICAL,
        LAYOUT_BLOCK
    };

    enum Repeat {
        REPEAT_NO_REPEAT,
        REPEAT_REPEAT_X,
        REPEAT_REPEAT_Y
    };

    enum Format {
        FORMAT_RGBA32,
        FORMAT_RGBA24,
        FORMAT_RGBA16,
        FORMAT_INDEXED8
    };

    static QList< CssSpriteElementImage > * updateCssSprite (
        QList< CssSpriteElementImage > * images,
        int xMargin = 8,
        int yMargin = 8,
        SpriteWidget::Layout layout = SpriteWidget::LAYOUT_VERTICAL
    );

    static QImage createCssSprite (
        QList< CssSpriteElementImage > * images,
        int xMargin = 8,
        int yMargin = 8,
        SpriteWidget::Layout layout = SpriteWidget::LAYOUT_VERTICAL,
        SpriteWidget::Format format = SpriteWidget::FORMAT_RGBA32
    );

    static bool exportToFile (
        QString fileName,
        QList< CssSpriteElementImage > * images,
        int xMargin = 8,
        int yMargin = 8,
        SpriteWidget::Layout layout = SpriteWidget::LAYOUT_VERTICAL,
        SpriteWidget::Format format = SpriteWidget::FORMAT_RGBA32
    ) ;

    static CssSpriteElementImageList * importFromFile (
        QString fileName
    ) ;

private:
    SpriteWidget (
        QList< CssSpriteElementImage > * images,
        int xMargin,
        int yMargin,
        SpriteWidget::Layout layout,
        QWidget* parent = 0,
        Qt::WFlags fl = 0
    );
    static SpriteWidget::Layout bestfit (
        QList< CssSpriteElementImage > * images,
        int xMargin = 8,
        int yMargin = 8
    );
    static SpriteWidget::Layout bestFileSize (
        QList< CssSpriteElementImage > * images,
        int xMargin = 8,
        int yMargin = 8
    );
    static QPair< QSize, QSize > extremeSizes (
        QList< CssSpriteElementImage > * images
    );
    QSize _spriteSize();
    void _init();
    void _calcImage();
    QPixmap _spriteImage;
    QList< CssSpriteElementImage > * _images;
    int _elementXMargin;
    int _elementYMargin;
    SpriteWidget::Layout _layout;

private slots:
    void paintEvent ( QPaintEvent * e );
};

#endif
