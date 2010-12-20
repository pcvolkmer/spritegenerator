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
    int xPos = this->_elementXMargin;
    int yPos = this->_elementYMargin;

    QPainter painter(this);

    switch (this->_layout) {
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
    int x = this->_elementXMargin;
    int y = this->_elementYMargin;
    switch (this->_layout) {
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
