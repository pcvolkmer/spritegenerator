#include "spritequalitytoolbartest.h"

SpriteQualityToolBarTest::SpriteQualityToolBarTest(QObject* parent): QObject(parent) {}

void SpriteQualityToolBarTest::initTestCase() {
    this->spriteQualityToolBar = new SpriteQualityToolBar();
    this->spriteQualityToolBar->show();
}

void SpriteQualityToolBarTest::cleanupTestCase() {
    this->spriteQualityToolBar->deleteLater();
}

