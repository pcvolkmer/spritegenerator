#include <QtCore>
#include <QtTest>

#include "../src/previewpage.h"

#ifndef PREVIEWPAGETEST_H
#define PREVIEWPAGETEST_H

class PreviewPageTest : public QObject {

    Q_OBJECT

public:
    explicit PreviewPageTest(QObject *parent = 0) ;

private slots:
    void initTestCase() ;
    void cleanupTestCase() ;

    void testShouldReturnCorrectStyleName() ;
};

#endif // PREVIEWPAGETEST_H