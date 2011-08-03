include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(spritegenerator_SRCS
  ui/mainwindow.cpp
  ui/infodialog.cpp
  ui/spriteelementtreewidget.cpp
  ui/spriteelementlistwidget.cpp
  spritewidget.cpp
  cssspriteelementdescription.cpp
  cssspriteelementimage.cpp
  cssspriteelementimagelist.cpp
  previewpage.cpp
  main.cpp
)

set(spritegenerator_MOC_SRCS
  ui/mainwindow.h
  ui/infodialog.h
  ui/spriteelementtreewidget.h
  ui/spriteelementlistwidget.h
  spritewidget.h
) 

SET(resources_RCCS 
  resources/resources.qrc
)

set(spritegenerator_UIS
  ui/mainwindow.ui
  ui/infoDialog.ui
  ui/spriteFormatSelector.ui
)

qt4_add_resources(resources_RCC_SRCS ${resources_RCCS})
qt4_wrap_cpp(spritegenerator_SRCS ${spritegenerator_MOC_SRCS})
qt4_wrap_ui(spritegenerator_UIS_H ${spritegenerator_UIS})

IF( WIN32 AND MINGW )
  # To cross compile on Linux use: 'i686-w64-mingw32-windres' or similar command shipped with mingw cross compiler.
  # Change resources/spritegeneratoricon.rc to use the correct path seperator depending on used plattform.
  ADD_CUSTOM_COMMAND( OUTPUT spritegeneratoricon.rc.obj
    COMMAND i686-w64-mingw32-windres -I${CMAKE_CURRENT_SOURCE_DIR} -i${CMAKE_CURRENT_SOURCE_DIR}/resources/spritegeneratoricon.rc 
	-o spritegeneratoricon.rc.obj
  )
  SET(spritegenerator_SRCS ${spritegenerator_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/spritegeneratoricon.rc.obj)
ENDIF( WIN32 AND MINGW )
IF( WIN32 AND NOT MINGW )
  SET(spritegenerator_SRCS ${dataseteditor_SRCS} spritegeneratoricon.rc)
ENDIF( WIN32 AND NOT MINGW )

add_executable(spritegenerator MACOSX_BUNDLE WIN32
  ${spritegenerator_SRCS}
  ${spritegenerator_UIS_H}
  ${resources_RCC_SRCS}
)

target_link_libraries(spritegenerator
  ${QT_QTCORE_LIBRARY}
  ${QT_QTGUI_LIBRARY}
  ${QT_QTXML_LIBRARY}
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
    RUNTIME DESTINATION bin
  )
ENDIF (UNIX AND NOT APPLE)

IF (WIN32)
  INSTALL(TARGETS spritegenerator
    RUNTIME DESTINATION .
  )
ENDIF (WIN32)