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
    ui = new Ui::SpriteFormatSelector();

    QWidget * spriteFormatWidget = new QWidget ( this );
    ui->setupUi ( spriteFormatWidget );

    connect (ui->xMarginSpinBox, SIGNAL(valueChanged(int)), SLOT(on_xMarginSpinBox_valueChanged(int)));
    connect (ui->yMarginSpinBox, SIGNAL(valueChanged(int)), SLOT(on_yMarginSpinBox_valueChanged(int)));
    connect (ui->lockMarginToolButton, SIGNAL(toggled(bool)), SLOT(on_lockMarginToolButton_toggled(bool)));
    connect (ui->elementLayoutComboBox, SIGNAL(currentIndexChanged(int)), SLOT(on_elementLayoutComboBox_currentIndexChanged(int)));
    connect (ui->spriteRepeatComboBox, SIGNAL(currentIndexChanged(int)), SLOT(on_spriteRepeatComboBox_currentIndexChanged(int)));
    this->addWidget ( spriteFormatWidget );
}

SpriteFormatToolBar::~SpriteFormatToolBar() {}

int SpriteFormatToolBar::xMargin() {
    return ui->xMarginSpinBox->value();
}

int SpriteFormatToolBar::yMargin() {
    return ui->yMarginSpinBox->value();
}

SpriteWidget::Layout SpriteFormatToolBar::layout() {
    return ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex();
}

QString SpriteFormatToolBar::repeat() {
    return ui->spriteRepeatComboBox->currentText();
}

int SpriteFormatToolBar::repeatIndex() {
    return ui->spriteRepeatComboBox->currentIndex();
}

void SpriteFormatToolBar::autoChangeSettings() {
    if ( ui->spriteRepeatComboBox->currentIndex() == ( int ) SpriteWidget::REPEAT_REPEAT_X ) {
        ui->xMarginSpinBox->setEnabled ( false );
        ui->yMarginSpinBox->setEnabled ( true );
        ui->xMarginSpinBox->setValue ( 0 );
        ui->elementLayoutComboBox->setCurrentIndex ( ( int ) SpriteWidget::LAYOUT_VERTICAL );
    } else if ( ui->spriteRepeatComboBox->currentIndex() == ( int ) SpriteWidget::REPEAT_REPEAT_Y ) {
        ui->xMarginSpinBox->setEnabled ( true );
        ui->yMarginSpinBox->setEnabled ( false );
        ui->yMarginSpinBox->setValue ( 0 );
        ui->elementLayoutComboBox->setCurrentIndex ( ( int ) SpriteWidget::LAYOUT_HORIZONTAL );
    }

    ui->elementLayoutComboBox->setEnabled ( false );
}

void SpriteFormatToolBar::on_xMarginSpinBox_valueChanged(int i) {
    if (
        ui->lockMarginToolButton->isChecked()
        && ( ui->spriteRepeatComboBox->currentIndex() != ( int ) SpriteWidget::REPEAT_REPEAT_Y )
    ) {
        ui->yMarginSpinBox->setValue ( ui->xMarginSpinBox->value() );
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
    ui->yMarginSpinBox->setEnabled ( !checked );
    ui->yMarginSpinBox->setValue ( ui->xMarginSpinBox->value() );
}

void SpriteFormatToolBar::on_spriteRepeatComboBox_currentIndexChanged(int index) {
    emit repeatNeedsAutoChange(false);
    ui->lockMarginToolButton->setEnabled ( true );
    ui->elementLayoutComboBox->setEnabled ( true );

    if ( ( index == ( int ) SpriteWidget::REPEAT_REPEAT_X ) || ( index == ( int ) SpriteWidget::REPEAT_REPEAT_Y ) ) {
        emit repeatNeedsAutoChange(true);
        ui->lockMarginToolButton->setEnabled ( false );
    }

    if ( index == ( int ) SpriteWidget::REPEAT_NO_REPEAT ) {
        ui->xMarginSpinBox->setEnabled ( true );
        ui->yMarginSpinBox->setEnabled ( ! ui->lockMarginToolButton->isChecked() );
    }
}
