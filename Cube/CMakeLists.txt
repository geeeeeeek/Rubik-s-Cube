project(Cube)


# 引入第三方库

find_package(Qt6Core REQUIRED)    
if(NOT Qt6Core_FOUND)
    message(FATAL_ERROR "Failed to find Qt6Core")
endif()

find_package(Qt6Quick REQUIRED)
if(NOT Qt6Quick_FOUND)
    message(FATAL_ERROR "Failed to find Qt6Quick")
endif()

# 添加源码

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp
)

set(INCLUDE
    # ${CMAKE_CURRENT_SOURCE_DIR}/Include/*
)

set(RESOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/Resource/Cube.qrc
)

# 编译

add_executable(${PROJECT_NAME} 
    ${SOURCE}
    ${INCLUDE}
    ${RESOURCE}
)


# 链接

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Quick
)

# 编译后命令
InstallToBinDir(${PROJECT_NAME})
DeployQt(${PROJECT_NAME})

# vs 设置
if(MSVC)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_COMMAND "${PRO_OUTPUT_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>")
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PRO_OUTPUT_DIR}")
endif()