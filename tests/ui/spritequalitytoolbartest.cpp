#include "spritequalitytoolbartest.h"

SpriteQualityToolBarTest::SpriteQualityToolBarTest(QObject* parent): QObject(parent) {}

void SpriteQualityToolBarTest::initTestCase() {
    this->spriteQualityToolBar = new SpriteQualityToolBar();
    this->spriteQualityToolBar->show();
}

void SpriteQualityToolBarTest::cleanupTestCase() {
    this->spriteQualityToolBar->deleteLater();
}

void SpriteQualityToolBarTest::testShouldChangeSpinBoxValueOnSliderChange() {
    QVERIFY(this->spriteQualityToolBar->compressionLevel() == 3);
    QTest::keyClick(
        this->spriteQualityToolBar->ui()->compressionSlider,
        Qt::Key_Right
    );
    QVERIFY(this->spriteQualityToolBar->ui()->compressionSpinBox->value() == 4);
    QVERIFY(this->spriteQualityToolBar->qImageQuality() == 44);

}

void SpriteQualityToolBarTest::testShouldChangeSliderValueOnSpinBoxChange() {
    QVERIFY(this->spriteQualityToolBar->compressionLevel() == 4);
    QTest::keyClick(
        this->spriteQualityToolBar->ui()->compressionSpinBox,
        Qt::Key_Up
    );
    QVERIFY(this->spriteQualityToolBar->ui()->compressionSlider->value() == 5);
    QVERIFY(this->spriteQualityToolBar->qImageQuality() == 55);
}

void SpriteQualityToolBarTest::testShouldChangeColorDepth() {
    QVERIFY(this->spriteQualityToolBar->ui()->qualityComboBox->currentIndex() == 0);
    QVERIFY(this->spriteQualityToolBar->colorDepth() == SpriteWidget::FORMAT_RGBA32);
    QTest::keyClick(
        this->spriteQualityToolBar->ui()->qualityComboBox,
        Qt::Key_Down
    );
    QVERIFY(this->spriteQualityToolBar->colorDepth() == SpriteWidget::FORMAT_RGBA24);
}

void SpriteQualityToolBarTest::testShouldEmitSignalQualityChangedOnColorDepthChange() {
    QSignalSpy spy(this->spriteQualityToolBar, SIGNAL(qualityChanged()));

    QTest::keyClick(
        this->spriteQualityToolBar->ui()->qualityComboBox,
        Qt::Key_Down
    );

    QCOMPARE(spy.count(),1);
}

void SpriteQualityToolBarTest::testShouldEmitSignalQualityChangedOnSpinBoxChange() {
    QSignalSpy spy(this->spriteQualityToolBar, SIGNAL(qualityChanged()));

    QTest::keyClick(
        this->spriteQualityToolBar->ui()->compressionSpinBox,
        Qt::Key_Down
    );

    QCOMPARE(spy.count(),1);
}

void SpriteQualityToolBarTest::testShouldEmitSignalQualityChangedOnSliderChange() {
    QSignalSpy spy(this->spriteQualityToolBar, SIGNAL(qualityChanged()));

    QTest::keyClick(
        this->spriteQualityToolBar->ui()->compressionSlider,
        Qt::Key_Right
    );

    QCOMPARE(spy.count(),1);
}
