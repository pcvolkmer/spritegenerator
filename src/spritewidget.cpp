/***************************************************************************
 *   Copyright (C) 2010  Paul-Christian Volkmer
 *   paul-christian.volkmer@mni.fh-giessen.de
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

#include "spritewidget.h"

QPixmap SpriteWidget::createCssSprite(
    QList< CssSpriteElementImage > * images,
    int xMargin,
    int yMargin,
    Layout layout
) {
    SpriteWidget swObject(images, xMargin, yMargin, layout);
    return swObject._spriteImage;
}

QList< CssSpriteElementImage > * SpriteWidget::updateCssSprite(
    QList< CssSpriteElementImage > * images,
    int xMargin,
    int yMargin,
    Layout layout
) {
    SpriteWidget swObject(images, xMargin, yMargin, layout);
    return swObject._images;
}

SpriteWidget::Layout SpriteWidget::bestfit(
    QList< CssSpriteElementImage > * images,
    int xMargin,
    int yMargin
) {
    int minSize = 0;
    SpriteWidget swObject(images, xMargin, yMargin, SpriteWidget::LAYOUT_HORIZONTAL);
    int horizontalSize = swObject._spriteSize().height() * swObject._spriteSize().width();
    swObject._layout = SpriteWidget::LAYOUT_VERTICAL;
    int verticalSize = swObject._spriteSize().height() * swObject._spriteSize().width();
    swObject._layout = SpriteWidget::LAYOUT_BLOCK;
    int blockSize = swObject._spriteSize().height() * swObject._spriteSize().width();

    minSize = (horizontalSize < verticalSize) ? horizontalSize : verticalSize;
    minSize = (minSize < blockSize) ? minSize : blockSize;

    if (minSize == horizontalSize) return SpriteWidget::LAYOUT_HORIZONTAL;
    if (minSize == verticalSize) return SpriteWidget::LAYOUT_VERTICAL;
    if (minSize == blockSize) return SpriteWidget::LAYOUT_BLOCK;
}

SpriteWidget::Layout SpriteWidget::bestFileSize(
    QList< CssSpriteElementImage > * images,
    int xMargin,
    int yMargin
) {
    int minSize = 0;
    QBuffer buffer;
    SpriteWidget::createCssSprite(images,xMargin,yMargin,SpriteWidget::LAYOUT_HORIZONTAL).save(&buffer,"PNG");
    int horizontalFileSize = buffer.size();
    buffer.close();
    buffer.setData(NULL);
    SpriteWidget::createCssSprite(images,xMargin,yMargin,SpriteWidget::LAYOUT_VERTICAL).save(&buffer,"PNG");
    int verticalFileSize = buffer.size();
    buffer.close();
    buffer.setData(NULL);
    SpriteWidget::createCssSprite(images,xMargin,yMargin,SpriteWidget::LAYOUT_BLOCK).save(&buffer,"PNG");
    int blockFileSize = buffer.size();
    buffer.close();
    buffer.setData(NULL);

    minSize = (horizontalFileSize < verticalFileSize) ? horizontalFileSize : verticalFileSize;
    minSize = (minSize < blockFileSize) ? minSize : blockFileSize;

    if (minSize == horizontalFileSize) return SpriteWidget::LAYOUT_HORIZONTAL;
    if (minSize == verticalFileSize) return SpriteWidget::LAYOUT_VERTICAL;
    if (minSize == blockFileSize) return SpriteWidget::LAYOUT_BLOCK;
}

QPair< QSize, QSize > SpriteWidget::extremeSizes(QList< CssSpriteElementImage > * images) {
    QSize minSize = images->first().image().size();
    QSize maxSize = images->first().image().size();
    foreach (CssSpriteElementImage image, * images) {
        minSize = minSize.boundedTo(image.image().size());
        maxSize = maxSize.expandedTo(image.image().size());
    }
    return QPair< QSize, QSize >(minSize, maxSize);
}

SpriteWidget::SpriteWidget (
    QList< CssSpriteElementImage > * images,
    int xMargin,
    int yMargin,
    Layout layout,
    QWidget * parent,
    Qt::WFlags fl
) : QWidget ( parent, fl ) {
    this->_images = images;
    this->_elementXMargin = xMargin;
    this->_elementYMargin = yMargin;
    this->_layout = layout;
    this->update();
    this->_init();
    this->_calcImage();
}

void SpriteWidget::_init() {
    this->resize(this->_spriteSize());
    this->setBackgroundRole(QPalette::NoRole);
    this->setAttribute(Qt::WA_NoSystemBackground);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void SpriteWidget::_calcImage() {
    QPixmap pm(this->size());
    pm.fill(QColor(0,0,0,0));
    this->render(&pm);
    this->_spriteImage = pm;
}

void SpriteWidget::paintEvent(QPaintEvent* e) {
    if (this->_images->count() == 0) return;
    int xPos = this->_elementXMargin;
    int yPos = this->_elementYMargin;
    QSize maxSize = SpriteWidget::extremeSizes(this->_images).second;
    int horizontalElements = (int)sqrt(this->_images->count());
    int verticalElements = (int)(this->_images->count() / horizontalElements);
    verticalElements = (horizontalElements * verticalElements < this->_images->count())
                       ? verticalElements + 1
                       :verticalElements;

    this->_layout = (this->_layout == SpriteWidget::LAYOUT_BESTFIT)
                    ? SpriteWidget::bestfit(this->_images,this->_elementXMargin,this->_elementYMargin)
                    : this->_layout;

    this->_layout = (this->_layout == SpriteWidget::LAYOUT_BESTFILESIZE)
                    ? SpriteWidget::bestFileSize(this->_images,this->_elementXMargin,this->_elementYMargin)
                    : this->_layout;

    QPainter painter(this);

    switch (this->_layout) {
    case SpriteWidget::LAYOUT_BLOCK:
        for (int yElement = 1; yElement <= verticalElements; yElement++) {
            for (int xElement = 1; xElement <= horizontalElements; xElement++) {
                if (xElement+((yElement-1)*horizontalElements) > this->_images->count()) continue;
                CssSpriteElementImage image = this->_images->at(xElement+((yElement-1)*horizontalElements)-1);
                CssSpriteElementDescription * descr = new CssSpriteElementDescription(QPoint(xPos,yPos),image.image().size());
                image.updateDescription(descr);
                painter.drawImage(xPos,yPos,image.image());
                this->_images->replace(xElement+((yElement-1)*horizontalElements)-1,image);
                xPos += maxSize.width() + this->_elementXMargin;
            }
            xPos = this->_elementXMargin;
            yPos += maxSize.height() + this->_elementYMargin;
        }
        break;
    case SpriteWidget::LAYOUT_HORIZONTAL:
        foreach(CssSpriteElementImage image, * this->_images) {
            CssSpriteElementDescription * descr = new CssSpriteElementDescription(QPoint(xPos,yPos),image.image().size());
            image.updateDescription(descr);
            painter.drawImage(xPos,yPos,image.image());
            xPos += image.image().size().width() + this->_elementXMargin;
            this->_images->replace(this->_images->indexOf(image),image);
        }
        break;
    default:
    case SpriteWidget::LAYOUT_VERTICAL:
        foreach(CssSpriteElementImage image, * this->_images) {
            CssSpriteElementDescription * descr = new CssSpriteElementDescription(QPoint(xPos,yPos),image.image().size());
            image.updateDescription(descr);
            painter.drawImage(xPos,yPos,image.image());
            yPos += image.image().size().height() + this->_elementYMargin;
            this->_images->replace(this->_images->indexOf(image),image);
        }
        break;
    }
}

QSize SpriteWidget::_spriteSize() {
    if (this->_images->count() == 0) return QSize(this->_elementXMargin,this->_elementYMargin);
    int x = this->_elementXMargin;
    int y = this->_elementYMargin;
    int horizontalElements = (int)sqrt(this->_images->count());
    int verticalElements = (int)(this->_images->count() / horizontalElements);
    QSize maxSize = SpriteWidget::extremeSizes(this->_images).second;

    this->_layout = (this->_layout == SpriteWidget::LAYOUT_BESTFIT)
                    ? SpriteWidget::bestfit(this->_images,this->_elementXMargin,this->_elementYMargin)
                    : this->_layout;

    this->_layout = (this->_layout == SpriteWidget::LAYOUT_BESTFILESIZE)
                    ? SpriteWidget::bestFileSize(this->_images,this->_elementXMargin,this->_elementYMargin)
                    : this->_layout;

    switch (this->_layout) {
    case SpriteWidget::LAYOUT_BLOCK:
        verticalElements = (horizontalElements * verticalElements < this->_images->count())
                           ? verticalElements + 1
                           :verticalElements;
        return QSize(
                   x + (horizontalElements * x) + (horizontalElements * maxSize.width()),
                   y + (verticalElements * x) + (verticalElements * maxSize.height())
               );

        break;
    case SpriteWidget::LAYOUT_HORIZONTAL:
        foreach(CssSpriteElementImage image, * this->_images) {
            x = (x + this->_elementXMargin + image.image().size().width());
            if (y < image.image().size().height()) {
                y = image.image().size().height();
            }
        }
        return QSize(x,y+(2*this->_elementYMargin));
        break;
    default:
    case SpriteWidget::LAYOUT_VERTICAL:
        foreach(CssSpriteElementImage image, * this->_images) {
            y = (y + this->_elementYMargin + image.image().size().height());
            if (x < image.image().size().width()) {
                x = image.image().size().width();
            }
        }
        return QSize(x+(2*this->_elementXMargin),y);
        break;
    }
}
