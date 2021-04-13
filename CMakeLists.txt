cmake_minimum_required(VERSION 3.17)

project(RubikCube)

message(STATUS "${PROJECT_NAME} start building")


# CMAKE 设置

# 引入cmake module
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Cmake")

include(Helpers)

# 指定DEBUG模式生成文件结尾符
if(NOT CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX d)
endif()
message(STATUS "current postfix: ${CMAKE_DEBUG_POSTFIX}")


# c++标准

set(CMAKE_CXX_STANDARD 11)
message(STATUS "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}");


# 编译标志


# 添加子目录

add_subdirectory(Cube)