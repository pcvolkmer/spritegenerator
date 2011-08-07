#include "spriteformattoolbartest.h"

SpriteFormatToolBarTest::SpriteFormatToolBarTest(QObject* parent) {}

void SpriteFormatToolBarTest::initTestCase() {
    this->spriteFormatToolBar = new SpriteFormatToolBar();
    this->spriteFormatToolBar->show();
}

void SpriteFormatToolBarTest::cleanupTestCase() {
    delete this->spriteFormatToolBar;
}

void SpriteFormatToolBarTest::testShouldEnableYMarginSpinBox() {
    QTest::mouseClick(
        this->spriteFormatToolBar->ui()->lockMarginToolButton,
        Qt::LeftButton
    );
    QVERIFY(this->spriteFormatToolBar->ui()->yMarginSpinBox->isEnabled());
}

void SpriteFormatToolBarTest::testShouldEmitSignalSettingsChangedOnXMarginChanged() {
    QSignalSpy spy(this->spriteFormatToolBar, SIGNAL(settingsChanged()));

    QTest::keyClick(
        this->spriteFormatToolBar->ui()->xMarginSpinBox,
        Qt::Key_Up
    );

    QCOMPARE(spy.count(),1);
}

void SpriteFormatToolBarTest::testShouldEmitSignalSettingsChangedOnYMarginChanged() {
    QSignalSpy spy(this->spriteFormatToolBar, SIGNAL(settingsChanged()));

    QTest::keyClick(
        this->spriteFormatToolBar->ui()->yMarginSpinBox,
        Qt::Key_Up
    );

    QCOMPARE(spy.count(),1);
}

void SpriteFormatToolBarTest::testShouldEmitSignalRepeatNeedsAutoChangeOnSpriteRepeatChanged() {
    QSignalSpy spy(this->spriteFormatToolBar, SIGNAL(repeatNeedsAutoChange(bool)));

    QTest::keyClick(
        this->spriteFormatToolBar->ui()->spriteRepeatComboBox,
        Qt::Key_Down
    );

    QCOMPARE(spy.count(),2);
}

void SpriteFormatToolBarTest::testShouldEmitSignalSettingsChangedOnElementLayoutChanged() {
    QSignalSpy spy(this->spriteFormatToolBar, SIGNAL(settingsChanged()));

    QTest::keyClick(
        this->spriteFormatToolBar->ui()->elementLayoutComboBox,
        Qt::Key_Down
    );

    QCOMPARE(spy.count(),1);
}
