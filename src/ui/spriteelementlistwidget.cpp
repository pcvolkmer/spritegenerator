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

#include "spriteelementlistwidget.h"

SpriteElementListWidget::SpriteElementListWidget(QWidget* parent): QListWidget(parent) {

}

SpriteElementListWidget::~SpriteElementListWidget() {

}

void SpriteElementListWidget::update(CssSpriteElementImageList* images) {
    this->_images = images;
    this->clear();
    foreach ( CssSpriteElementImage image, *this->_images ) {
        QListWidgetItem * item = new QListWidgetItem(image.fileName());
        if ( image.fileState() == CssSpriteElementImage::FILE_VIRTUAL ) {
            item->setIcon ( QIcon ( ":images/images/16x16/image-stack.png" ) );
            item->setTextColor ( QColor::fromRgb ( qRgb ( 0,0,0 ) ) );
            item->setToolTip ( "This image is present in a sprite file and not synchronised with the filesystem." );
        }
        if ( image.fileState() == CssSpriteElementImage::FILE_MODIFIED ) {
            item->setIcon ( QIcon ( ":images/images/16x16/vcs-locally-modified.png" ) );
            item->setTextColor ( QColor::fromRgb ( qRgb ( 0,100,0 ) ) );
            item->setToolTip ( "This image is ready to be exported." );
        }
        if ( image.fileState() == CssSpriteElementImage::FILE_ADDED ) {
            item->setIcon ( QIcon ( ":images/images/16x16/vcs-added.png" ) );
            item->setTextColor ( QColor::fromRgb ( qRgb ( 0,0,0 ) ) );
            item->setToolTip ( "This image has just been added from filesystem." );
        }
        if ( image.fileState() == CssSpriteElementImage::FILE_CONFLICT ) {
            item->setIcon ( QIcon ( ":images/images/16x16/vcs-conflicting.png" ) );
            item->setTextColor ( QColor::fromRgb ( qRgb ( 240,0,0 ) ) );
            item->setToolTip ( "This image conflicts with filesystem." );
        }
        if ( image.fileState() == CssSpriteElementImage::FILE_CHANGED ) {
            item->setIcon ( QIcon ( ":images/images/16x16/vcs-update-required.png" ) );
            item->setToolTip ( "Image changed on disk" );
            item->setTextColor ( QColor::fromRgb ( qRgb ( 240,0,0 ) ) );
            item->setToolTip ( "This image has just been changed on filesystem." );
        }
        if ( image.fileState() == CssSpriteElementImage::FILE_DELETED ) {
            item->setIcon ( QIcon ( ":images/images/16x16/vcs-removed.png" ) );
            item->setToolTip ( "Image deleted from disk" );
            item->setTextColor ( QColor::fromRgb ( qRgb ( 240,0,0 ) ) );
            item->setToolTip ( "This image has just been removed from filesystem." );
        }
        this->addItem ( item );
    }
}

