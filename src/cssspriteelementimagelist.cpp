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

#include "cssspriteelementimagelist.h"

bool CssSpriteElementImageList::moveUp ( CssSpriteElementImage image ) {
    int index = this->indexOf ( image );
    if ( index >= 1 ) {
        this->move ( index, index-1 );
        return true;
    }
    return false;
}

bool CssSpriteElementImageList::moveDown ( CssSpriteElementImage image ) {
    int index = this->indexOf ( image );
    if ( index < this->count()-1 ) {
        this->move ( index, index+1 );
        return true;
    }
    return false;
}

CssSpriteElementImage * CssSpriteElementImageList::find ( QString fileName ) {
    QListIterator<CssSpriteElementImage> i ( * this );
    CssSpriteElementImage * image;
    while ( i.hasNext() ) {
        image = ( CssSpriteElementImage * ) & i.next();
        if ( image->fileName() == fileName ) return image;
    }
    return NULL;
}
