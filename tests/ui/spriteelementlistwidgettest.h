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

    void testShouldInsertNewImagesIntoList() {
        spriteElementListWidget->update(cssSpriteElementImageList());
        QVERIFY(spriteElementListWidget->count() == 2);
        QVERIFY(spriteElementListWidget->item(0)->text() == QString("images/16x16/arrow-down.png"));
        QVERIFY(spriteElementListWidget->item(1)->text() == QString("images/16x16/arrow-up.png"));
    }
};

#endif
