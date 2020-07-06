cmake_minimum_required(VERSION 3.7)

project(PiRadio)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# BOOST
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.71.0 COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

# WebToolKit
find_package( Wt REQUIRED )
include_directories( ${Wt_INCLUDE_DIR} )

# Gstreamer
set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.2)
include_directories( ${GST_INCLUDE_DIRS})

set (SOURCES
    source/main.cpp
    source/AudioEngine.cpp
    )
include_directories(source)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GST_LIBRARIES} ${Boost_LIBRARIES} ${Wt_INCLUDE_DIR} )











