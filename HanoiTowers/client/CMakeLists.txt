#
# Copyright (C) 2018-2020 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.1)


set(CURRENT_PROJECT ${PROJECT_NAME})

include(../Heart/QuasarAppLib/CMake/ProjectOut.cmake)
include(../Heart/QuasarAppLib/CMake/ccache.cmake)
include(../Heart/QuasarAppLib/CMake/Version.cmake)

add_subdirectory(QMLLoginView)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

file(GLOB SOURCE_CPP
    "*.cpp" "*.qrc"
)

add_executable(${CURRENT_PROJECT} ${SOURCE_CPP})
target_link_libraries(${CURRENT_PROJECT} PRIVATE QmlNotyfyService Heart LoginView)
target_include_directories(${CURRENT_PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

setVersion(${PRODUCT_VER_Mj} ${PRODUCT_VER_Mn} ${PRODUCT_VER_Re})