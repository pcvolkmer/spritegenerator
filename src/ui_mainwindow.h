/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAddFile;
    QAction *actionAddDirectory;
    QAction *actionRemoveFile;
    QAction *actionInfo;
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QCommandLinkButton *createSpriteCommandButton;
    QCommandLinkButton *previewPageCommandButton;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QHBoxLayout *imageNameHorizontalLayout_2;
    QLabel *label_4;
    QSpinBox *marginSpinBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *imageNameHorizontalLayout;
    QLabel *label;
    QLineEdit *fileName;
    QHBoxLayout *imageSizeHorizontalLayout;
    QLabel *label_2;
    QLineEdit *imageSizeX;
    QLabel *label_3;
    QLineEdit *imageSizeY;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *elementImageLabel;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTextBrowser *resultingCssTextBrowser;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(699, 811);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/spritegenerator.svg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionAddFile = new QAction(MainWindow);
        actionAddFile->setObjectName(QString::fromUtf8("actionAddFile"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/22x22/archive-insert.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddFile->setIcon(icon1);
        actionAddDirectory = new QAction(MainWindow);
        actionAddDirectory->setObjectName(QString::fromUtf8("actionAddDirectory"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/22x22/archive-insert-directory.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddDirectory->setIcon(icon2);
        actionRemoveFile = new QAction(MainWindow);
        actionRemoveFile->setObjectName(QString::fromUtf8("actionRemoveFile"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/22x22/archive-remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemoveFile->setIcon(icon3);
        actionInfo = new QAction(MainWindow);
        actionInfo->setObjectName(QString::fromUtf8("actionInfo"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setAlternatingRowColors(true);
        listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        listWidget->setSortingEnabled(true);

        gridLayout_4->addWidget(listWidget, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        createSpriteCommandButton = new QCommandLinkButton(centralwidget);
        createSpriteCommandButton->setObjectName(QString::fromUtf8("createSpriteCommandButton"));
        createSpriteCommandButton->setMaximumSize(QSize(340, 16777215));

        verticalLayout->addWidget(createSpriteCommandButton);

        previewPageCommandButton = new QCommandLinkButton(centralwidget);
        previewPageCommandButton->setObjectName(QString::fromUtf8("previewPageCommandButton"));
        previewPageCommandButton->setEnabled(true);
        previewPageCommandButton->setMaximumSize(QSize(340, 16777215));

        verticalLayout->addWidget(previewPageCommandButton);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_5 = new QGridLayout(groupBox_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        imageNameHorizontalLayout_2 = new QHBoxLayout();
        imageNameHorizontalLayout_2->setObjectName(QString::fromUtf8("imageNameHorizontalLayout_2"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(100, 0));
        label_4->setMaximumSize(QSize(100, 16777215));

        imageNameHorizontalLayout_2->addWidget(label_4);

        marginSpinBox = new QSpinBox(groupBox_3);
        marginSpinBox->setObjectName(QString::fromUtf8("marginSpinBox"));
        marginSpinBox->setMaximum(80);
        marginSpinBox->setValue(8);

        imageNameHorizontalLayout_2->addWidget(marginSpinBox);


        gridLayout_5->addLayout(imageNameHorizontalLayout_2, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(340, 16777215));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        imageNameHorizontalLayout = new QHBoxLayout();
        imageNameHorizontalLayout->setObjectName(QString::fromUtf8("imageNameHorizontalLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(100, 0));
        label->setMaximumSize(QSize(100, 16777215));

        imageNameHorizontalLayout->addWidget(label);

        fileName = new QLineEdit(groupBox_2);
        fileName->setObjectName(QString::fromUtf8("fileName"));
        fileName->setReadOnly(true);

        imageNameHorizontalLayout->addWidget(fileName);


        gridLayout_3->addLayout(imageNameHorizontalLayout, 0, 0, 1, 1);

        imageSizeHorizontalLayout = new QHBoxLayout();
        imageSizeHorizontalLayout->setObjectName(QString::fromUtf8("imageSizeHorizontalLayout"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(100, 0));
        label_2->setMaximumSize(QSize(100, 16777215));

        imageSizeHorizontalLayout->addWidget(label_2);

        imageSizeX = new QLineEdit(groupBox_2);
        imageSizeX->setObjectName(QString::fromUtf8("imageSizeX"));
        imageSizeX->setReadOnly(true);

        imageSizeHorizontalLayout->addWidget(imageSizeX);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        imageSizeHorizontalLayout->addWidget(label_3);

        imageSizeY = new QLineEdit(groupBox_2);
        imageSizeY->setObjectName(QString::fromUtf8("imageSizeY"));
        imageSizeY->setReadOnly(true);

        imageSizeHorizontalLayout->addWidget(imageSizeY);


        gridLayout_3->addLayout(imageSizeHorizontalLayout, 1, 0, 1, 1);

        scrollArea = new QScrollArea(groupBox_2);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(320, 240));
        scrollArea->setMaximumSize(QSize(320, 240));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 314, 234));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        elementImageLabel = new QLabel(scrollAreaWidgetContents);
        elementImageLabel->setObjectName(QString::fromUtf8("elementImageLabel"));
        elementImageLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(elementImageLabel, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(scrollArea, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(340, 16777215));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        resultingCssTextBrowser = new QTextBrowser(groupBox);
        resultingCssTextBrowser->setObjectName(QString::fromUtf8("resultingCssTextBrowser"));
        QFont font;
        font.setFamily(QString::fromUtf8("Monospace"));
        resultingCssTextBrowser->setFont(font);

        gridLayout_2->addWidget(resultingCssTextBrowser, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout_4->addLayout(verticalLayout, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 699, 19));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMovable(false);
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionAddFile);
        menuFile->addAction(actionAddDirectory);
        menuFile->addAction(actionRemoveFile);
        menuHelp->addAction(actionInfo);
        toolBar->addAction(actionAddFile);
        toolBar->addAction(actionAddDirectory);
        toolBar->addAction(actionRemoveFile);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SpriteGenerator", 0, QApplication::UnicodeUTF8));
        actionAddFile->setText(QApplication::translate("MainWindow", "Add File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAddFile->setToolTip(QApplication::translate("MainWindow", "Add File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAddDirectory->setText(QApplication::translate("MainWindow", "Add Directory", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAddDirectory->setToolTip(QApplication::translate("MainWindow", "Add Directory", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRemoveFile->setText(QApplication::translate("MainWindow", "Remove File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRemoveFile->setToolTip(QApplication::translate("MainWindow", "Remove File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionInfo->setText(QApplication::translate("MainWindow", "Info", 0, QApplication::UnicodeUTF8));
        createSpriteCommandButton->setText(QApplication::translate("MainWindow", "Save css sprite", 0, QApplication::UnicodeUTF8));
        previewPageCommandButton->setText(QApplication::translate("MainWindow", "Create preview page", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Element margin", 0, QApplication::UnicodeUTF8));
        marginSpinBox->setSuffix(QApplication::translate("MainWindow", "px", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Element information", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Image name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Image size", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "x", 0, QApplication::UnicodeUTF8));
        elementImageLabel->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Generated css values", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
