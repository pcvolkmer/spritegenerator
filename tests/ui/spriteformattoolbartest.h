#include <QtCore>
#include <QtGui>
#include <QtTest>
#include <QtTest/qtestmouse.h>
#include <QtTest/qtestkeyboard.h>

#include "../../src/ui/spriteformattoolbar.h"

#ifndef SPRITEFORMATTOOLBARTEST_H
#define SPRITEFORMATTOOLBARTEST_H

class SpriteFormatToolBarTest : public QObject {

    Q_OBJECT

public:
    explicit SpriteFormatToolBarTest(QObject *parent = 0);

private:
    SpriteFormatToolBar * spriteFormatToolBar;

private slots:
    void initTestCase() ;
    void cleanupTestCase() ;
    void testShouldEnableYMarginSpinBox() ;
    void testShouldEmitSignalSettingsChangedOnXMarginChanged() ;
    void testShouldEmitSignalSettingsChangedOnYMarginChanged() ;
    void testShouldEmitSignalRepeatNeedsAutoChangeOnSpriteRepeatChanged() ;
    void testShouldEmitSignalSettingsChangedOnElementLayoutChanged() ;
};

#endif
