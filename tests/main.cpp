#include <QtCore>
#include <QtGui>
#include <QApplication>

#include "ui/spriteformattoolbartest.h"
#include "ui/spriteelementlistwidgettest.h"
#include "ui/spriteelementtreewidgettest.h"
#include "ui/mainwindowtest.h"

int main( int argc, char ** argv ) {
    QApplication app(argc, argv);

    if (QString(argv[argc-1]) == "SpriteFormatToolBarTest") {
        SpriteFormatToolBarTest spriteFormatToolBarTest;
        return QTest::qExec(&spriteFormatToolBarTest, argc-1, argv);
    }
    else if (QString(argv[argc-1]) == "SpriteElementListWidgetTest") {
        SpriteElementListWidgetTest spriteElementListWidgetTest;
        return QTest::qExec(&spriteElementListWidgetTest, argc-1, argv);
    }
    else if (QString(argv[argc-1]) == "SpriteElementTreeWidgetTest") {
        SpriteElementTreeWidgetTest spriteElementTreeWidgetTest;
        return QTest::qExec(&spriteElementTreeWidgetTest, argc-1, argv);
    }
    else if (QString(argv[argc-1]) == "MainWindowTest") {
        MainWindowTest mainWindowTest;
        return QTest::qExec(&mainWindowTest, argc-1, argv);
    }
    else {
        qDebug() << "Not a valid test case selected. Add test case name as last parameter. (e.g.: tests -xunitxml MainWindowTest)";
    }
}
