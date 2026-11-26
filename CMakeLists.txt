cmake_minimum_required(VERSION 3.16)
project(SmartFootball VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

add_executable(smartfootball
    src/main.cpp
    src/model/Player.cpp
    src/model/Team.cpp
    src/logic/ScoutController.cpp
    src/logic/commands/FindCommand.cpp
    src/logic/commands/FilterCommand.cpp
    src/logic/commands/SortCommand.cpp
    src/ui/MainWindow.h
    src/ui/MainWindow.cpp
)

target_include_directories(smartfootball PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(smartfootball PRIVATE
    Qt5::Core
    Qt5::Widgets
)
