#include "spriteelementlistwidgettest.h"

SpriteElementListWidgetTest::SpriteElementListWidgetTest(QObject* parent): QObject(parent) {

}

CssSpriteElementImageList* SpriteElementListWidgetTest::cssSpriteElementImageList() {
    CssSpriteElementImageList * result = new CssSpriteElementImageList();
    result->append(
        CssSpriteElementImage(
            "images/16x16/arrow-down.png",
            QImage(":images/16x16/arrow-down.png")
        )
    );
    result->append(
        CssSpriteElementImage(
            "images/16x16/arrow-up.png",
            QImage("images/16x16/arrow-up.png")
        )
    );
    return result;
}

void SpriteElementListWidgetTest::initTestCase() {
    spriteElementListWidget = new SpriteElementListWidget();
    spriteElementListWidget->show();
}

void SpriteElementListWidgetTest::cleanupTestCase() {
    delete spriteElementListWidget;
}
