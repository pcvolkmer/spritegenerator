#include "previewpagetest.h"

PreviewPageTest::PreviewPageTest(QObject* parent): QObject(parent) {}

void PreviewPageTest::initTestCase() {}

void PreviewPageTest::cleanupTestCase() {}

void PreviewPageTest::testShouldReturnCorrectStyleName() {
  QString fileName = "this/is/a/test#1";
  QCOMPARE(PreviewPage::styleName(fileName, "testsprite"), QString("testsprite_test1_19a1"));
  
  fileName = "this/is/a/test.png";
  QCOMPARE(PreviewPage::styleName(fileName, "testsprite2"), QString("testsprite2_test_png_bf9"));
  
  fileName = "this/is/a/test@3.png";
  QCOMPARE(PreviewPage::styleName(fileName, "testsprite123"), QString("testsprite123_test3_png_8fa2"));
}


