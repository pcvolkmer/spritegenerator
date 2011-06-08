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
 *   along with SpriteGenerator.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "cssspriteelementimage.h"

CssSpriteElementImage::CssSpriteElementImage(QString fileName, QImage image) {
    this->_fileName = fileName;
    this->_image = image;
    this->_description = NULL;
    QFile imageFile(fileName);
    if (imageFile.exists()) {
        imageFile.open(QIODevice::ReadOnly);
        this->_fileData = imageFile.readAll();
        imageFile.close();
    }
    else {
        this->_virtual = true;
    }
}

bool CssSpriteElementImage::operator==(CssSpriteElementImage obj) {
    return (
               this->fileName() == obj.fileName()
               && this->image() == obj.image()
           );
}

QImage CssSpriteElementImage::image() {
    return this->_image;
}

void CssSpriteElementImage::setImage(QImage image) {
    this->_image = image;
}

QString CssSpriteElementImage::fileName() {
    return this->_fileName;
}

void CssSpriteElementImage::setFileName(QString fileName) {
    this->_fileName = fileName;
}

QByteArray CssSpriteElementImage::fileData() {
    return this->_fileData;
}

void CssSpriteElementImage::setFileData(QByteArray data) {
    this->_fileData = data;
}

bool CssSpriteElementImage::isVirtual() {
    return this->_virtual;
}

void CssSpriteElementImage::setVirtual(bool isVirtual) {
    this->_virtual = isVirtual;
}

CssSpriteElementDescription * CssSpriteElementImage::description() {
    return this->_description;
}

void CssSpriteElementImage::updateDescription(CssSpriteElementDescription* description) {
    this->_description = description;
}

