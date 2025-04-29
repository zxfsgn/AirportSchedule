cmake_minimum_required(VERSION 3.5)

project(AIRPORT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AIRPORT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
          chartview.h chartview.cpp
        circlechart.h circlechart.cpp
        barchart.h barchart.cpp
        editflight.h editflight.cpp
        linechart.h linechart.cpp
        ../CMAKESRC/FileInteractions/FileInteractions.cpp ../CMAKESRC/FileInteractions/FileInteractions.h ../CMAKESRC/Flight/Flight.cpp ../CMAKESRC/Flight/Flight.h ../CMAKESRC/a.out ../CMAKESRC/BinaryInput.cpp ../CMAKESRC/BinaryInput.h ../CMAKESRC/Date.h ../CMAKESRC/FileInput.cpp ../CMAKESRC/FileInput.h ../CMAKESRC/FileOutput.cpp ../CMAKESRC/FileOutput.h ../CMAKESRC/InputChecks.cpp ../CMAKESRC/InputChecks.h ../CMAKESRC/InputKeyboard.cpp ../CMAKESRC/InputKeyboard.h ../CMAKESRC/Manipulations.cpp ../CMAKESRC/Manipulations.h ../CMAKESRC/Others.cpp ../CMAKESRC/Others.h ../CMAKESRC/OutputScreen.cpp ../CMAKESRC/OutputScreen.h ../CMAKESRC/Request.cpp ../CMAKESRC/Request.h ../CMAKESRC/Source.cpp ../CMAKESRC/Source.h ../CMAKESRC/Student.h ../CMAKESRC/Flights.bin ../CMAKESRC/Flights.txt ../CMAKESRC/Widths.h
        ../CMAKESRC/CUDFlight/cudflight.cpp ../CMAKESRC/CUDFlight/cudflight.h
        ../CMAKESRC/CriteriaSum/criteriasum.cpp ../CMAKESRC/CriteriaSum/criteriasum.h
        addflight.h addflight.cpp
        table.h table.cpp
        requests.h requests.cpp
        ../CMAKESRC/Sort/Sort.cpp ../CMAKESRC/Sort/Sort.h
        ../CMAKESRC/Search/search.cpp ../CMAKESRC/Search/search.h
        tablewrapper.h tablewrapper.cpp
        flighttablemodel.h flighttablemodel.cpp
        qflight.h qflight.cpp
        tabledelegate.h tabledelegate.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET AIRPORT APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(AIRPORT SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AIRPORT
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(AIRPORT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AIRPORT)
endif()
set_target_properties(AIRPORT PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AIRPORT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AIRPORT)
endif()
