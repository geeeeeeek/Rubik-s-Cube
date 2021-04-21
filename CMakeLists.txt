cmake_minimum_required(VERSION 3.17)

project(RubikCube)

message(STATUS "${PROJECT_NAME} start building")

# 项目设置

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BIT_SUFFIX "64bit")
else()
    set(BIT_SUFFIX "32bit")
endif()

set(PRO_OUTPUT_DIR "${CMAKE_BINARY_DIR}/rundir/$<CONFIGURATION>/bin/${BIT_SUFFIX}/")

set(QT6DIR "D:/Third/Qt6_0_0/6.0.0/msvc2019_64")
list(APPEND CMAKE_PREFIX_PATH "${QT6DIR}")

# CMAKE 设置

# 引入cmake module
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Cmake/Modules")

include(Helpers)

# 指定DEBUG模式生成文件结尾符
if(NOT CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX d)
endif()
message(STATUS "current postfix: ${CMAKE_DEBUG_POSTFIX}")

# 包含当前目录
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt设置

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# c++标准

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")


# 编译标志


# 添加子目录

add_subdirectory(Cube)