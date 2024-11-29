cmake_minimum_required(VERSION 3.16)

project(parser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Specify the root directory
set(ROOT_DIR ${CMAKE_SOURCE_DIR})

# Collect source files and header files dynamically for each module
file(GLOB Parser_SRC
    "${ROOT_DIR}/Parser/src/*.cpp"
    "${ROOT_DIR}/Parser/include/*.h"
)

file(GLOB Scanner_SRC
    "${ROOT_DIR}/Scanner/src/*.cpp"
    "${ROOT_DIR}/Scanner/include/*.h"
)

file(GLOB Data_SRC
    "${ROOT_DIR}/Data/src/*.cpp"
    "${ROOT_DIR}/Data/include/*.h"
)

file(GLOB FileHandling_SRC
    "${ROOT_DIR}/FileHandling/src/*.cpp"
    "${ROOT_DIR}/FileHandling/include/*.h"
)

file(GLOB Widgets_SRC
    "${ROOT_DIR}/Widgets/src/*.cpp"
    "${ROOT_DIR}/Widgets/include/*.h"
)

set(Widgets
    MainWindow.cpp  MainWindow.h
    ${Widgets_SRC}
)

set(Parser
    ${Parser_SRC}
)

set(Scanner
    ${Scanner_SRC}
)

set(Data
    ${Data_SRC}
)

set(FileHandling
    ${FileHandling_SRC}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(parser
        MANUAL_FINALIZATION
        main.cpp
        ${Widgets}
        ${Parser}
        ${Scanner}
        ${Data}
        ${FileHandling}
        resources.qrc
    )
endif()


# Include directories for headers
include_directories(
    ${ROOT_DIR}/Parser/include
    ${ROOT_DIR}/Scanner/include
    ${ROOT_DIR}/Data/include
    ${ROOT_DIR}/FileHandling/include
    ${ROOT_DIR}/Widgets/include
)

target_link_libraries(parser PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.parser)
endif()
set_target_properties(parser PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS parser
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(parser)
endif()
