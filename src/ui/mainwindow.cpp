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

#include "mainwindow.h"

MainWindow::MainWindow ( QWidget* parent, Qt::WFlags fl )
        : QMainWindow ( parent, fl ), Ui::MainWindow() {
    setupUi ( this );

    this->repeatSettingsInfoWidget->setVisible(false);

    this->listWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    this->listWidget->addActions(this->toolBar->actions());

    this->actionRemoveFile->setEnabled(false);
    this->createSpriteCommandButton->setEnabled(false);
    this->previewPageCommandButton->setEnabled(false);

    this->_images = new QList< CssSpriteElementImage >();
}

MainWindow::~MainWindow() {
    delete this->_images;
}

void MainWindow::updateListWidget() {
    this->actionRemoveFile->setEnabled(false);
    this->createSpriteCommandButton->setEnabled(false);
    this->previewPageCommandButton->setEnabled(false);
    if (this->listWidget->count() > 0) {
        this->actionRemoveFile->setEnabled(true);
        this->createSpriteCommandButton->setEnabled(true);
        this->previewPageCommandButton->setEnabled(true);
    }
}

void MainWindow::on_actionAddDirectory_triggered() {
    QString dirName = QFileDialog::getExistingDirectory(
                          this,
                          tr ( "Add directory" ),
                          "./",
                          QFileDialog::ReadOnly
                      );
    this->setCursor(Qt::WaitCursor);
    QDir directory(dirName);
    foreach (QString fileName, directory.entryList()) {
        QImage image(dirName + "/" + fileName);
        if (!image.isNull()) {
            CssSpriteElementImage img(dirName + "/" + fileName,image);
            if (!this->_images->contains(img)) {
                this->_images->append(img);
                this->listWidget->addItem(dirName + "/" + fileName);
            }
        }
    }

    this->_images = SpriteWidget::updateCssSprite(
                        this->_images,
                        this->xMarginSpinBox->value(),
                        this->yMarginSpinBox->value(),
                        (SpriteWidget::Layout) this->elementLayoutComboBox->currentIndex()
                    );
    this->setCursor(Qt::ArrowCursor);
    this->updateListWidget();
}

void MainWindow::on_actionAddFile_triggered() {
    QString fileName = QFileDialog::getOpenFileName(
                           this,
                           tr ( "Add file" ),
                           "./"
                       );

    this->setCursor(Qt::WaitCursor);
    QImage image(fileName);
    if (!image.isNull()) {
        CssSpriteElementImage img(fileName,image);
        if (!this->_images->contains(img)) {
            this->_images->append(img);
            this->listWidget->addItem(fileName);
        }
    }

    this->_images = SpriteWidget::updateCssSprite(
                        this->_images,
                        this->xMarginSpinBox->value(),
                        this->yMarginSpinBox->value(),
                        (SpriteWidget::Layout) this->elementLayoutComboBox->currentIndex()
                    );
    this->setCursor(Qt::ArrowCursor);
    this->updateListWidget();
}

void MainWindow::on_actionRemoveFile_triggered() {
    QList<QListWidgetItem*> itemlist = this->listWidget->selectedItems();
    foreach (QListWidgetItem * item, itemlist) {
        foreach (CssSpriteElementImage image, *this->_images) {
            if (image.fileName() == item->text()) {
                this->_images->removeOne(image);
            }
        }
        this->_images = SpriteWidget::updateCssSprite(
                            this->_images,
                            this->xMarginSpinBox->value(),
                            this->yMarginSpinBox->value(),
                            (SpriteWidget::Layout) this->elementLayoutComboBox->currentIndex()
                        );
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
        this->xMarginSpinBox->value(),
        this->yMarginSpinBox->value(),
        (SpriteWidget::Layout) this->elementLayoutComboBox->currentIndex()
    ).save(fileName);
}

void MainWindow::on_previewPageCommandButton_clicked() {
    QString dirName = QDir::tempPath();
    if (dirName.isEmpty()) return;
    this->createPreviewPage(dirName);
    SpriteWidget::createCssSprite(
        this->_images,
        this->xMarginSpinBox->value(),
        this->yMarginSpinBox->value(),
        (SpriteWidget::Layout) this->elementLayoutComboBox->currentIndex()
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
            this->fileName->setText(this->stripFileName(fileName));
            this->imageSizeX->setText(QString::number(elem.description()->size().width(),10) + "px");
            this->imageSizeY->setText(QString::number(elem.description()->size().height(),10) + "px");
            this->resultingCssTextBrowser->setText(
                "background-image: url(<SPRITE URL>);\n"
                + QString("background-repeat: ")
                + this->spriteRepeatComboBox->currentText()
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
            this->elementImageLabel->setPixmap(QPixmap::fromImage(elem.image()));
            return;
        }
    }
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem* item) {
    this->fileName->clear();
    this->imageSizeX->clear();
    this->imageSizeY->clear();
    this->resultingCssTextBrowser->clear();
    this->elementImageLabel->clear();
    if (item == NULL) return;
    this->on_listWidget_itemPressed(item);
}

void MainWindow::on_actionInfo_triggered() {
    InfoDialog infoDialog;
    infoDialog.exec();
}

void MainWindow::on_xMarginSpinBox_valueChanged(int i) {
    if (
        this->lockMarginToolButton->isChecked()
        && (this->spriteRepeatComboBox->currentIndex() != (int)SpriteWidget::REPEAT_REPEAT_Y)
    ) {
        this->yMarginSpinBox->setValue(this->xMarginSpinBox->value());
    }

    this->_images = SpriteWidget::updateCssSprite(
                        this->_images,
                        this->xMarginSpinBox->value(),
                        this->yMarginSpinBox->value(),
                        (SpriteWidget::Layout) this->elementLayoutComboBox->currentIndex()
                    );
    this->on_listWidget_currentItemChanged(this->listWidget->currentItem());
}

void MainWindow::on_yMarginSpinBox_valueChanged(int i) {
    this->_images = SpriteWidget::updateCssSprite(
                        this->_images,
                        this->xMarginSpinBox->value(),
                        this->yMarginSpinBox->value(),
                        (SpriteWidget::Layout) this->elementLayoutComboBox->currentIndex()
                    );
    this->on_listWidget_currentItemChanged(this->listWidget->currentItem());
}

void MainWindow::on_elementLayoutComboBox_currentIndexChanged(int index) {
    this->_images = SpriteWidget::updateCssSprite(
                        this->_images,
                        this->xMarginSpinBox->value(),
                        this->yMarginSpinBox->value(),
                        (SpriteWidget::Layout) index
                    );
    this->on_listWidget_currentItemChanged(this->listWidget->currentItem());
}

// Refacs!

void MainWindow::on_spriteRepeatComboBox_currentIndexChanged(int index) {
    this->repeatSettingsInfoWidget->setVisible(false);
    this->resultingCssTextBrowser->setVisible(true);
    this->lockMarginToolButton->setEnabled(true);
    this->elementLayoutComboBox->setEnabled(true);

    if ((index == (int)SpriteWidget::REPEAT_REPEAT_X) || (index == (int)SpriteWidget::REPEAT_REPEAT_Y)) {
        this->repeatSettingsInfoWidget->setVisible(true);
        this->resultingCssTextBrowser->setVisible(false);
        this->lockMarginToolButton->setEnabled(false);
    }

    if (index == (int) SpriteWidget::REPEAT_NO_REPEAT) {
        this->xMarginSpinBox->setEnabled(true);
        this->yMarginSpinBox->setEnabled(!this->lockMarginToolButton->isChecked());
    }
}

void MainWindow::on_lockMarginToolButton_toggled(bool checked) {
    this->yMarginSpinBox->setEnabled(!checked);
    this->yMarginSpinBox->setValue(this->xMarginSpinBox->value());
}

void MainWindow::on_changeSettingsButton_clicked() {
    int repeatIndex = this->spriteRepeatComboBox->currentIndex();

    if (repeatIndex == (int)SpriteWidget::REPEAT_REPEAT_X) {
        this->xMarginSpinBox->setEnabled(false);
        this->yMarginSpinBox->setEnabled(true);
        this->xMarginSpinBox->setValue(0);
        this->elementLayoutComboBox->setCurrentIndex((int)SpriteWidget::LAYOUT_VERTICAL);
    }
    else if (repeatIndex == (int)SpriteWidget::REPEAT_REPEAT_Y) {
        this->xMarginSpinBox->setEnabled(true);
        this->yMarginSpinBox->setEnabled(false);
        this->yMarginSpinBox->setValue(0);
        this->elementLayoutComboBox->setCurrentIndex((int)SpriteWidget::LAYOUT_HORIZONTAL);
    }

    this->elementLayoutComboBox->setEnabled(false);

    this->repeatSettingsInfoWidget->setVisible(false);
    this->resultingCssTextBrowser->setVisible(true);
    this->on_listWidget_currentItemChanged(this->listWidget->currentItem());
}

void MainWindow::on_abortChangeSettingsButton_clicked() {
    this->repeatSettingsInfoWidget->setVisible(false);
    this->resultingCssTextBrowser->setVisible(true);
    this->on_listWidget_currentItemChanged(this->listWidget->currentItem());
}

QString MainWindow::stripFileName(QString filePath) {
    return filePath.split("/").last();
}
