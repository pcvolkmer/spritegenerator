include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(spritegenerator_SRCS
  ui/mainwindow.cpp
  ui/infodialog.cpp
  spritewidget.cpp
  cssspriteelementdescription.cpp
  cssspriteelementimage.cpp
  main.cpp
)

set(spritegenerator_MOC_SRCS
  ui/mainwindow.h
  ui/infodialog.h
  spritewidget.h
) 

SET(resources_RCCS 
  resources/resources.qrc
)

set(spritegenerator_UIS
  ui/mainwindow.ui
  ui/infoDialog.ui
)

qt4_add_resources(resources_RCC_SRCS ${resources_RCCS})
qt4_wrap_cpp(spritegenerator_SRCS ${spritegenerator_MOC_SRCS})
qt4_wrap_ui(spritegenerator_UIS_H ${spritegenerator_UIS})

add_executable(spritegenerator MACOSX_BUNDLE
  ${spritegenerator_SRCS}
  ${spritegenerator_UIS_H}
  ${resources_RCC_SRCS}
)

target_link_libraries(spritegenerator
  ${QT_QTCORE_LIBRARY}
  ${QT_QTGUI_LIBRARY}
)

IF(APPLE)
  SET (CMAKE_CXX_FLAGS "-mmacosx-version-min=10.5") 
  INSTALL(CODE
    "SET(BUNDLE
      \"\${CMAKE_INSTALL_PREFIX}/../..\"
    )"
  )
  INSTALL(CODE "EXECUTE_PROCESS(COMMAND macdeployqt ./bin/spritegenerator.app)")
  INSTALL(TARGETS spritegenerator BUNDLE DESTINATION ../../../)
ENDIF(APPLE)

IF (UNIX AND NOT APPLE)
  INSTALL(TARGETS spritegenerator
    RUNTIME DESTINATION /opt/spritegenerator
  )
ENDIF (UNIX AND NOT APPLE)