project(spritegenerator)
cmake_minimum_required(VERSION 2.6)

set(QT_MIN_VERSION 4.6.0)
find_package(Qt4 REQUIRED)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 2)
set(VERSION_PATCH 0)

if (BUILD_NUMBER)
  set(VERSION_PATCH "${VERSION_PATCH}-${BUILD_NUMBER}")
else(BUILD_NUMBER)
  find_program(GIT_EXECUTABLE "git")
  if(GIT_EXECUTABLE)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} rev-parse --verify -q --short=7 HEAD
      OUTPUT_VARIABLE head
      OUTPUT_STRIP_TRAILING_WHITESPACE
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    set(VERSION_PATCH "${VERSION_PATCH}-git${head}")
  endif()
endif()

set(EXECUTABLE_OUTPUT_PATH
  ${CMAKE_CURRENT_BINARY_DIR}/bin
)

set(LIBRARY_OUTPUT_PATH
  ${CMAKE_CURRENT_BINARY_DIR}/libs
)

message ("Start build configuration for SpriteGenerator ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} ...")
message ("use 'cmake -i' to run CMake in interactive mode")
message ("or use:")
message ("  -DTESTS=(ON|OFF)    to build test application")
message ("  -DCOVERAGE=(ON|OFF) to run test application with code coverage")
message ("")

option (TESTS "Enable build of tests" OFF)
option (COVERAGE "Enable coverage" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/libs)

CONFIGURE_FILE( version.h.cmake src/version.h )
CONFIGURE_FILE( Doxyfile.cmake Doxyfile )

add_custom_target(doc)
find_program(DOXYGEN_EXECUTABLE "doxygen")
if (DOXYGEN_EXECUTABLE)
  add_custom_command(TARGET doc POST_BUILD
    COMMAND ${DOXYGEN_EXECUTABLE}
  )
endif()

SET(DESKTOP
  spritegenerator.desktop
)

SET(ICONS
  src/resources/images/spritegenerator.svg
)

add_subdirectory(src)
add_subdirectory(libs/csscomposer/src)

if(TESTS)
  if (COVERAGE)
    message ("Execute tests with coverage is enabled")
    find_program(LCOV_TOOL "lcov")
    find_program(LCOV_HTML "genhtml")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
  else (COVERAGE)
    message ("Execute tests with coverage is disabled")
  endif(COVERAGE)
  message ("Build of tests is enabled")
  enable_testing()
  add_subdirectory(tests)
else(TESTS)
  message ("Build of tests is disabled")
endif(TESTS)

IF (UNIX AND NOT APPLE)
  INSTALL(FILES ${DESKTOP}
    DESTINATION share/applications
  )
  INSTALL(FILES ${ICONS}
    DESTINATION share/icons/hicolor/scalable/apps
  )
ENDIF (UNIX AND NOT APPLE)

IF (APPLE)
  INSTALL(FILES ${FILES}
    DESTINATION ../../../
  )
ENDIF (APPLE)

IF (WIN32)
  INSTALL(FILES ${FILES}
    DESTINATION .
  )
  SET(WINQTFILES
    # This part should contain DLL files to be included in package e.g.:
    ${CMAKE_CURRENT_BINARY_DIR}/lib/libgcc_s_sjlj-1.dll
    ${CMAKE_CURRENT_BINARY_DIR}/lib/libstdc++-6.dll
    ${CMAKE_CURRENT_BINARY_DIR}/lib/QtCore4.dll
    ${CMAKE_CURRENT_BINARY_DIR}/lib/QtGui4.dll
    ${CMAKE_CURRENT_BINARY_DIR}/lib/QtSvg4.dll
    ${CMAKE_CURRENT_BINARY_DIR}/lib/QtXml4.dll
    ${CMAKE_CURRENT_BINARY_DIR}/lib/libjpeg-8.dll 
    ${CMAKE_CURRENT_BINARY_DIR}/lib/libpng15-15.dll
    ${CMAKE_CURRENT_BINARY_DIR}/lib/libtiff-5.dll
    ${CMAKE_CURRENT_BINARY_DIR}/lib/zlib1.dll
  )
  INSTALL(FILES ${WINQTFILES}
    DESTINATION .
  )
ENDIF (WIN32)

# CPACK
INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_RESOURCE_FILE_LICENSE "COPYING")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SpriteGenerator is a simple generator for CSS sprites.")
SET(CPACK_PACKAGE_VENDOR "Paul-Christian Volkmer <paul-christian.volkmer@mni.thm.de>")
SET(CPACK_PACKAGE_CONTACT "Paul-Christian Volkmer <paul-christian.volkmer@mni.thm.de>")
SET(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
IF (UNIX AND NOT APPLE)
  SET(CPACK_GENERATOR  "RPM")
  SET(CPACK_SYSTEM_NAME "i586")
  SET(CPACK_RPM_PACKAGE_RELEASE "1")
  SET(CPACK_RPM_PACKAGE_LICENSE "GPLv3")
  SET(
    CPACK_RPM_PACKAGE_DESCRIPTION
    "SpriteGenerator generates a css sprite out of several images and shows css needed to use the sprite image. Several options can be used to customize sprite generation like sprite orientation and color depth from 32 bit RGBA to 8 bit indexed color."
  )
  #SET(CPACK_RPM_CHANGELOG_FILE ${CMAKE_CURRENT_BINARY_DIR}/CHANGES)
  SET(CPACK_STRIP_FILES  ${CMAKE_CURRENT_BINARY_DIR}/bin/spritegenerator)
ENDIF (UNIX AND NOT APPLE)
IF (WIN32)
  SET(CPACK_GENERATOR  "NSIS")
  SET(CPACK_SYSTEM_NAME "win32")
  SET(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_BINARY_DIR}/COPYING)
  SET(CPACK_NSIS_MODIFY_PATH ON)
  SET(CPACK_NSIS_PACKAGE_NAME "SpriteGenerator")
  SET(CPACK_NSIS_DISPLAY_NAME "SpriteGenerator")
  SET(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_VENDOR}")
  SET(CPACK_PACKAGE_EXECUTABLES  ..\\\\spritegenerator;SpriteGenerator)
  SET(CPACK_CREATE_DESKTOP_LINKS ..\\\\spritegenerator)
  SET(CPACK_PACKAGE_INSTALL_DIRECTORY spritegenerator)
  SET(CPACK_STRIP_FILES  ${CMAKE_CURRENT_BINARY_DIR}/bin/spritegenerator.exe)
ENDIF (WIN32)
IF (APPLE)
  SET(CPACK_GENERATOR  "Bundle")
  SET(CPACK_BUNDLE_NAME "spritegenerator")
  SET(CPACK_BUNDLE_PLIST ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)
  SET(CPACK_BUNDLE_ICON ${CMAKE_CURRENT_BINARY_DIR}/src/resources/images/spritegenerator.icns)
ENDIF (APPLE)
INCLUDE(CPack)

