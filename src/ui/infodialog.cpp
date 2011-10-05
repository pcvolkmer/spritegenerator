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
 *   along with SpriteGenerator.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "infodialog.h"

InfoDialog::InfoDialog ( QWidget* parent, Qt::WFlags fl )
        : QDialog ( parent, fl ), Ui::InfoDialog() {
    setupUi ( this );
    this->licenseBrowser->hide();
    this->setFixedHeight(200);
    QFile license ( ":others/others/license" );
    license.open ( QIODevice::ReadOnly );
    this->licenseBrowser->setText ( license.readAll() );
    this->versionLabel->setText ( QString(VERSION_MAJOR) +"." + QString(VERSION_MINOR) + "." + QString(VERSION_RELEASE) + "-" + QString(VERSION_BUILD) );
}

InfoDialog::~InfoDialog() {
}

void InfoDialog::on_closeButton_clicked() {
    this->close();
}

void InfoDialog::on_licenseButton_clicked() {
    if (this->licenseButton->isChecked()) {
        this->setFixedHeight(400);
        this->licenseBrowser->show();
    }
    else {
        this->setFixedHeight(200);
        this->licenseBrowser->hide();
    }
}

