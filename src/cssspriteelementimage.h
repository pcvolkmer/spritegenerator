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

#ifndef CSSSPRITEELEMENTIMAGE_H
#define CSSSPRITEELEMENTIMAGE_H

#include <QtGui>
#include "cssspriteelementdescription.h"

class CssSpriteElementImage {
public:
    CssSpriteElementImage(QString fileName, QImage image) ;

    QString fileName() ;

    QImage image() ;
    
    CssSpriteElementDescription * description();
    void updateDescription(CssSpriteElementDescription * description);

    bool operator==(CssSpriteElementImage obj);

private:
    QString _fileName;
    QImage _image;
    CssSpriteElementDescription * _description;
};

#endif
