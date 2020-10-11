cmake_minimum_required(VERSION 3.9.0)

project(PiRadioApp VERSION 0.4.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## DEPENDENCIES ###########################################
## gstreamer
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

## catch2 - utest
set (enginePath engine)
include_directories(engine/dependencies)

## gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


## ENGINE LIBS ############################################

include_directories(${enginePath}/include)
set (engineSrcPath ${enginePath}/source)
set(engineSrc
    ${engineSrcPath}/Audio.cpp
    ${engineSrcPath}/RadioStation.cpp
    ${engineSrcPath}/RadioManager.cpp
    ${engineSrcPath}/AudioManager.cpp
    ${engineSrcPath}/Logs.cpp
    ${engineSrcPath}/dbStationJson.cpp
    ${engineSrcPath}/RadioRoutes.cpp
)
add_library(${PROJECT_NAME}EngineLib SHARED ${engineSrc})
set (engineLib ${PROJECT_NAME}EngineLib)


## APP EXECUTABLE #########################################

set(engineSrcMain ${enginePath}/PiRadioApp.cpp)
add_executable(${PROJECT_NAME} ${engineSrcMain})
target_link_libraries(
    ${PROJECT_NAME}
    ${engineLib}
    ${GST_LIBRARIES}
    zmq
    pthread
)


## uTESTS #################################################

set (engineTestsPath engine-utests)
include_directories(${engineTestsPath})
set (engineTestsSrc 
    ${engineTestsPath}/test_main.cpp
    ${engineTestsPath}/test_IPCMessage.cpp
    ${engineTestsPath}/test_IPCMaanger.cpp
    ${engineTestsPath}/test_Database.cpp
)

set (project_name_engine_tests ${PROJECT_NAME}-engine-tests)
add_executable(${project_name_engine_tests} ${engineTestsSrc})
target_link_libraries(
    ${project_name_engine_tests}
    ${GTEST_LIBRARIES}
    ${engineLib}
    ${GST_LIBRARIES}
    zmq
    pthread
)
add_test(unitTest ${project_name_engine_tests})
