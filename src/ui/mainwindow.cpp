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

#include "mainwindow.h"

MainWindow::MainWindow ( QWidget* parent, Qt::WFlags fl )
        : QMainWindow ( parent, fl ), ui ( new Ui::MainWindow() ) {
    this->_progressBar = new QProgressBar();

    this->_statusWarningPushButton = new QPushButton();
    this->_statusWarningPushButton->setIcon ( QIcon ( ":images/images/16x16/dialog-warning.png" ) );
    this->_statusWarningPushButton->setEnabled ( false );

    this->_images = new CssSpriteElementImageList();

    ui->setupUi ( this );

    this->addQualityComboBox();
    this->statusBar()->addPermanentWidget ( this->_progressBar );
    this->statusBar()->addPermanentWidget ( this->_statusWarningPushButton );

    ui->repeatSettingsInfoWidget->setVisible ( false );

    ui->listWidget->setContextMenuPolicy ( Qt::ActionsContextMenu );
    foreach ( QAction * action, ui->toolBar->actions() ) {
        if ( ! ( action->text() == NULL ) ) {
            ui->listWidget->addAction ( action );
        }
    }

    this->update();
    this->fsWatcher = new QFileSystemWatcher();

    connect ( fsWatcher, SIGNAL ( fileChanged ( QString ) ), this, SLOT ( onFileChanged ( QString ) ) );
}

MainWindow::~MainWindow() {
    delete this->_images;
    delete this->_progressBar;
    delete this->ui;
}

void MainWindow::update() {
    ui->actionRemoveFile->setEnabled ( false );
    ui->actionExport->setEnabled ( false );
    ui->actionSyncFilesystem->setEnabled ( false );
    ui->createSpriteCommandButton->setEnabled ( false );
    ui->previewPageCommandButton->setEnabled ( false );
    if ( ui->listWidget->count() > 0 ) {
        ui->actionRemoveFile->setEnabled ( true );
        if ( this->readyToExportSprite() ) ui->actionExport->setEnabled ( true );
        ui->actionSyncFilesystem->setEnabled ( true );
        ui->createSpriteCommandButton->setEnabled ( true );
        ui->previewPageCommandButton->setEnabled ( true );
    }

    ui->listWidget->update ( this->_images );
    ui->treeWidget->update ( this->_images );
}

void MainWindow::onFileChanged ( QString path ) {
    QListWidgetItem * item = ui->listWidget->findItems ( path, Qt::MatchExactly ).at ( 0 );
    item->setTextColor ( QColor::fromRgb ( qRgb ( 240,0,0 ) ) );
    QFileInfo fileInfo ( path );
    CssSpriteElementImage * image = this->_images->find ( path );
    if ( image->fileState() == CssSpriteElementImage::FILE_MODIFY ) return;
    if ( fileInfo.exists() ) {
        item->setIcon ( QIcon ( ":images/images/16x16/vcs-update-required.png" ) );
        item->setToolTip ( "Image changed on disk" );
        image->setFileState ( CssSpriteElementImage::FILE_CHANGED );
    } else {
        item->setIcon ( QIcon ( ":images/images/16x16/vcs-removed.png" ) );
        item->setToolTip ( "Image deleted from disk" );
        image->setFileState ( CssSpriteElementImage::FILE_DELETED );
    }
}

void MainWindow::on_actionAddDirectory_triggered() {
    QString dirName = QFileDialog::getExistingDirectory (
                          this,
                          tr ( "Add directory" ),
                          "./",
                          QFileDialog::ReadOnly
                      );
    if ( dirName.isEmpty() ) return;
    this->statusBar()->clearMessage();
    this->setCursor ( Qt::WaitCursor );
    QDir directory ( dirName );
    this->_progressBar->setMinimum ( 0 );
    this->_progressBar->setMaximum ( directory.count()-1 );

    int importCounter = 0;
    int failCounter = 0;
    foreach ( QString fileName, directory.entryList() ) {
        QFileInfo fileInfo ( dirName + "/" + fileName );
        this->_progressBar->setValue ( this->_progressBar->value() +1 );
        if ( fileInfo.isDir() ) continue;
        QImage image ( dirName + "/" + fileName );

        if ( !image.isNull() ) {
            CssSpriteElementImage img ( dirName + "/" + fileName,image );
            if ( !this->_images->contains ( img ) ) {
                img.setFileState ( CssSpriteElementImage::FILE_ADDED );
                this->_images->append ( img );
                ui->listWidget->addItem ( dirName + "/" + fileName );
                this->fsWatcher->addPath ( dirName + "/" + fileName );
            }
            importCounter++;
        } else {
            failCounter++;
        }
    }

    if ( ( importCounter > 0 ) && ( failCounter == 0 ) ) {
        this->statusBar()->showMessage (
            tr ( "Import of %n image(s) succeed.","",importCounter ),
            15000
        );
    }
    if ( ( importCounter == 0 ) && ( failCounter > 0 ) ) {
        this->statusBar()->showMessage (
            tr ( "No usable images were found." ),
            15000
        );
    }
    if ( ( importCounter > 0 ) && ( failCounter > 0 ) ) {
        this->statusBar()->showMessage (
            tr ( "Import of %n image(s) succeed, ","",importCounter )
            + tr ( "import of %n file(s) failed. ","",failCounter ),
            15000
        );
    }

    this->_images = new CssSpriteElementImageList (
        SpriteWidget::updateCssSprite (
            this->_images,
            ui->xMarginSpinBox->value(),
            ui->yMarginSpinBox->value(),
            ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex()
        )
    );
    this->_progressBar->reset();
    this->setCursor ( Qt::ArrowCursor );
    this->update();
}

void MainWindow::on_actionAddFile_triggered() {
    QString fileName = QFileDialog::getOpenFileName (
                           this,
                           tr ( "Add file" ),
                           "./"
                       );
    if ( fileName.isEmpty() ) return;
    this->statusBar()->clearMessage();
    this->setCursor ( Qt::WaitCursor );
    QImage image ( fileName );
    if ( !image.isNull() ) {
        CssSpriteElementImage img ( fileName,image );
        if ( !this->_images->contains ( img ) ) {
            img.setFileState ( CssSpriteElementImage::FILE_ADDED );
            this->_images->append ( img );
            ui->listWidget->addItem ( fileName );
            this->fsWatcher->addPath ( fileName );
        }
        this->statusBar()->showMessage (
            tr ( "Import of 1 image succeed." ),
            10000
        );
    } else {
        this->statusBar()->showMessage (
            tr ( "Could not import file: Not a useable image format." ),
            10000
        );
    }
    this->_images = new CssSpriteElementImageList ( SpriteWidget::updateCssSprite (
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex()
            ) );
    this->setCursor ( Qt::ArrowCursor );
    this->update();
}

void MainWindow::on_actionRemoveFile_triggered() {
    if ( ui->tabWidget->currentIndex() == 0 ) {
        QList<QListWidgetItem*> itemlist = ui->listWidget->selectedItems();
        foreach ( QListWidgetItem * item, itemlist ) {
            foreach ( CssSpriteElementImage image, *this->_images ) {
                if ( image.fileName() == item->text() ) {
                    this->_images->removeOne ( image );
                }
            }
            this->fsWatcher->removePath ( item->text() );
            this->_images = new CssSpriteElementImageList ( SpriteWidget::updateCssSprite (
                        this->_images,
                        ui->xMarginSpinBox->value(),
                        ui->yMarginSpinBox->value(),
                        ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex()
                    ) );
            delete item;
        }
    } else if ( ui->tabWidget->currentIndex() == 1 ) {
        QList<QTreeWidgetItem*> itemlist = ui->treeWidget->selectedItems();
        foreach ( QTreeWidgetItem * item, itemlist ) {
            foreach ( CssSpriteElementImage image, *this->_images ) {
                if ( image.fileName() == ui->treeWidget->fileName ( item ) ) {
                    this->_images->removeOne ( image );
                }
            }
            this->fsWatcher->removePath ( ui->treeWidget->fileName ( item ) );
            this->_images = new CssSpriteElementImageList ( SpriteWidget::updateCssSprite (
                        this->_images,
                        ui->xMarginSpinBox->value(),
                        ui->yMarginSpinBox->value(),
                        ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex()
                    ) );
            delete item;
        }
    }
    this->update();
}

void MainWindow::on_actionExport_triggered() {
    QString fileName = QFileDialog::getSaveFileName (
                           this,
                           tr ( "Export spriteset" ),
                           "./",
                           "Spriteset (*.sprite)"
                       );

    if ( fileName.isEmpty() ) return;

    SpriteWidget::exportToFile (
        fileName,
        this->_images,
        ui->xMarginSpinBox->value(),
        ui->yMarginSpinBox->value(),
        ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex(),
        ( SpriteWidget::Format ) this->selectedSpriteFormat()
    );

    this->update();
}

void MainWindow::on_actionImport_triggered() {
    if ( ui->listWidget->count() > 0 ) {
        if (
            QMessageBox::question (
                this,
                "Import spriteset",
                "A spriteset should be imported. This will discard the actual sprite.",
                QMessageBox::Ok|QMessageBox::Abort,
                QMessageBox::Abort
            ) == QMessageBox::Abort
        ) return;
    }

    QString fileName = QFileDialog::getOpenFileName (
                           this,
                           tr ( "Import spriteset" ),
                           "./",
                           "Spriteset (*.sprite)"
                       );

    if ( fileName.isEmpty() ) return;

    ui->listWidget->clear();
    this->_images->clear();

    foreach ( CssSpriteElementImage image, * SpriteWidget::importFromFile ( fileName ) ) {
        ui->listWidget->addItem ( image.fileName() );
        this->_images->append ( image );
        QListWidgetItem * item = ui->listWidget->findItems ( image.fileName(), Qt::MatchExactly ).at ( 0 );
        item->setIcon ( QIcon ( ":images/images/16x16/vcs-added.png" ) );
        item->setTextColor ( QColor::fromRgb ( qRgb ( 0,100,0 ) ) );
    }

    this->_images = new CssSpriteElementImageList ( SpriteWidget::updateCssSprite (
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex()
            ) );

    this->update();
}

void MainWindow::on_actionSyncFilesystem_triggered() {
    QString dirName = QFileDialog::getExistingDirectory (
                          this,
                          tr ( "Select directory to store imported files" ),
                          "./",
                          QFileDialog::ReadOnly
                      );

    if ( dirName.isEmpty() ) return;

    bool conflicts = false;

    QListIterator<CssSpriteElementImage> i ( * this->_images );

    while ( i.hasNext() ) {
        CssSpriteElementImage * image = ( CssSpriteElementImage * ) &i.next();
        if ( image->fileState() == CssSpriteElementImage::FILE_CONFLICT ) {
            conflicts = true;
            continue;
        }
        if (
            image->fileState()
            & (
                CssSpriteElementImage::FILE_VIRTUAL
                | CssSpriteElementImage::FILE_ADDED
                | CssSpriteElementImage::FILE_CHANGED
            )
        ) {
            QListWidgetItem * item = ui->listWidget->findItems ( image->fileName(), Qt::MatchExactly ).at ( 0 );
            if ( image->fileState() & CssSpriteElementImage::FILE_VIRTUAL ) {
                image->setFileName ( dirName + "/" + image->fileName() );
            }
            QFile file ( image->fileName() );
            QFileInfo fileInfo ( file.fileName() );
            item->setText ( image->fileName() );
            if ( fileInfo.exists() ) {
                conflicts = true;
                image->setFileState ( CssSpriteElementImage::FILE_CONFLICT );
                continue;
            }
            QDir dir;
            dir.mkpath ( fileInfo.path() );
            file.open ( QIODevice::WriteOnly );
            CssSpriteElementImage::FileState oldState = image->fileState();
            image->setFileState ( CssSpriteElementImage::FILE_MODIFY );
            this->fsWatcher->removePath ( image->fileName() );
            if ( file.write ( image->fileData() ) ) {
                image->setFileState ( CssSpriteElementImage::FILE_MODIFIED );
            } else {
                image->setFileState ( oldState );
            }
            file.close();

            this->fsWatcher->addPath ( image->fileName() );
        }
    }

    if ( conflicts ) {
        if (
            QMessageBox::question (
                this,
                "Sync filesystem",
                "Some conflicts occure. Do you wish to overwrite files on filesystem?",
                QMessageBox::Ok|QMessageBox::Abort,
                QMessageBox::Abort
            ) == QMessageBox::Ok
        ) {
            QListIterator<CssSpriteElementImage> i ( * this->_images );

            while ( i.hasNext() ) {
                CssSpriteElementImage * image = ( CssSpriteElementImage * ) &i.next();
                if ( image->fileState() == CssSpriteElementImage::FILE_CONFLICT ) {
                    QFile file ( image->fileName() );
                    QFileInfo fileInfo ( file.fileName() );
                    QDir dir;
                    dir.mkpath ( fileInfo.path() );
                    file.open ( QIODevice::WriteOnly );
                    CssSpriteElementImage::FileState oldState = image->fileState();
                    image->setFileState ( CssSpriteElementImage::FILE_MODIFY );
                    this->fsWatcher->removePath ( image->fileName() );
                    if ( file.write ( image->fileData() ) ) {
                        image->setFileState ( CssSpriteElementImage::FILE_MODIFIED );
                    } else {
                        image->setFileState ( oldState );
                    }
                    file.close();

                    this->fsWatcher->addPath ( image->fileName() );
                }
            }
        }
    }

    this->update();
}

void MainWindow::on_createSpriteCommandButton_clicked() {
    QString fileName = QFileDialog::getSaveFileName (
                           this,
                           tr ( "Save css sprite file" ),
                           "./",
                           "PNG Image (*.png)"
                       );

    if ( fileName.isEmpty() ) return;

    SpriteWidget::createCssSprite (
        this->_images,
        ui->xMarginSpinBox->value(),
        ui->yMarginSpinBox->value(),
        ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex(),
        ( SpriteWidget::Format ) this->selectedSpriteFormat()
    ).save ( fileName );
}

void MainWindow::on_previewPageCommandButton_clicked() {
    QString dirName = QDir::tempPath();
    if ( dirName.isEmpty() ) return;
    this->createPreviewPage ( dirName );
    SpriteWidget::createCssSprite (
        this->_images,
        ui->xMarginSpinBox->value(),
        ui->yMarginSpinBox->value(),
        ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex(),
        ( SpriteWidget::Format ) this->selectedSpriteFormat()
    ).save ( dirName + "/sprite.png" );

#ifdef WIN32
    QDesktopServices::openUrl ( QUrl ( "file:///" + dirName + "/index.html" ) );
#else
    QDesktopServices::openUrl ( QUrl ( "file://" + dirName + "/index.html" ) );
#endif
}

bool MainWindow::createPreviewPage ( QString dirName ) {
    QFile htmlFile ( dirName + "/index.html" );
    htmlFile.open ( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate );
    if ( !htmlFile.isWritable() ) return false;

    htmlFile.write ( PreviewPage::create ( *this->_images ) );

    htmlFile.close();
    return true;
}

void MainWindow::on_listWidget_itemPressed ( QListWidgetItem * item ) {
    QString fileName = item->text();

    foreach ( CssSpriteElementImage elem, * this->_images ) {
        if ( elem.fileName() == fileName ) {
            ui->fileName->setText ( this->stripFileName ( fileName ) );
            ui->imageSizeX->setText ( QString::number ( elem.description()->size().width(),10 ) + "px" );
            ui->imageSizeY->setText ( QString::number ( elem.description()->size().height(),10 ) + "px" );
            ui->resultingCssTextBrowser->setText (
                "/* " + this->stripFileName ( fileName ) + " */\n"
                + QString ( "background-image: url(<SPRITE URL>);\n" )
                + QString ( "background-repeat: " )
                + ui->spriteRepeatComboBox->currentText()
                + ";\nbackground-position: -"
                + QString::number ( elem.description()->startPosition().x(),10 )
                + "px -"
                + QString::number ( elem.description()->startPosition().y(),10 )
                + "px;\n"
                + "width: "
                + QString::number ( elem.description()->size().width(),10 )
                + "px;\nheight: "
                + QString::number ( elem.description()->size().height(),10 )
                + "px;"
            );
            ui->elementImageLabel->setPixmap ( QPixmap::fromImage ( elem.image() ) );
            return;
        }
    }
}

void MainWindow::on_treeWidget_itemPressed ( QTreeWidgetItem * item ) {
    QString fileName;

    while ( item->parent() ) {
        fileName.prepend ( item->text ( 0 ) );
        if ( item->text ( 0 ) != "/" ) fileName.prepend ( "/" );
        item = item->parent();
    }
    fileName.remove ( 0,1 );

    foreach ( CssSpriteElementImage elem, * this->_images ) {
        if ( elem.fileName() == fileName ) {
            ui->fileName->setText ( this->stripFileName ( fileName ) );
            ui->imageSizeX->setText ( QString::number ( elem.description()->size().width(),10 ) + "px" );
            ui->imageSizeY->setText ( QString::number ( elem.description()->size().height(),10 ) + "px" );
            ui->resultingCssTextBrowser->setText (
                "/* " + this->stripFileName ( fileName ) + " */\n"
                + QString ( "background-image: url(<SPRITE URL>);\n" )
                + QString ( "background-repeat: " )
                + ui->spriteRepeatComboBox->currentText()
                + ";\nbackground-position: -"
                + QString::number ( elem.description()->startPosition().x(),10 )
                + "px -"
                + QString::number ( elem.description()->startPosition().y(),10 )
                + "px;\n"
                + "width: "
                + QString::number ( elem.description()->size().width(),10 )
                + "px;\nheight: "
                + QString::number ( elem.description()->size().height(),10 )
                + "px;"
            );
            ui->elementImageLabel->setPixmap ( QPixmap::fromImage ( elem.image() ) );
            return;
        }
    }
}

void MainWindow::on_listWidget_currentItemChanged ( QListWidgetItem* item ) {
    ui->fileName->clear();
    ui->imageSizeX->clear();
    ui->imageSizeY->clear();
    ui->resultingCssTextBrowser->clear();
    ui->elementImageLabel->clear();
    if ( item == NULL ) return;
    this->on_listWidget_itemPressed ( item );
}

void MainWindow::on_treeWidget_currentItemChanged ( QTreeWidgetItem* item ) {
    ui->fileName->clear();
    ui->imageSizeX->clear();
    ui->imageSizeY->clear();
    ui->resultingCssTextBrowser->clear();
    ui->elementImageLabel->clear();
    if ( item == NULL ) return;
    this->on_treeWidget_itemPressed ( item );
}

void MainWindow::on_actionInfo_triggered() {
    InfoDialog infoDialog;
    infoDialog.exec();
}

void MainWindow::on_xMarginSpinBox_valueChanged ( int i ) {
    if (
        ui->lockMarginToolButton->isChecked()
        && ( ui->spriteRepeatComboBox->currentIndex() != ( int ) SpriteWidget::REPEAT_REPEAT_Y )
    ) {
        ui->yMarginSpinBox->setValue ( ui->xMarginSpinBox->value() );
    }

    this->_images = new CssSpriteElementImageList ( SpriteWidget::updateCssSprite (
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex()
            ) );
    this->on_listWidget_currentItemChanged ( ui->listWidget->currentItem() );
}

void MainWindow::on_yMarginSpinBox_valueChanged ( int i ) {
    this->_images = new CssSpriteElementImageList ( SpriteWidget::updateCssSprite (
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex()
            ) );
    this->on_listWidget_currentItemChanged ( ui->listWidget->currentItem() );
}

void MainWindow::on_elementLayoutComboBox_currentIndexChanged ( int index ) {
    this->_images = new CssSpriteElementImageList ( SpriteWidget::updateCssSprite (
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                ( SpriteWidget::Layout ) index
            ) );
    this->on_listWidget_currentItemChanged ( ui->listWidget->currentItem() );
}

// Refacs!

void MainWindow::on_spriteRepeatComboBox_currentIndexChanged ( int index ) {
    ui->repeatSettingsInfoWidget->setVisible ( false );
    ui->resultingCssTextBrowser->setVisible ( true );
    ui->lockMarginToolButton->setEnabled ( true );
    ui->elementLayoutComboBox->setEnabled ( true );

    if ( ( index == ( int ) SpriteWidget::REPEAT_REPEAT_X ) || ( index == ( int ) SpriteWidget::REPEAT_REPEAT_Y ) ) {
        ui->repeatSettingsInfoWidget->setVisible ( true );
        ui->resultingCssTextBrowser->setVisible ( false );
        ui->lockMarginToolButton->setEnabled ( false );
    }

    if ( index == ( int ) SpriteWidget::REPEAT_NO_REPEAT ) {
        ui->xMarginSpinBox->setEnabled ( true );
        ui->yMarginSpinBox->setEnabled ( ! ui->lockMarginToolButton->isChecked() );
    }
}

void MainWindow::on_lockMarginToolButton_toggled ( bool checked ) {
    ui->yMarginSpinBox->setEnabled ( !checked );
    ui->yMarginSpinBox->setValue ( ui->xMarginSpinBox->value() );
}

void MainWindow::on_changeSettingsButton_clicked() {
    int repeatIndex = ui->spriteRepeatComboBox->currentIndex();

    if ( repeatIndex == ( int ) SpriteWidget::REPEAT_REPEAT_X ) {
        ui->xMarginSpinBox->setEnabled ( false );
        ui->yMarginSpinBox->setEnabled ( true );
        ui->xMarginSpinBox->setValue ( 0 );
        ui->elementLayoutComboBox->setCurrentIndex ( ( int ) SpriteWidget::LAYOUT_VERTICAL );
    } else if ( repeatIndex == ( int ) SpriteWidget::REPEAT_REPEAT_Y ) {
        ui->xMarginSpinBox->setEnabled ( true );
        ui->yMarginSpinBox->setEnabled ( false );
        ui->yMarginSpinBox->setValue ( 0 );
        ui->elementLayoutComboBox->setCurrentIndex ( ( int ) SpriteWidget::LAYOUT_HORIZONTAL );
    }

    ui->elementLayoutComboBox->setEnabled ( false );

    this->on_abortChangeSettingsButton_clicked();
}

void MainWindow::on_abortChangeSettingsButton_clicked() {
    ui->repeatSettingsInfoWidget->setVisible ( false );
    ui->resultingCssTextBrowser->setVisible ( true );
    this->on_listWidget_currentItemChanged ( ui->listWidget->currentItem() );
}

void MainWindow::on_moveDownToolButton_clicked() {
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();
    QList<QString> selectedItemLabels;

    if ( selectedItems.count() == 0 ) return;

    QList<CssSpriteElementImage> images;
    foreach ( CssSpriteElementImage image, *this->_images ) {
        images.push_front ( image );
    }

    foreach ( CssSpriteElementImage image, images ) {
        foreach ( QListWidgetItem * item, selectedItems ) {
            if ( image.fileName() == item->text() ) {
                this->_images->moveDown ( image );
            }
            selectedItemLabels.append ( item->text() );
        }
    }

    this->_images = new CssSpriteElementImageList ( SpriteWidget::updateCssSprite (
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex()
            ) );

    ui->listWidget->update(this->_images);

    for ( int i = 0; i < ui->listWidget->count(); i++ ) {
        if ( selectedItemLabels.contains ( ui->listWidget->item ( i )->text() ) ) {
            ui->listWidget->item ( i )->setSelected ( true );
            this->on_listWidget_itemPressed ( ui->listWidget->item ( i ) );
        }
    }
}

void MainWindow::on_moveUpToolButton_clicked() {
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();
    QList<QString> selectedItemLabels;

    if ( selectedItems.count() == 0 ) return;

    foreach ( CssSpriteElementImage image, *this->_images ) {
        foreach ( QListWidgetItem * item, selectedItems ) {
            if ( image.fileName() == item->text() ) {
                this->_images->moveUp ( image );
            }
            selectedItemLabels.append ( item->text() );
        }
    }
    this->_images = new CssSpriteElementImageList ( SpriteWidget::updateCssSprite (
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                ( SpriteWidget::Layout ) ui->elementLayoutComboBox->currentIndex()
            ) );

    ui->listWidget->update(this->_images);

    for ( int i = 0; i < ui->listWidget->count(); i++ ) {
        if ( selectedItemLabels.contains ( ui->listWidget->item ( i )->text() ) ) {
            ui->listWidget->item ( i )->setSelected ( true );
            this->on_listWidget_itemPressed ( ui->listWidget->item ( i ) );
        }
    }
}

QString MainWindow::stripFileName ( QString filePath ) {
    return filePath.split ( "/" ).last();
}

void MainWindow::addQualityComboBox() {
    Ui_SpriteFormatSelector * spriteFormatSelector = new Ui_SpriteFormatSelector();
    QWidget * spriteFormatWidget = new QWidget ( this );
    spriteFormatSelector->setupUi ( spriteFormatWidget );

    ui->toolBar->addSeparator();
    ui->toolBar->addWidget ( spriteFormatWidget );
}

SpriteWidget::Format MainWindow::selectedSpriteFormat() {
    return ( SpriteWidget::Format ) this->ui->toolBar->findChild<QComboBox *> ( "qualityComboBox" )->currentIndex();
}

bool MainWindow::readyToExportSprite() {
    bool pureVirtual = true;
    foreach ( CssSpriteElementImage image, * this->_images ) {
        if ( ! ( image.fileState() & CssSpriteElementImage::FILE_VIRTUAL ) ) {
            pureVirtual = false;
            continue;
        }
    }

    if ( pureVirtual ) return true;

    foreach ( CssSpriteElementImage image, * this->_images ) {
        if (
            ! ( image.fileState() & CssSpriteElementImage::FILE_MODIFIED )
            || ! ( image.fileState() & CssSpriteElementImage::FILE_ADDED )
        ) return false;
    }
    return true;
}
