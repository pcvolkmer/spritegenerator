/********************************************************************************
** Form generated from reading UI file 'infoDialog.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFODIALOG_H
#define UI_INFODIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfoDialog
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *versionLabel;
    QTabWidget *infoWidget;
    QWidget *aboutTab;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *licenseLabel;
    QWidget *licenseTab;
    QGridLayout *gridLayout;
    QTextBrowser *licenseBrowser;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *closeButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *InfoDialog)
    {
        if (InfoDialog->objectName().isEmpty())
            InfoDialog->setObjectName(QString::fromUtf8("InfoDialog"));
        InfoDialog->resize(600, 308);
        InfoDialog->setMinimumSize(QSize(600, 308));
        InfoDialog->setMaximumSize(QSize(600, 308));
        InfoDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        InfoDialog->setSizeGripEnabled(false);
        gridLayout_3 = new QGridLayout(InfoDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(InfoDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(40, 40));
        label_2->setMaximumSize(QSize(40, 40));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/images/spritegenerator.svg")));
        label_2->setScaledContents(true);
        label_2->setMargin(4);

        horizontalLayout_3->addWidget(label_2);

        versionLabel = new QLabel(InfoDialog);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        versionLabel->setFont(font);
        versionLabel->setMargin(10);

        horizontalLayout_3->addWidget(versionLabel);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        infoWidget = new QTabWidget(InfoDialog);
        infoWidget->setObjectName(QString::fromUtf8("infoWidget"));
        aboutTab = new QWidget();
        aboutTab->setObjectName(QString::fromUtf8("aboutTab"));
        gridLayout_2 = new QGridLayout(aboutTab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(aboutTab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label->setMargin(20);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 24, -1);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        licenseLabel = new QLabel(aboutTab);
        licenseLabel->setObjectName(QString::fromUtf8("licenseLabel"));
        licenseLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/images/gplv3-88x31.png")));

        horizontalLayout_2->addWidget(licenseLabel);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        infoWidget->addTab(aboutTab, QString());
        licenseTab = new QWidget();
        licenseTab->setObjectName(QString::fromUtf8("licenseTab"));
        gridLayout = new QGridLayout(licenseTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        licenseBrowser = new QTextBrowser(licenseTab);
        licenseBrowser->setObjectName(QString::fromUtf8("licenseBrowser"));
        licenseBrowser->setAutoFormatting(QTextEdit::AutoNone);
        licenseBrowser->setLineWrapMode(QTextEdit::NoWrap);
        licenseBrowser->setAcceptRichText(true);
        licenseBrowser->setTextInteractionFlags(Qt::NoTextInteraction);

        gridLayout->addWidget(licenseBrowser, 0, 0, 1, 1);

        infoWidget->addTab(licenseTab, QString());

        gridLayout_3->addWidget(infoWidget, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 4);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeButton = new QPushButton(InfoDialog);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout->addWidget(closeButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(InfoDialog);

        infoWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InfoDialog);
    } // setupUi

    void retranslateUi(QDialog *InfoDialog)
    {
        InfoDialog->setWindowTitle(QApplication::translate("InfoDialog", "About DataSetEditor", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        versionLabel->setText(QApplication::translate("InfoDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:8pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">SpriteGenerator</p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("InfoDialog", "SpriteGenerator is a simple generator for CSS sprites.\n"
"\n"
"Copyright (c) 2010  Paul-Christian Volkmer", 0, QApplication::UnicodeUTF8));
        licenseLabel->setText(QString());
        infoWidget->setTabText(infoWidget->indexOf(aboutTab), QApplication::translate("InfoDialog", "About", 0, QApplication::UnicodeUTF8));
        infoWidget->setTabText(infoWidget->indexOf(licenseTab), QApplication::translate("InfoDialog", "License", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("InfoDialog", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InfoDialog: public Ui_InfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFODIALOG_H
