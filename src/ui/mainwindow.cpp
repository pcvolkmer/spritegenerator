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

#include "mainwindow.h"

MainWindow::MainWindow ( QWidget* parent, Qt::WFlags fl )
        : QMainWindow ( parent, fl ), Ui::MainWindow() {
    setupUi ( this );

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

    this->_images = SpriteWidget::updateCssSprite(this->_images, this->marginSpinBox->value());
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

    this->_images = SpriteWidget::updateCssSprite(this->_images, this->marginSpinBox->value());
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
        this->_images =  SpriteWidget::updateCssSprite(this->_images, this->marginSpinBox->value());
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
    SpriteWidget::createCssSprite(this->_images, this->marginSpinBox->value()).save(fileName);
}

void MainWindow::on_previewPageCommandButton_clicked() {
    QString dirName = QDir::tempPath();
    if (dirName.isEmpty()) return;

    QFile htmlFile(dirName + "/index.html");
    htmlFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
    QTextStream out(&htmlFile);
    out << "<!DOCTYPE html>\n";
    out << "<html lang=\"de-DE\">\n<head>\n<meta charset=\"UTF-8\"/>\n<title>Preview</title>\n<style type=\"text/css\">\n";
    out << "body { margin: 24px; background-color: #DDD; font-family: sans-serif; }\n";
    out << "b { margin: 8px; display: block; }\n";
    out << ".style { border: 1px solid gray; background-color: #FFF; color: #333; margin: 2px; padding: 8px; ";
    out << "-moz-border-radius: 8px; -webkit-border-radius: 8px; }\n";
    out << ".style:hover { background-color: #FFC; ";
    out << "-moz-box-shadow:0 0 2px gray; -webkit-box-shadow:0 0 2px gray; }\n";
    foreach (CssSpriteElementImage elem, *this->_images) {
        out << ".style_" << QCryptographicHash::hash(
            elem.fileName().toUtf8(),
            QCryptographicHash::Md5
        ).toHex() << " {";
        out << " background: url(sprite.png) no-repeat; ";
        out << "background-position: -" << elem.description()->startPosition().x() << "px -";
        out << elem.description()->startPosition().y() << "px; ";
        out << "width: " << elem.description()->size().width() << "px; ";
        out << "height: " << elem.description()->size().height() << "px; ";
        out << "}\n";
    }
    out << "</style>\n</head>\n";
    out << "<body>\n";
    QString versionText = "SpriteGenerator "
                          + QString::number ( VERSION_MAJOR,10 )
                          + "." + QString::number ( VERSION_MINOR,10 )
                          + "." + QString::number ( VERSION_RELEASE,10 );
    out << "<b>" << "This is a preview page created with " << versionText << "</b>\n";
    foreach (CssSpriteElementImage elem, * this->_images) {
        out << "<div class=\"style\"\n>";
        out << "<div class=\"style_" << QCryptographicHash::hash(elem.fileName().toUtf8(),QCryptographicHash::Md5).toHex() << "\">";
        out << "</div>\n";
        out << "<pre>\n";
        out << ".style_" << QCryptographicHash::hash(
            elem.fileName().toUtf8(),
            QCryptographicHash::Md5
        ).toHex() << " {\n";
        out << "  background: url(sprite.png) no-repeat;\n";
        out << "  background-position: -" << elem.description()->startPosition().x() << "px -";
        out << elem.description()->startPosition().y() << "px;\n";
        out << "  width: " << elem.description()->size().width() << "px;\n";
        out << "  height: " << elem.description()->size().height() << "px;\n";
        out << "}\n";
        out << "</pre>\n";
        out << "</div>\n";
    }
    out << "</body>\n";
    out << "</html>";
    htmlFile.flush();
    htmlFile.close();

    SpriteWidget::createCssSprite(this->_images, this->marginSpinBox->value()).save(dirName + "/sprite.png");
	
    #ifdef WIN32
    QDesktopServices::openUrl(QUrl("file:///" + dirName + "/index.html"));
    #else
    QDesktopServices::openUrl(QUrl("file://" + dirName + "/index.html"));
    #endif
}

void MainWindow::on_listWidget_itemPressed(QListWidgetItem * item) {
    QString fileName = item->text();

    foreach (CssSpriteElementImage elem, * this->_images) {
        if (elem.fileName() == fileName) {
            this->fileName->setText(this->stripFileName(fileName));
            this->imageSizeX->setText(QString::number(elem.description()->size().width(),10) + "px");
            this->imageSizeY->setText(QString::number(elem.description()->size().height(),10) + "px");
            this->resultingCssTextBrowser->setText(
                "background: url(<SPRITE URL>) no-repeat;\nbackground-position: -"
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

void MainWindow::on_marginSpinBox_valueChanged(int i) {
    this->_images =  SpriteWidget::updateCssSprite(this->_images, this->marginSpinBox->value());
    this->on_listWidget_currentItemChanged(this->listWidget->currentItem());
}
