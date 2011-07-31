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

#ifndef CSSSPRITEELEMENTIMAGE_H
#define CSSSPRITEELEMENTIMAGE_H

#include <QtGui>
#include "cssspriteelementdescription.h"

class CssSpriteElementImage {
public:
    CssSpriteElementImage ( QString fileName, QImage image ) ;

    enum FileState {
        FILE_VIRTUAL = 1,
        FILE_DELETED = 2,
        FILE_CHANGED = 4,
        FILE_ADDED = 8,
        FILE_CONFLICT = 16,
        FILE_MODIFY = 32,
        FILE_MODIFIED = 64
    };

    QString fileName();
    void setFileName ( QString fileName );

    QImage image();
    void setImage ( QImage image );

    QByteArray fileData();
    void setFileData ( QByteArray data );

    bool isVirtual();
    void setVirtual ( bool isVirtual );

    bool isConflicting();
    void setConflicting ( bool isConflicting );

    CssSpriteElementImage::FileState fileState();
    void setFileState ( CssSpriteElementImage::FileState fileState );

    CssSpriteElementDescription * description();
    void updateDescription ( CssSpriteElementDescription * description );

    bool operator== ( CssSpriteElementImage obj );

private:
    QString _fileName;
    QImage _image;
    QByteArray _fileData;
    CssSpriteElementDescription * _description;
    CssSpriteElementImage::FileState _fileState;
};

#endif
