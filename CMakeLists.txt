cmake_minimum_required(VERSION 3.16)
project(LifeGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

add_executable(LifeGame
    src/main.cpp
    src/lifeWidget.cpp
    src/lifeWidget.h
    src/QtHud.cpp
    src/QtHud.h
    src/winGOL.cpp
    src/winGOL.h
    src/engine/LifeGame.cpp
    src/engine/Object.cpp
    src/engine/Square.cpp
    src/engine/Square8.cpp
    src/engine/Table.cpp
    src/engine/Table8.cpp
    src/engine/Type.cpp
    ui/GOL.ui
    res/res.qrc
)

target_include_directories(LifeGame PRIVATE src src/engine)
target_link_libraries(LifeGame PRIVATE Qt6::Widgets)

if(WIN32)
    target_sources(LifeGame PRIVATE LifeGame.rc)
endif()
