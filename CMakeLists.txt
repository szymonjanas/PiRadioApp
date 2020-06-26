cmake_minimum_required(VERSION 3.7)

project(PiRadio)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.2)

include_directories("${GST_INCLUDE_DIRS}")
link_libraries(${GST_LIBRARIES})















