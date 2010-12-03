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

#include "cssspriteelementdescription.h"

CssSpriteElementDescription::CssSpriteElementDescription(QPoint start, QSize size) {
    this->_position = start;
    this->_size = size;
}

QSize CssSpriteElementDescription::size() {
    return this->_size;
}

QPoint CssSpriteElementDescription::startPosition() {
    return this->_position;
}


