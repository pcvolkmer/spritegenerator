#include <QtCore>
#include <QtGui>
#include <QtTest>
#include <QtTest/qtestmouse.h>
#include <QtTest/qtestkeyboard.h>

#include "../../src/ui/spriteelementlistwidget.h"

#ifndef SPRITEELEMENTLISTWIDGETTEST_H
#define SPRITEELEMENTLISTWIDGETTEST_H

class SpriteElementListWidgetTest : public QObject {

    Q_OBJECT

public:
    explicit SpriteElementListWidgetTest(QObject *parent = 0) ;

private:
    SpriteElementListWidget * spriteElementListWidget;
    CssSpriteElementImageList * cssSpriteElementImageList() ;

private slots:
    void initTestCase() ;
    void cleanupTestCase() ;
    void testShouldInsertNewImagesIntoList() ;
};

#endif
