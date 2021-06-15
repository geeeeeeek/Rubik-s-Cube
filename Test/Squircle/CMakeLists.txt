project(Squircle)


# 引入第三方库

find_package(Qt6Core REQUIRED)    
if(NOT Qt6Core_FOUND)
    message(FATAL_ERROR "Failed to find Qt6Core")
endif()

find_package(Qt6Quick REQUIRED)
if(NOT Qt6Quick_FOUND)
    message(FATAL_ERROR "Failed to find Qt6Quick")
endif()

find_package(Qt6OpenGL REQUIRED)
if(NOT Qt6OpenGL_FOUND)
    message(FATAL_ERROR "Failed to find Qt6OpenGL")
endif()

find_package(Qt6Gui REQUIRED)
if(NOT Qt6Gui_FOUND)
    message(FATAL_ERROR "Failed to find Qt6Gui")
endif()

find_package(Qt6Qml REQUIRED)
if(NOT Qt6Qml_FOUND)
    message(FATAL_ERROR "Failed to find Qt6Qml")
endif()

# 添加源码

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/squircle.cpp
)

set(INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/squircle.h
)

set(RESOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/Resource/Squircle.qrc
)

# 编译

add_executable(${PROJECT_NAME} WIN32
    ${SOURCE}
    ${INCLUDE}
    ${RESOURCE}
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Test")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

# 链接

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt6::Core
    Qt6::Quick
    Qt6::Gui
    Qt6::OpenGL
    Qt6::Qml
)


# 编译后命令
InstallToBinDir(${PROJECT_NAME})
DeployQt(${PROJECT_NAME})

# vs 设置
if(MSVC)
    # set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_COMMAND "${PRO_OUTPUT_DIR}${PROJECT_NAME}/$<TARGET_FILE_NAME:${PROJECT_NAME}>")
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PRO_OUTPUT_DIR}/${PROJECT_NAME}")
endif()