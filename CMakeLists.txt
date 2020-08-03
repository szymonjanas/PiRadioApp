cmake_minimum_required(VERSION 3.7.0)

project(PiRadioApp VERSION 0.3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
find_package(PkgConfig REQUIRED)
if ( NOT (PKGCONFIG_FOUND))
      message(FATAL_ERROR "Please Install PPkgConfig: CMake will Exit")
endif()
pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.2)
if ( NOT (GST_FOUND))
      message(FATAL_ERROR "Please Install Gstreamer Dev: CMake will Exit")
endif()
set(ENV{PKG_CONFIG_PATH})

include_directories("${GST_INCLUDE_DIRS}")
link_libraries(${GST_LIBRARIES})

include_directories(
    sources/DatabaseEngine
    sources/AudioEngine
    sources/Communication
    sources/RadioManager
)

set(SOURCES
    sources/PiRadioApp.cpp
    sources/AudioEngine/AudioEngine.cpp
    sources/AudioEngine/AudioEngineManager.cpp
    sources/DatabaseEngine/Station.cpp
    sources/DatabaseEngine/StationsDatabaseTxt.cpp
    sources/Communication/Communication.cpp
    sources/RadioManager/RadioManager.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(
    ${PROJECT_NAME} 
    ${GST_LIBRARIES}
    zmq
)
