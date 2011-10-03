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

#ifndef PREVIEWPAGE_H
#define PREVIEWPAGE_H

#include <QtCore>
#include "cssspriteelementimage.h"
#include "version.h"

class PreviewPage {
public:
    static QByteArray create ( QList<CssSpriteElementImage> images );
    static QByteArray createCssOnly ( QList<CssSpriteElementImage> images );
    
private:
    PreviewPage ( QList<CssSpriteElementImage> images );
    ~PreviewPage();

    QByteArray create();
    QByteArray generateCss();

    QString * _outPuffer;
    QList<CssSpriteElementImage> _images;
};

#endif // PREVIEWPAGE_H
