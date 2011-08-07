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

#include "spriteformattoolbar.h"
#include <ui_spriteFormatSelector.h>

SpriteFormatToolBar::SpriteFormatToolBar(QWidget * parent): QToolBar(parent) {
    _ui = new Ui::SpriteFormatSelector();

    QWidget * spriteFormatWidget = new QWidget ( this );
    _ui->setupUi ( spriteFormatWidget );

    connect (_ui->xMarginSpinBox, SIGNAL(valueChanged(int)), SLOT(on_xMarginSpinBox_valueChanged(int)));
    connect (_ui->yMarginSpinBox, SIGNAL(valueChanged(int)), SLOT(on_yMarginSpinBox_valueChanged(int)));
    connect (_ui->lockMarginToolButton, SIGNAL(toggled(bool)), SLOT(on_lockMarginToolButton_toggled(bool)));
    connect (_ui->elementLayoutComboBox, SIGNAL(currentIndexChanged(int)), SLOT(on_elementLayoutComboBox_currentIndexChanged(int)));
    connect (_ui->spriteRepeatComboBox, SIGNAL(currentIndexChanged(int)), SLOT(on_spriteRepeatComboBox_currentIndexChanged(int)));
    this->addWidget ( spriteFormatWidget );
}

SpriteFormatToolBar::~SpriteFormatToolBar() {}

int SpriteFormatToolBar::xMargin() {
    return _ui->xMarginSpinBox->value();
}

int SpriteFormatToolBar::yMargin() {
    return _ui->yMarginSpinBox->value();
}

SpriteWidget::Layout SpriteFormatToolBar::layout() {
    return ( SpriteWidget::Layout ) _ui->elementLayoutComboBox->currentIndex();
}

QString SpriteFormatToolBar::repeat() {
    return _ui->spriteRepeatComboBox->currentText();
}

int SpriteFormatToolBar::repeatIndex() {
    return _ui->spriteRepeatComboBox->currentIndex();
}

void SpriteFormatToolBar::autoChangeSettings() {
    if ( _ui->spriteRepeatComboBox->currentIndex() == ( int ) SpriteWidget::REPEAT_REPEAT_X ) {
        _ui->xMarginSpinBox->setEnabled ( false );
        _ui->yMarginSpinBox->setEnabled ( true );
        _ui->xMarginSpinBox->setValue ( 0 );
        _ui->elementLayoutComboBox->setCurrentIndex ( ( int ) SpriteWidget::LAYOUT_VERTICAL );
    } else if ( _ui->spriteRepeatComboBox->currentIndex() == ( int ) SpriteWidget::REPEAT_REPEAT_Y ) {
        _ui->xMarginSpinBox->setEnabled ( true );
        _ui->yMarginSpinBox->setEnabled ( false );
        _ui->yMarginSpinBox->setValue ( 0 );
        _ui->elementLayoutComboBox->setCurrentIndex ( ( int ) SpriteWidget::LAYOUT_HORIZONTAL );
    }

    _ui->elementLayoutComboBox->setEnabled ( false );
}

void SpriteFormatToolBar::on_xMarginSpinBox_valueChanged(int i) {
    if (
        _ui->lockMarginToolButton->isChecked()
        && ( _ui->spriteRepeatComboBox->currentIndex() != ( int ) SpriteWidget::REPEAT_REPEAT_Y )
    ) {
        _ui->yMarginSpinBox->setValue ( _ui->xMarginSpinBox->value() );
    }
    emit settingsChanged();
}

void SpriteFormatToolBar::on_yMarginSpinBox_valueChanged(int i) {
    emit settingsChanged();
}

void SpriteFormatToolBar::on_elementLayoutComboBox_currentIndexChanged(int index) {
    emit settingsChanged();
}

void SpriteFormatToolBar::on_lockMarginToolButton_toggled(bool checked) {
    _ui->yMarginSpinBox->setEnabled ( !checked );
    _ui->yMarginSpinBox->setValue ( _ui->xMarginSpinBox->value() );
}

void SpriteFormatToolBar::on_spriteRepeatComboBox_currentIndexChanged(int index) {
    emit repeatNeedsAutoChange(false);
    _ui->lockMarginToolButton->setEnabled ( true );
    _ui->elementLayoutComboBox->setEnabled ( true );

    if ( ( index == ( int ) SpriteWidget::REPEAT_REPEAT_X ) || ( index == ( int ) SpriteWidget::REPEAT_REPEAT_Y ) ) {
        emit repeatNeedsAutoChange(true);
        _ui->lockMarginToolButton->setEnabled ( false );
    }

    if ( index == ( int ) SpriteWidget::REPEAT_NO_REPEAT ) {
        _ui->xMarginSpinBox->setEnabled ( true );
        _ui->yMarginSpinBox->setEnabled ( ! _ui->lockMarginToolButton->isChecked() );
    }
}
