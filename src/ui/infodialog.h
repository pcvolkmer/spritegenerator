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

#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QtGui>
#include <QtCore>
#include "ui_infoDialog.h"
#include "version.h"

class InfoDialog : public QDialog, private Ui::InfoDialog {
    Q_OBJECT

public:
    InfoDialog ( QWidget* parent = 0, Qt::WFlags fl = 0 );
    ~InfoDialog();

public slots:

protected:

protected slots:
    void on_closeButton_clicked();
    void on_licenseButton_clicked();

};

#endif
