#include "mainwindowtest.h"

MainWindowTest::MainWindowTest(QObject* parent): QObject(parent) {}

void MainWindowTest::initTestCase() {
    mainWindow = new MainWindow();
    mainWindow->show();
}

void MainWindowTest::cleanupTestCase() {
    delete mainWindow;
}

void MainWindowTest::testShouldDisableXMarginSelectorOnXRepeat() {
    QVERIFY(mainWindow->getUi()->resultingCssTextBrowser->isVisible());
    QVERIFY(! mainWindow->getUi()->repeatSettingsInfoWidget->isVisible());

    QTest::keyClick(
        mainWindow->getUi()->spriteSettingsToolBar->ui()->spriteRepeatComboBox,
        Qt::Key_Down
    );

    QVERIFY(mainWindow->getUi()->spriteSettingsToolBar->ui()->spriteRepeatComboBox->currentText() == QString("repeat-x"));

    QVERIFY(! mainWindow->getUi()->resultingCssTextBrowser->isVisible());
    QVERIFY(mainWindow->getUi()->repeatSettingsInfoWidget->isVisible());

    QTest::mouseClick(
        mainWindow->getUi()->changeSettingsButton,
        Qt::LeftButton
    );

    QVERIFY(! mainWindow->getUi()->spriteSettingsToolBar->ui()->xMarginSpinBox->isEnabled());
}

void MainWindowTest::testShouldDisableYMarginSelectorOnYRepeat() {
    QVERIFY(mainWindow->getUi()->resultingCssTextBrowser->isVisible());
    QVERIFY(! mainWindow->getUi()->repeatSettingsInfoWidget->isVisible());

    QTest::keyClick(
        mainWindow->getUi()->spriteSettingsToolBar->ui()->spriteRepeatComboBox,
        Qt::Key_Down
    );

    QVERIFY(mainWindow->getUi()->spriteSettingsToolBar->ui()->spriteRepeatComboBox->currentText() == QString("repeat-y"));

    QVERIFY(! mainWindow->getUi()->resultingCssTextBrowser->isVisible());
    QVERIFY(mainWindow->getUi()->repeatSettingsInfoWidget->isVisible());

    QTest::mouseClick(
        mainWindow->getUi()->changeSettingsButton,
        Qt::LeftButton
    );

    QVERIFY(! mainWindow->getUi()->spriteSettingsToolBar->ui()->yMarginSpinBox->isEnabled());
}

void MainWindowTest::testShouldEnableMarginSelectorsOnNoRepeat() {
    QVERIFY(mainWindow->getUi()->resultingCssTextBrowser->isVisible());
    QVERIFY(! mainWindow->getUi()->repeatSettingsInfoWidget->isVisible());

    QTest::keyClick(
        mainWindow->getUi()->spriteSettingsToolBar->ui()->spriteRepeatComboBox,
        Qt::Key_Up
    );
    QTest::keyClick(
        mainWindow->getUi()->spriteSettingsToolBar->ui()->spriteRepeatComboBox,
        Qt::Key_Up
    );

    QVERIFY(mainWindow->getUi()->spriteSettingsToolBar->ui()->spriteRepeatComboBox->currentText() == QString("no-repeat"));

    QVERIFY(mainWindow->getUi()->resultingCssTextBrowser->isVisible());
    QVERIFY(! mainWindow->getUi()->repeatSettingsInfoWidget->isVisible());

    QTest::mouseClick(
        mainWindow->getUi()->changeSettingsButton,
        Qt::LeftButton
    );

    QVERIFY(mainWindow->getUi()->spriteSettingsToolBar->ui()->xMarginSpinBox->isEnabled());
    QVERIFY(! mainWindow->getUi()->spriteSettingsToolBar->ui()->yMarginSpinBox->isEnabled());
}
