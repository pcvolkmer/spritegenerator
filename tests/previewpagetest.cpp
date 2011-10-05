#include "previewpagetest.h"

PreviewPageTest::PreviewPageTest(QObject* parent): QObject(parent) {}

void PreviewPageTest::initTestCase() {}

void PreviewPageTest::cleanupTestCase() {}

void PreviewPageTest::testShouldReturnCorrectStyleName() {
  QString fileName = "this/is/a/test#1";
  QCOMPARE(PreviewPage::styleName(fileName), QString("sprite_test1_19a1"));
  
  fileName = "this/is/a/test.png";
  QCOMPARE(PreviewPage::styleName(fileName), QString("sprite_test_png_bf9"));
  
  fileName = "this/is/a/test@3.png";
  QCOMPARE(PreviewPage::styleName(fileName), QString("sprite_test3_png_8fa2"));
}


