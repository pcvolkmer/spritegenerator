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

QPixmap SpriteWidget::createCssSprite(QList< CssSpriteElementImage > * images, int margin) {
    SpriteWidget swObject(images, margin);
    return swObject._spriteImage;
}

QList< CssSpriteElementImage > * SpriteWidget::updateCssSprite(QList< CssSpriteElementImage > * images, int margin) {
    SpriteWidget swObject(images, margin);
    return swObject._images;
}

SpriteWidget::SpriteWidget (
    QList< CssSpriteElementImage > * images,
    int margin,
    QWidget * parent,
    Qt::WFlags fl
) : QWidget ( parent, fl ) {
    this->_images = images;
    this->_elementMargin = margin;
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
    int xPos = this->_elementMargin;
    int yPos = this->_elementMargin;

    QPainter painter(this);

    foreach(CssSpriteElementImage image, * this->_images) {
        CssSpriteElementDescription * descr = new CssSpriteElementDescription(QPoint(xPos,yPos),image.image().size());
        image.updateDescription(descr);
        painter.drawImage(xPos,yPos,image.image());
        yPos += image.image().size().height() + this->_elementMargin;
        this->_images->replace(this->_images->indexOf(image),image);
    }
}

QSize SpriteWidget::_spriteSize() {
    int x = this->_elementMargin;
    int y = this->_elementMargin;
    foreach(CssSpriteElementImage image, * this->_images) {
        y = (y + this->_elementMargin + image.image().size().height());
        if (x < image.image().size().width()) {
            x = image.image().size().width();
        }
    }
    return QSize(x+10+this->_elementMargin,y+this->_elementMargin);
}
