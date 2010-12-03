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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "ui_mainwindow.h"
#include "spritewidget.h"
#include "infodialog.h"

class MainWindow : public QMainWindow, private Ui::MainWindow {
    Q_OBJECT

public:
    MainWindow ( QWidget* parent = 0, Qt::WFlags fl = 0 );
    ~MainWindow();

private:
    void updateListWidget();

    QList< CssSpriteElementImage > * _images;
    
    QString stripFileName(QString filePath) {
        return filePath.split("/").last();
    }

protected slots:
    void on_actionAddFile_triggered();
    void on_actionAddDirectory_triggered();
    void on_actionRemoveFile_triggered();
    void on_createSpriteCommandButton_clicked();
    void on_previewPageCommandButton_clicked();
    void on_listWidget_itemPressed(QListWidgetItem* item);
    void on_listWidget_currentItemChanged(QListWidgetItem* item);
    void on_actionInfo_triggered();
    void on_marginSpinBox_valueChanged(int i);
};

#endif
