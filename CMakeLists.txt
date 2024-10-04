cmake_minimum_required(VERSION 3.16)

project(Final_project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск Qt6 с компонентами Widgets и Network
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    server.cpp
    server.h
)



qt_add_executable(Final_project
    ${PROJECT_SOURCES}
)

# Линковка с Qt6 Widgets и Network
target_link_libraries(Final_project PRIVATE Qt6::Widgets Qt6::Network)

install(TARGETS Final_project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
