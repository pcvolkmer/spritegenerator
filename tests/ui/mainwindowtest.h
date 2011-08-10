#include <QtCore>
#include <QtGui>
#include <QtTest>
#include <QtTest/qtestmouse.h>
#include <QtTest/qtestkeyboard.h>

#include "../../src/ui/mainwindow.h"

#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

class MainWindowTest : public QObject {

    Q_OBJECT

public:
    explicit MainWindowTest(QObject *parent = 0) ;

private:
    MainWindow * mainWindow;

private slots:
    void initTestCase() ;
    void cleanupTestCase() ;

    void testShouldDisableXMarginSelectorOnXRepeat() ;
    void testShouldDisableYMarginSelectorOnYRepeat() ;
    void testShouldEnableMarginSelectorsOnNoRepeat() ;
    void testShouldUndoRepeatOnCancelButtonClicked() ;
};

#endif
