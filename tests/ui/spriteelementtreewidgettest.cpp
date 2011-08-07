#include "spriteelementtreewidgettest.h"


SpriteElementTreeWidgetTest::SpriteElementTreeWidgetTest(QObject* parent) {

}

CssSpriteElementImageList* SpriteElementTreeWidgetTest::cssSpriteElementImageList() {
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

void SpriteElementTreeWidgetTest::initTestCase() {
    spriteElementTreeWidget = new SpriteElementTreeWidget();
    spriteElementTreeWidget->show();
}

void SpriteElementTreeWidgetTest::cleanupTestCase() {
    delete spriteElementTreeWidget;
}

void SpriteElementTreeWidgetTest::testShouldUpdateTreeWidget() {
    spriteElementTreeWidget->update(cssSpriteElementImageList());
    QTreeWidgetItem * node = spriteElementTreeWidget->invisibleRootItem()->child(1)->child(0)->child(0);
    QVERIFY(node->childCount() == 2);
    QVERIFY(node->child(0)->text(0) == QString("arrow-down.png"));
    QVERIFY(node->child(1)->text(0) == QString("arrow-up.png"));
}

void SpriteElementTreeWidgetTest::testShouldRemoveImage() {
    QTreeWidgetItem * node = spriteElementTreeWidget->invisibleRootItem()->child(1)->child(0)->child(0);
    spriteElementTreeWidget->setCurrentItem(node->child(0));

}
