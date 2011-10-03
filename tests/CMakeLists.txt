include_directories(
  ${QT_INCLUDES}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/../src/
)

set(tests_SRCS
  ui/spriteformattoolbartest.cpp
  ../src/ui/spriteformattoolbar.cpp
  ui/spritequalitytoolbartest.cpp
  ../src/ui/spritequalitytoolbar.cpp
  ui/spriteelementtreewidgettest.cpp
  ../src/ui/spriteelementtreewidget.cpp
  ui/spriteelementlistwidgettest.cpp
  ../src/ui/spriteelementlistwidget.cpp
  ui/mainwindowtest.cpp
  ../src/ui/mainwindow.cpp
  ../src/ui/infodialog.cpp
  ../src/cssspriteelementimage.cpp
  ../src/cssspriteelementdescription.cpp
  ../src/cssspriteelementimagelist.cpp
  ../src/spritewidget.cpp
  ../src/previewpage.cpp
  main.cpp
)

set(tests_MOC_SRCS
  ui/spriteformattoolbartest.h
  ../src/ui/spriteformattoolbar.h
  ui/spritequalitytoolbartest.h
  ../src/ui/spritequalitytoolbar.h
  ui/spriteelementtreewidgettest.h
  ../src/ui/spriteelementtreewidget.h
  ui/spriteelementlistwidgettest.h
  ../src/ui/spriteelementlistwidget.h
  ui/mainwindowtest.h
  ../src/ui/mainwindow.h
  ../src/ui/infodialog.h
  ../src/cssspriteelementimage.h
  ../src/cssspriteelementdescription.h
  ../src/cssspriteelementimagelist.h
  ../src/spritewidget.h
  ../src/previewpage.h
)

SET(tests_RCCS 
  ../src/resources/resources.qrc
)

qt4_add_resources(tests_RCC_SRCS ${tests_RCCS})
qt4_wrap_cpp(tests_SRCS ${tests_MOC_SRCS})

add_executable(tests MACOSX_BUNDLE WIN32
  ${tests_SRCS} 
  ${tests_RCC_SRCS}
)

target_link_libraries(tests
  ${QT_QTCORE_LIBRARY}
  ${QT_QTGUI_LIBRARY}
  ${QT_QTTEST_LIBRARY}
  ${QT_QTXML_LIBRARY}
)

add_test(SpriteFormatToolBarTest ${EXECUTABLE_OUTPUT_PATH}/tests SpriteFormatToolBarTest)
add_test(SpriteQualityToolBarTest ${EXECUTABLE_OUTPUT_PATH}/tests SpriteQualityToolBarTest)
add_test(SpriteElementListWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests SpriteElementListWidgetTest)
add_test(SpriteElementTreeWidgetTest ${EXECUTABLE_OUTPUT_PATH}/tests SpriteElementTreeWidgetTest)
add_test(MainWindowTest ${EXECUTABLE_OUTPUT_PATH}/tests MainWindowTest)
