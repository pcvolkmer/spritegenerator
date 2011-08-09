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

#include "spritequalitytoolbar.h"

SpriteQualityToolBar::SpriteQualityToolBar(QWidget* parent): QToolBar(parent) {
    _ui = new Ui::SpriteQualitySelector();

    QWidget * spriteQualityWidget = new QWidget ( this );
    _ui->setupUi ( spriteQualityWidget );

    connect(_ui->compressionSpinBox, SIGNAL(valueChanged(int)), SLOT(emitQualityChanged()));
    connect(_ui->qualityComboBox, SIGNAL(currentIndexChanged(int)), SLOT(emitQualityChanged()));

    this->addWidget( spriteQualityWidget );
}

SpriteQualityToolBar::~SpriteQualityToolBar() {}

void SpriteQualityToolBar::emitQualityChanged() {
    emit qualityChanged();
}

const Ui_SpriteQualitySelector* SpriteQualityToolBar::ui() {
    return _ui;
}

int SpriteQualityToolBar::compressionLevel() {
    return _ui->compressionSpinBox->value();
}

int SpriteQualityToolBar::qImageQuality() {
    return this->compressionLevel() * 11;
}

SpriteWidget::Format SpriteQualityToolBar::colorDepth() {
    return (SpriteWidget::Format) _ui->qualityComboBox->currentIndex();
}
