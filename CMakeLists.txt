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

if(WIN32)
    if(MSVC)
        # 设置警告等级，/W3
        if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/W3" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
        endif()
    endif()

    # 禁止4127 4201 警告
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4127 /wd4201")

    # 设置RelWithDebinfo
    # Zi 生成单独PDB文件
    # MP 多核编译
    # Od 关闭程序中的所有优化并加快编译速度
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Zi /MP /Od")

    # 添加预编译宏 DEBUG _DEBUG
    set(CMAKE_CXX_FLAGS_DEBUG "/DDEBUG=1 /D_DEBUG=1 ${CMAKE_CXX_FLAGS_DEBUG}")

    # 禁止链接器生成带有安全异常处理程序表的映像（为了兼容其他模块，降低安全性）
    if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
		set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")
	endif()
endif()

# 添加子目录

add_subdirectory(Cube)