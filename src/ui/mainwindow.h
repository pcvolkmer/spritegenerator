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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "ui_mainwindow.h"
#include "ui_spriteQualitySelector.h"
#include "spritewidget.h"
#include "infodialog.h"
#include "previewpage.h"
#include "cssspriteelementimagelist.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow ( QWidget* parent = 0, Qt::WFlags fl = 0 );
    ~MainWindow();

    Ui::MainWindow * getUi() {
        return this->ui;
    }

private:
    Ui::MainWindow * ui;
    QFileSystemWatcher * fsWatcher;
    CssSpriteElementImageList * _images;
    QComboBox * _qualityComboBox;
    QLabel * _qualityLabel;
    QProgressBar * _progressBar;
    QPushButton * _statusWarningPushButton;

    bool readyToExportSprite() ;
    void update();
    QString stripFileName ( QString filePath );
    bool createPreviewPage ( QString dirName );
    SpriteWidget::Format selectedSpriteFormat();
    void addQualityComboBox();

protected slots:
    void onFileChanged ( QString path );
    void onSettingsChanged() {
        this->_images = new CssSpriteElementImageList ( SpriteWidget::updateCssSprite (
                    this->_images,
                    ui->spriteSettingsToolBar->xMargin(),
                    ui->spriteSettingsToolBar->yMargin(),
                    ui->spriteSettingsToolBar->layout()
                ) );
        this->on_listWidget_currentItemChanged ( ui->listWidget->currentItem() );
    }

    void onShowAutoChangeForm(bool show) {
        ui->repeatSettingsInfoWidget->setVisible ( show );
        ui->resultingCssTextBrowser->setVisible ( ! show );
    }

    void on_actionAddFile_triggered();
    void on_actionAddDirectory_triggered();
    void on_actionRemoveFile_triggered();
    void on_actionExport_triggered();
    void on_actionImport_triggered();
    void on_actionSyncFilesystem_triggered();
    void on_createSpriteCommandButton_clicked();
    void on_previewPageCommandButton_clicked();
    void on_listWidget_itemPressed ( QListWidgetItem* item );
    void on_listWidget_currentItemChanged ( QListWidgetItem* item );
    void on_treeWidget_itemPressed ( QTreeWidgetItem* item );
    void on_treeWidget_currentItemChanged ( QTreeWidgetItem* item );
    void on_treeWidget_itemMoved();
    void on_actionInfo_triggered();
    void on_changeSettingsButton_clicked();
    void on_abortChangeSettingsButton_clicked();
    void on_moveUpToolButton_clicked();
    void on_moveDownToolButton_clicked();
};

#endif
