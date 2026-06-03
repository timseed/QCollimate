cmake_minimum_required(VERSION 3.16)

project(QCollimate VERSION 0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED)
message(status "QT Version Major is ${QT_VERSION_MAJOR}")
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets UiTools MultimediaWidgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Widgets/ringwidget.ui
        Widgets/ringwidget.cpp
        Widgets/ringwidget.h
        Widgets/colview.ui
        Widgets/colview.cpp
        Widgets/colview.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(QCollimate
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Widgets/gridlayoutdebugger.h Widgets/gridlayoutdebugger.cpp
        Info.plist
        Readme.md
        Info.plist
        documentation/img0.png documentation/img1.png documentation/img2.png
    )
  # Define target properties for Android with Qt 6 as:
  #    set_property(TARGET QCollimate APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
  #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
  # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(QCollimate SHARED
            ${PROJECT_SOURCES}
        )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(QCollimate
            ${PROJECT_SOURCES}
        )
  endif()
endif()

target_link_libraries(QCollimate PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::UiTools Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::MultimediaWidgets)
set_target_properties(QCollimate PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QCollimate)
endif()
set_target_properties(QCollimate PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QCollimate
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
#Add a run command
add_custom_target(run
    COMMAND $<TARGET_FILE:QCollimate>
    DEPENDS QCollimate
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running the Qt application..."
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(QCollimate)
endif()
