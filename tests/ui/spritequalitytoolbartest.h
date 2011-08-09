#include <QtCore>
#include <QtGui>
#include <QtTest>
#include <QtTest/qtestmouse.h>
#include <QtTest/qtestkeyboard.h>

#include "../../src/ui/spritequalitytoolbar.h"

#ifndef SPRITEQUALITYTOOLBARTEST_H
#define SPRITEQUALITYTOOLBARTEST_H

class SpriteQualityToolBarTest : public QObject {

    Q_OBJECT

public:
    explicit SpriteQualityToolBarTest(QObject *parent = 0);

private:
    SpriteQualityToolBar * spriteQualityToolBar;

private slots:
    void initTestCase() ;
    void cleanupTestCase() ;

    void testShouldChangeSpinBoxValueOnSliderChange() ;
    void testShouldChangeSliderValueOnSpinBoxChange() ;
    void testShouldChangeColorDepth() ;
    void testShouldEmitSignalQualityChangedOnColorDepthChange() ;
    void testShouldEmitSignalQualityChangedOnSpinBoxChange() ;
    void testShouldEmitSignalQualityChangedOnSliderChange() ;
};

#endif
