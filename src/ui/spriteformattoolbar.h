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

#ifndef SPRITEFORMATTOOLBAR_H
#define SPRITEFORMATTOOLBAR_H

#include <QtGui>
#include <QtCore>
#include "ui_spriteFormatSelector.h"
#include "spritewidget.h"

class SpriteFormatToolBar : public QToolBar {
    Q_OBJECT

public:
    explicit SpriteFormatToolBar(QWidget * parent = 0);
    ~SpriteFormatToolBar();

    const Ui_SpriteFormatSelector * ui() {
      return _ui;
    }
    
    int xMargin();
    int yMargin();
    SpriteWidget::Layout layout();
    QString repeat();
    int repeatIndex();
    void autoChangeSettings();

private slots:
    void on_xMarginSpinBox_valueChanged ( int i ) ;
    void on_yMarginSpinBox_valueChanged ( int i ) ;
    void on_elementLayoutComboBox_currentIndexChanged ( int index ) ;
    void on_lockMarginToolButton_toggled ( bool checked ) ;
    void on_spriteRepeatComboBox_currentIndexChanged ( int index ) ;

private:
    Ui::SpriteFormatSelector * _ui;

signals:
    void settingsChanged();
    void repeatNeedsAutoChange(bool);
};

#endif
