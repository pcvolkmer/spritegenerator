#include <QtCore>
#include <QtGui>
#include <QtTest>
#include <QtTest/qtestmouse.h>
#include <QtTest/qtestkeyboard.h>

#include "../../src/ui/spriteelementtreewidget.h"

#ifndef SPRITEELEMENTTREEWIDGETTEST_H
#define SPRITEELEMENTTREEWIDGETTEST_H

class SpriteElementTreeWidgetTest : public QObject {

    Q_OBJECT

public:
    explicit SpriteElementTreeWidgetTest(QObject *parent = 0) ;

private:
    SpriteElementTreeWidget * spriteElementTreeWidget;
    CssSpriteElementImageList * cssSpriteElementImageList() ;

private slots:
    void initTestCase() ;
    void cleanupTestCase() ;

    void testShouldUpdateTreeWidget() ;
    void testShouldRemoveImage() ;
};

#endif
