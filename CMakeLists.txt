cmake_minimum_required(VERSION 3.19)
project(SmartBackpack LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets SerialPort Bluetooth Network)

qt_standard_project_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUUI ON)

qt_add_executable(SmartBackpack
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    logindialog.cpp
    logindialog.h
    logindialog.ui
    btconnection.cpp
    btconnection.h
)

target_link_libraries(SmartBackpack
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::SerialPort
        Qt6::Bluetooth
        Qt6::Network
)

include(GNUInstallDirs)

install(TARGETS SmartBackpack
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SmartBackpack
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
