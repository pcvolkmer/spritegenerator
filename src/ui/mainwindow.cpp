/***************************************************************************
 *   Copyright (C) 2011  Paul-Christian Volkmer
 *   paul-christian.volkmer@mni.th-mittelhessen.de
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
        : QMainWindow ( parent, fl ), ui(new Ui::MainWindow()) {
    this->_progressBar = new QProgressBar();

    this->_statusWarningPushButton = new QPushButton();
    this->_statusWarningPushButton->setIcon(QIcon(":images/images/16x16/dialog-warning.png"));
    this->_statusWarningPushButton->setEnabled(false);

    this->_images = new CssSpriteElementImageList();

    ui->setupUi ( this );

    this->addQualityComboBox();
    this->statusBar()->addPermanentWidget(this->_progressBar);
    this->statusBar()->addPermanentWidget(this->_statusWarningPushButton);

    ui->repeatSettingsInfoWidget->setVisible(false);

    ui->listWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    foreach(QAction * action, ui->toolBar->actions()) {
        if (! (action->text() == NULL)) {
            ui->listWidget->addAction(action);
        }
    }

    ui->actionRemoveFile->setEnabled(false);
    ui->createSpriteCommandButton->setEnabled(false);
    ui->previewPageCommandButton->setEnabled(false);
}

MainWindow::~MainWindow() {
    delete this->_images;
    delete this->_qualityComboBox;
    delete this->_qualityLabel;
    delete this->_progressBar;
    delete this->ui;
}

void MainWindow::updateListWidget() {
    ui->actionRemoveFile->setEnabled(false);
    ui->createSpriteCommandButton->setEnabled(false);
    ui->previewPageCommandButton->setEnabled(false);
    if (ui->listWidget->count() > 0) {
        ui->actionRemoveFile->setEnabled(true);
        ui->createSpriteCommandButton->setEnabled(true);
        ui->previewPageCommandButton->setEnabled(true);
    }
}

void MainWindow::on_actionAddDirectory_triggered() {
    QString dirName = QFileDialog::getExistingDirectory(
                          this,
                          tr ( "Add directory" ),
                          "./",
                          QFileDialog::ReadOnly
                      );
    if (dirName.isEmpty()) return;
    this->statusBar()->clearMessage();
    this->setCursor(Qt::WaitCursor);
    QDir directory(dirName);
    this->_progressBar->setMinimum(0);
    this->_progressBar->setMaximum(directory.count()-1);

    int importCounter = 0;
    int failCounter = 0;
    foreach (QString fileName, directory.entryList()) {
        QFileInfo fileInfo(dirName + "/" + fileName);
        this->_progressBar->setValue(this->_progressBar->value()+1);
        if (fileInfo.isDir()) continue;
        QImage image(dirName + "/" + fileName);

        if (!image.isNull()) {
            CssSpriteElementImage img(dirName + "/" + fileName,image);
            if (!this->_images->contains(img)) {
                this->_images->append(img);
                ui->listWidget->addItem(dirName + "/" + fileName);
            }
            importCounter++;
        }
        else {
            failCounter++;
        }
    }

    if ((importCounter > 0) && (failCounter == 0)) {
        this->statusBar()->showMessage(
            tr("Import of %n image(s) succeed.","",importCounter),
            15000
        );
    }
    if ((importCounter == 0) && (failCounter > 0)) {
        this->statusBar()->showMessage(
            tr("No usable images were found."),
            15000
        );
    }
    if ((importCounter > 0) && (failCounter > 0)) {
        this->statusBar()->showMessage(
            tr("Import of %n image(s) succeed, ","",importCounter)
            + tr("import of %n file(s) failed. ","",failCounter),
            15000
        );
    }

    this->_images = new CssSpriteElementImageList(
        SpriteWidget::updateCssSprite(
            this->_images,
            ui->xMarginSpinBox->value(),
            ui->yMarginSpinBox->value(),
            (SpriteWidget::Layout) ui->elementLayoutComboBox->currentIndex()
        )
    );
    this->_progressBar->reset();
    this->setCursor(Qt::ArrowCursor);
    this->updateListWidget();
}

void MainWindow::on_actionAddFile_triggered() {
    QString fileName = QFileDialog::getOpenFileName(
                           this,
                           tr ( "Add file" ),
                           "./"
                       );
    if (fileName.isEmpty()) return;
    this->statusBar()->clearMessage();
    this->setCursor(Qt::WaitCursor);
    QImage image(fileName);
    if (!image.isNull()) {
        CssSpriteElementImage img(fileName,image);
        if (!this->_images->contains(img)) {
            this->_images->append(img);
            ui->listWidget->addItem(fileName);
        }
        this->statusBar()->showMessage(
            tr("Import of 1 image succeed."),
            10000
        );
    }
    else {
        this->statusBar()->showMessage(
            tr("Could not import file: Not a useable image format."),
            10000
        );
    }
    this->_images = new CssSpriteElementImageList(SpriteWidget::updateCssSprite(
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                (SpriteWidget::Layout) ui->elementLayoutComboBox->currentIndex()
            ));
    this->setCursor(Qt::ArrowCursor);
    this->updateListWidget();
}

void MainWindow::on_actionRemoveFile_triggered() {
    QList<QListWidgetItem*> itemlist = ui->listWidget->selectedItems();
    foreach (QListWidgetItem * item, itemlist) {
        foreach (CssSpriteElementImage image, *this->_images) {
            if (image.fileName() == item->text()) {
                this->_images->removeOne(image);
            }
        }
        this->_images = new CssSpriteElementImageList(SpriteWidget::updateCssSprite(
                    this->_images,
                    ui->xMarginSpinBox->value(),
                    ui->yMarginSpinBox->value(),
                    (SpriteWidget::Layout) ui->elementLayoutComboBox->currentIndex()
                ));
        delete item;
    }
    this->updateListWidget();
}

void MainWindow::on_createSpriteCommandButton_clicked() {
    QString fileName = QFileDialog::getSaveFileName(
                           this,
                           tr ( "Save css sprite file" ),
                           "./",
                           "PNG Image (*.png)"
                       );
    if (fileName.isEmpty()) return;
    SpriteWidget::createCssSprite(
        this->_images,
        ui->xMarginSpinBox->value(),
        ui->yMarginSpinBox->value(),
        (SpriteWidget::Layout) ui->elementLayoutComboBox->currentIndex(),
        (SpriteWidget::Format) this->_qualityComboBox->currentIndex()
    ).save(fileName);
}

void MainWindow::on_previewPageCommandButton_clicked() {
    QString dirName = QDir::tempPath();
    if (dirName.isEmpty()) return;
    this->createPreviewPage(dirName);
    SpriteWidget::createCssSprite(
        this->_images,
        ui->xMarginSpinBox->value(),
        ui->yMarginSpinBox->value(),
        (SpriteWidget::Layout) ui->elementLayoutComboBox->currentIndex(),
        (SpriteWidget::Format) this->_qualityComboBox->currentIndex()
    ).save(dirName + "/sprite.png");

#ifdef WIN32
    QDesktopServices::openUrl(QUrl("file:///" + dirName + "/index.html"));
#else
    QDesktopServices::openUrl(QUrl("file://" + dirName + "/index.html"));
#endif
}

bool MainWindow::createPreviewPage(QString dirName) {
    QFile htmlFile(dirName + "/index.html");
    htmlFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
    if (!htmlFile.isWritable()) return false;

    htmlFile.write(PreviewPage::create(*this->_images));

    htmlFile.close();
    return true;
}

void MainWindow::on_listWidget_itemPressed(QListWidgetItem * item) {
    QString fileName = item->text();

    foreach (CssSpriteElementImage elem, * this->_images) {
        if (elem.fileName() == fileName) {
            ui->fileName->setText(this->stripFileName(fileName));
            ui->imageSizeX->setText(QString::number(elem.description()->size().width(),10) + "px");
            ui->imageSizeY->setText(QString::number(elem.description()->size().height(),10) + "px");
            ui->resultingCssTextBrowser->setText(
                "/* " + this->stripFileName(fileName) + " */\n"
                + QString("background-image: url(<SPRITE URL>);\n")
                + QString("background-repeat: ")
                + ui->spriteRepeatComboBox->currentText()
                + ";\nbackground-position: -"
                + QString::number(elem.description()->startPosition().x(),10)
                + "px -"
                + QString::number(elem.description()->startPosition().y(),10)
                + "px;\n"
                + "width: "
                + QString::number(elem.description()->size().width(),10)
                + "px;\nheight: "
                + QString::number(elem.description()->size().height(),10)
                + "px;"
            );
            ui->elementImageLabel->setPixmap(QPixmap::fromImage(elem.image()));
            return;
        }
    }
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem* item) {
    ui->fileName->clear();
    ui->imageSizeX->clear();
    ui->imageSizeY->clear();
    ui->resultingCssTextBrowser->clear();
    ui->elementImageLabel->clear();
    if (item == NULL) return;
    this->on_listWidget_itemPressed(item);
}

void MainWindow::on_actionInfo_triggered() {
    InfoDialog infoDialog;
    infoDialog.exec();
}

void MainWindow::on_xMarginSpinBox_valueChanged(int i) {
    if (
        ui->lockMarginToolButton->isChecked()
        && (ui->spriteRepeatComboBox->currentIndex() != (int)SpriteWidget::REPEAT_REPEAT_Y)
    ) {
        ui->yMarginSpinBox->setValue(ui->xMarginSpinBox->value());
    }

    this->_images = new CssSpriteElementImageList(SpriteWidget::updateCssSprite(
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                (SpriteWidget::Layout) ui->elementLayoutComboBox->currentIndex()
            ));
    this->on_listWidget_currentItemChanged(ui->listWidget->currentItem());
}

void MainWindow::on_yMarginSpinBox_valueChanged(int i) {
    this->_images = new CssSpriteElementImageList(SpriteWidget::updateCssSprite(
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                (SpriteWidget::Layout) ui->elementLayoutComboBox->currentIndex()
            ));
    this->on_listWidget_currentItemChanged(ui->listWidget->currentItem());
}

void MainWindow::on_elementLayoutComboBox_currentIndexChanged(int index) {
    this->_images = new CssSpriteElementImageList(SpriteWidget::updateCssSprite(
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                (SpriteWidget::Layout) index
            ));
    this->on_listWidget_currentItemChanged(ui->listWidget->currentItem());
}

// Refacs!

void MainWindow::on_spriteRepeatComboBox_currentIndexChanged(int index) {
    ui->repeatSettingsInfoWidget->setVisible(false);
    ui->resultingCssTextBrowser->setVisible(true);
    ui->lockMarginToolButton->setEnabled(true);
    ui->elementLayoutComboBox->setEnabled(true);

    if ((index == (int)SpriteWidget::REPEAT_REPEAT_X) || (index == (int)SpriteWidget::REPEAT_REPEAT_Y)) {
        ui->repeatSettingsInfoWidget->setVisible(true);
        ui->resultingCssTextBrowser->setVisible(false);
        ui->lockMarginToolButton->setEnabled(false);
    }

    if (index == (int) SpriteWidget::REPEAT_NO_REPEAT) {
        ui->xMarginSpinBox->setEnabled(true);
        ui->yMarginSpinBox->setEnabled(! ui->lockMarginToolButton->isChecked());
    }
}

void MainWindow::on_lockMarginToolButton_toggled(bool checked) {
    ui->yMarginSpinBox->setEnabled(!checked);
    ui->yMarginSpinBox->setValue(ui->xMarginSpinBox->value());
}

void MainWindow::on_changeSettingsButton_clicked() {
    int repeatIndex = ui->spriteRepeatComboBox->currentIndex();

    if (repeatIndex == (int)SpriteWidget::REPEAT_REPEAT_X) {
        ui->xMarginSpinBox->setEnabled(false);
        ui->yMarginSpinBox->setEnabled(true);
        ui->xMarginSpinBox->setValue(0);
        ui->elementLayoutComboBox->setCurrentIndex((int)SpriteWidget::LAYOUT_VERTICAL);
    }
    else if (repeatIndex == (int)SpriteWidget::REPEAT_REPEAT_Y) {
        ui->xMarginSpinBox->setEnabled(true);
        ui->yMarginSpinBox->setEnabled(false);
        ui->yMarginSpinBox->setValue(0);
        ui->elementLayoutComboBox->setCurrentIndex((int)SpriteWidget::LAYOUT_HORIZONTAL);
    }

    ui->elementLayoutComboBox->setEnabled(false);

    this->on_abortChangeSettingsButton_clicked();
}

void MainWindow::on_abortChangeSettingsButton_clicked() {
    ui->repeatSettingsInfoWidget->setVisible(false);
    ui->resultingCssTextBrowser->setVisible(true);
    this->on_listWidget_currentItemChanged(ui->listWidget->currentItem());
}

void MainWindow::on_moveDownToolButton_clicked() {
    foreach(QListWidgetItem * item, ui->listWidget->selectedItems()) {
        foreach(CssSpriteElementImage image, *this->_images) {
            if (image.fileName() == item->text()) {
                this->_images->moveDown(image);
            }
        }
    }
    ui->listWidget->clear();
    foreach(CssSpriteElementImage image, *this->_images) {
        ui->listWidget->addItem(image.fileName());
    }
    this->_images = new CssSpriteElementImageList(SpriteWidget::updateCssSprite(
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                (SpriteWidget::Layout) ui->elementLayoutComboBox->currentIndex()
            ));
    this->updateListWidget();
}

void MainWindow::on_moveUpToolButton_clicked() {
    foreach(QListWidgetItem * item, ui->listWidget->selectedItems()) {
        foreach(CssSpriteElementImage image, *this->_images) {
            if (image.fileName() == item->text()) {
                this->_images->moveUp(image);
            }
        }
    }
    ui->listWidget->clear();
    foreach(CssSpriteElementImage image, *this->_images) {
        ui->listWidget->addItem(image.fileName());
    }
    this->_images = new CssSpriteElementImageList(SpriteWidget::updateCssSprite(
                this->_images,
                ui->xMarginSpinBox->value(),
                ui->yMarginSpinBox->value(),
                (SpriteWidget::Layout) ui->elementLayoutComboBox->currentIndex()
            ));
    this->updateListWidget();
}

QString MainWindow::stripFileName(QString filePath) {
    return filePath.split("/").last();
}

void MainWindow::addQualityComboBox() {
    ui->toolBar->addSeparator();
    this->_qualityLabel = new QLabel(tr("Sprite format"));
    ui->toolBar->addWidget(this->_qualityLabel);
    this->_qualityComboBox = new QComboBox();
    this->_qualityComboBox->addItem(tr("32 bit RGBA (best quality)"));
    this->_qualityComboBox->addItem(tr("24 bit RGBA"));
    this->_qualityComboBox->addItem(tr("16 bit RGBA"));
    this->_qualityComboBox->addItem(tr("8 bit indexed (smallest file size)"));
    ui->toolBar->addWidget(this->_qualityComboBox);
}
