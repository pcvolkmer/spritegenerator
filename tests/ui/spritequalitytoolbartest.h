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

    void testShouldChangeSpinBoxValueOnSliderChange() {
        QVERIFY(this->spriteQualityToolBar->compressionLevel() == 3);
        QTest::keyClick(
            this->spriteQualityToolBar->ui()->compressionSlider,
            Qt::Key_Right
        );
        QVERIFY(this->spriteQualityToolBar->ui()->compressionSpinBox->value() == 4);
        QVERIFY(this->spriteQualityToolBar->qImageQuality() == 44);

    }

    void testShouldChangeSliderValueOnSpinBoxChange() {
        QVERIFY(this->spriteQualityToolBar->compressionLevel() == 4);
        QTest::keyClick(
            this->spriteQualityToolBar->ui()->compressionSpinBox,
            Qt::Key_Up
        );
        QVERIFY(this->spriteQualityToolBar->ui()->compressionSlider->value() == 5);
        QVERIFY(this->spriteQualityToolBar->qImageQuality() == 55);
    }

    void testShouldChangeColorDepth() {
        QVERIFY(this->spriteQualityToolBar->ui()->qualityComboBox->currentIndex() == 0);
        QVERIFY(this->spriteQualityToolBar->colorDepth() == SpriteWidget::FORMAT_RGBA32);
        QTest::keyClick(
            this->spriteQualityToolBar->ui()->qualityComboBox,
            Qt::Key_Down
        );
        QVERIFY(this->spriteQualityToolBar->colorDepth() == SpriteWidget::FORMAT_RGBA24);
    }
};

#endif
