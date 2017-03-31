cmake_minimum_required(VERSION 3.7)
project(Enyo_Game)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp include/Animation.h source/Animation.cpp include/Application.h source/Application.cpp include/Asteroid.h source/Asteroid.cpp include/Bullet.h source/Bullet.cpp include/Entity.h source/Entity.cpp include/Explosion.h source/Explosion.cpp include/GamePlay.h source/GamePlay.cpp include/GameStage.h source/GameStage.cpp include/Id.h include/MapGenerator.h source/MapGenerator.cpp include/Menu.h source/Menu.cpp include/Player.h source/Player.cpp include/ResourceHolder.hpp include/SceneNode.h include/Wall.h source/Wall.cpp)

include_directories(include)

add_executable(Enyo_Game ${SOURCE_FILES})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Enyo_Game ${SFML_LIBRARIES})
endif()