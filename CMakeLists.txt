cmake_minimum_required(VERSION 3.7)

# Solution Name
project(Enyo_Game)

# C++ Version
set(CMAKE_CXX_STANDARD 14)

# Set CMake modules path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set SFML root path
set(SFML_ROOT "")

# Set SFML Path
if(NOT SFML_ROOT)
    SET(SFML_ROOT "" CACHE STRING "Path to SFML root.")
endif()

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Find SFML
find_package(SFML 2 REQUIRED audio graphics network system window)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else(NOT SFML_FOUND)
    SET(SFML_ROOT "" CACHE STRING "Path to SFML root.")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add files
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")
file(GLOB_RECURSE SOURCES "source/*.cpp")

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("include" FILES ${HEADERS})
source_group("source" FILES ${SOURCES})

# Create .exe
add_executable(Enyo_Game ${HEADERS} ${SOURCES})

# Link libraries
target_link_libraries(Enyo_Game ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})