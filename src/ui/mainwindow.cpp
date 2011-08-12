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

    this->statusBar()->addPermanentWidget ( this->_progressBar );
    this->statusBar()->addPermanentWidget ( this->_statusWarningPushButton );

    ui->repeatSettingsInfoWidget->setVisible ( false );

    this->update();
    this->fsWatcher = new QFileSystemWatcher();

    connect ( fsWatcher, SIGNAL ( fileChanged ( QString ) ), SLOT ( onFileChanged ( QString ) ) );
    connect ( ui->spriteSettingsToolBar, SIGNAL(settingsChanged()), SLOT (onSettingsChanged()));
    connect ( ui->spriteQualityToolBar, SIGNAL(qualityChanged()), SLOT (onQualityChanged()));
    connect ( ui->spriteSettingsToolBar, SIGNAL(repeatNeedsAutoChange(bool)), SLOT (onShowAutoChangeForm(bool)));
}

MainWindow::~MainWindow() {
    delete this->_images;
    delete this->_progressBar;
    delete this->ui;
}

void MainWindow::update() {
    ui->actionRemoveFile->setEnabled ( false );
    ui->actionExport->setEnabled ( false );
    ui->actionExportToFilesystem->setEnabled ( false );
    ui->actionSaveCssSprite->setEnabled ( false );
    ui->actionPreview->setEnabled ( false );
    if ( this->_images->count() > 0 ) {
        if ( this->readyToExportSprite() ) {
            ui->actionExport->setEnabled ( true );
            ui->actionSaveCssSprite->setEnabled ( true );
            ui->actionPreview->setEnabled ( true );
        }
        ui->actionRemoveFile->setEnabled ( true );
        ui->actionExportToFilesystem->setEnabled ( true );
    }

    ui->listWidget->update ( this->_images );
    ui->treeWidget->update ( this->_images );

    this->updateSaveRatioProgessBar();
}

void MainWindow::updateSaveRatioProgessBar() {
    int savedBytes = _images->sumOfImageSizes() - SpriteWidget::instance()->resultingFileSize();
    int savedBytesPercent = _images->sumOfImageSizes() == 0 || ((savedBytes * 100) / _images->sumOfImageSizes()) < 0
                            ? 0
                            : (savedBytes * 100) / _images->sumOfImageSizes();

    int savedRequests = _images->count() - 1;
    int savedRequestsPercent = _images->count() == 0 || ((savedRequests * 100) / _images->count()) < 0
                               ? 0
                               : (savedRequests * 100) / _images->count();
    ui->savedBytesRatioProgessBar->setValue(100 - savedBytesPercent);
    ui->savedRequestsRatioProgessBar->setValue(100 - savedRequestsPercent);

    if (_images->size() > 0) {
        ui->savedBytesDescriptionLabel->setText(
            tr ("This sprite will save %n bytes " , "", savedBytes)
            + tr ("and will have  a file size of %n bytes.", "", SpriteWidget::instance()->resultingFileSize())
        );

        ui->savedRequestsDescriptionLabel->setText(
            tr("Instead of requesting %n images, only a single request will be done.", "", savedRequests + 1)
        );
    } else {
        ui->savedBytesDescriptionLabel->setText( tr ("No images available in sprite."));
        ui->savedRequestsDescriptionLabel->setText( tr ("No images available in sprite."));
    }
}

void MainWindow::updateResultingCssTextBrowser(QString fileName) {
    foreach ( CssSpriteElementImage elem, * this->_images ) {
        if ( elem.fileName() == fileName ) {
            ui->fileName->setText ( this->stripFileName ( fileName ) );
            ui->imageSizeX->setText ( QString::number ( elem.description()->size().width(),10 ) + "px" );
            ui->imageSizeY->setText ( QString::number ( elem.description()->size().height(),10 ) + "px" );
            ui->resultingCssTextBrowser->setText (
                "/* " + this->stripFileName ( fileName ) + " */\n"
                + QString ( "background-image: url(<SPRITE URL>);\n" )
                + QString ( "background-repeat: " )
                + ui->spriteSettingsToolBar->repeat()
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

QString MainWindow::stripFileName ( QString filePath ) {
    return filePath.split ( "/" ).last();
}

SpriteWidget::Format MainWindow::selectedSpriteColorDepth() {
    return ( SpriteWidget::Format ) this->ui->spriteQualityToolBar->colorDepth();
}

bool MainWindow::readyToExportSprite() {
    bool pureVirtual = true;
    foreach ( CssSpriteElementImage image, * this->_images ) {
        if ( ! ( image.fileState() & ( CssSpriteElementImage::FILE_VIRTUAL|CssSpriteElementImage::FILE_MODIFIED ) ) ) {
            return false;
        }
    }
    return true;
}

void MainWindow::onFileChanged ( QString path ) {
    QListWidgetItem * item = ui->listWidget->findItems ( path, Qt::MatchExactly ).at ( 0 );
    item->setTextColor ( QColor::fromRgb ( qRgb ( 240,0,0 ) ) );
    QFileInfo fileInfo ( path );
    CssSpriteElementImage * image = this->_images->find ( path );
    if ( image->fileState() == CssSpriteElementImage::FILE_MODIFY ) return;
    if ( fileInfo.exists() ) {
        image->setFileState ( CssSpriteElementImage::FILE_CHANGED );
    } else {
        image->setFileState ( CssSpriteElementImage::FILE_DELETED );
    }
    this->update();
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
                img.setFileState ( CssSpriteElementImage::FILE_VIRTUAL );
                img.setFileName ( stripFileName( dirName ) + "/" + fileName );
                this->_images->append ( img );
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

    this->_images = SpriteWidget::instance()->updateElementImages( this->_images );
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
        CssSpriteElementImage img ( fileName, image );
        if ( !this->_images->contains ( img ) ) {
            img.setFileState ( CssSpriteElementImage::FILE_VIRTUAL );
            img.setFileName ( stripFileName( fileName ) );
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
    this->_images = SpriteWidget::instance()->updateElementImages( this->_images );
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
            delete item;
        }
    }
    this->_images = SpriteWidget::instance()->updateElementImages( this->_images );
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

    SpriteWidget::instance()->exportToFile(fileName);

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

    this->_images = SpriteWidget::instance()->importFromFile(fileName);
    
    ui->spriteSettingsToolBar->ui()->xMarginSpinBox->setValue(SpriteWidget::instance()->elementXMargin());
    ui->spriteSettingsToolBar->ui()->yMarginSpinBox->setValue(SpriteWidget::instance()->elementYMargin());
    ui->spriteSettingsToolBar->ui()->elementLayoutComboBox->setCurrentIndex((int)SpriteWidget::instance()->elementLayout());
    ui->spriteQualityToolBar->ui()->qualityComboBox->setCurrentIndex((int)SpriteWidget::instance()->colorDepth());
    ui->spriteQualityToolBar->ui()->compressionSpinBox->setValue((int)SpriteWidget::instance()->compression());
    this->update();
}

void MainWindow::on_actionExportToFilesystem_triggered() {
    QString dirName = QFileDialog::getExistingDirectory (
                          this,
                          tr ( "Select directory to export files to" ),
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
                "Export to filesystem",
                "Some of the files allready exist. Do you wish to overwrite files on filesystem?",
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

void MainWindow::on_actionSaveCssSprite_triggered() {
    QString fileName = QFileDialog::getSaveFileName (
                           this,
                           tr ( "Save css sprite file" ),
                           "./",
                           "PNG Image (*.png)"
                       );

    if ( fileName.isEmpty() ) return;

    SpriteWidget::instance()->createCssSprite().save ( fileName, "PNG", ui->spriteQualityToolBar->qImageQuality() );
}

void MainWindow::on_actionPreview_triggered() {
    QString dirName = QDir::tempPath();
    if ( dirName.isEmpty() ) return;
    this->createPreviewPage ( dirName );
    SpriteWidget::instance()->createCssSprite().save ( dirName + "/sprite.png", "PNG", ui->spriteQualityToolBar->qImageQuality() );

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
    this->updateResultingCssTextBrowser(fileName);
}

void MainWindow::on_treeWidget_itemPressed ( QTreeWidgetItem * item ) {
    QString fileName;
    while ( item->parent() ) {
        fileName.prepend ( item->text ( 0 ) );
        if ( item->text ( 0 ) != "/" ) fileName.prepend ( "/" );
        item = item->parent();
    }
    fileName.remove ( 0,1 );
    this->updateResultingCssTextBrowser(fileName);
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

void MainWindow::on_changeSettingsButton_clicked() {
    ui->spriteSettingsToolBar->autoChangeSettings();
    ui->repeatSettingsInfoWidget->setVisible ( false );
    ui->resultingCssTextBrowser->setVisible ( true );
    this->on_listWidget_currentItemChanged ( ui->listWidget->currentItem() );
}

void MainWindow::on_abortChangeSettingsButton_clicked() {
    ui->spriteSettingsToolBar->undoRepeatChange();
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

    this->_images = SpriteWidget::instance()->updateElementImages(this->_images);

    ui->listWidget->update ( this->_images );

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
    this->_images = SpriteWidget::instance()->updateElementImages(this->_images);

    ui->listWidget->update ( this->_images );

    for ( int i = 0; i < ui->listWidget->count(); i++ ) {
        if ( selectedItemLabels.contains ( ui->listWidget->item ( i )->text() ) ) {
            ui->listWidget->item ( i )->setSelected ( true );
            this->on_listWidget_itemPressed ( ui->listWidget->item ( i ) );
        }
    }
}

void MainWindow::on_treeWidget_itemMoved() {
    ui->listWidget->clear();
    foreach ( CssSpriteElementImage image, *this->_images ) {
        ui->listWidget->addItem ( image.fileName() );
    }
    this->update();
}

void MainWindow::onSettingsChanged() {
    this->_images = SpriteWidget::instance()->updateElementImages(this->_images);
    SpriteWidget::instance()->setLayout(ui->spriteSettingsToolBar->xMargin(), ui->spriteSettingsToolBar->yMargin(), ui->spriteSettingsToolBar->layout());
    this->on_listWidget_currentItemChanged ( ui->listWidget->currentItem() );

    updateSaveRatioProgessBar();
}

void MainWindow::onQualityChanged() {
    this->_images = SpriteWidget::instance()->updateElementImages(this->_images);
    SpriteWidget::instance()->setFormat(ui->spriteQualityToolBar->colorDepth(), ui->spriteQualityToolBar->compressionLevel());
    this->on_listWidget_currentItemChanged ( ui->listWidget->currentItem() );

    updateSaveRatioProgessBar();
}

void MainWindow::onShowAutoChangeForm(bool show) {
    ui->repeatSettingsInfoWidget->setVisible ( show );
    ui->resultingCssTextBrowser->setVisible ( ! show );
}
