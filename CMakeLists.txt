cmake_minimum_required(VERSION 3.7)
project(Enyo_Game)

set(CMAKE_CXX_STANDARD 14)
set(SFML_ROOT "D:/Development/SFML-2.4.2-gcc")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")


# Find SFML
find_package(SFML 2 REQUIRED audio graphics network system window)
if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML couldn't be located!")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${SFML_INCLUDE_DIR})

set(HEADER_FILES
        include/Animation.h include/Application.h include/Asteroid.h include/Bullet.h include/Constants.h
        include/Entity.h include/Explosion.h include/GamePlay.h include/GameStage.h include/Id.h include/MapGenerator.h
        include/Menu.h include/Player.h include/ResourceHolder.hpp include/Vector.hpp include/Wall.h)

set(SOURCE_FILES main.cpp source/Animation.cpp source/Application.cpp source/Asteroid.cpp source/Bullet.cpp
        source/Entity.cpp source/Explosion.cpp source/GamePlay.cpp source/MapGenerator.cpp source/Menu.cpp
        source/Player.cpp source/Wall.cpp)

add_executable(Enyo_Game ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(Enyo_Game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})