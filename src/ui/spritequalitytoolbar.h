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

#ifndef SPRITEQUALITYTOOLBAR_H
#define SPRITEQUALITYTOOLBAR_H

#include <QtGui>
#include <QtCore>
#include "ui_spriteQualitySelector.h"
#include "spritewidget.h"

class SpriteQualityToolBar : public QToolBar {
    Q_OBJECT

public:
    explicit SpriteQualityToolBar(QWidget * parent = 0);
    virtual ~SpriteQualityToolBar();

    const Ui_SpriteQualitySelector * ui() ;
    int compressionLevel() ;
    int qImageQuality() ;
    SpriteWidget::Format colorDepth() ;

private:
    Ui::SpriteQualitySelector * _ui;
    
private slots:
    void emitQualityChanged() ;

signals:
    void qualityChanged();
};

#endif
