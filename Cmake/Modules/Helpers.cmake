function(InstallToBinDir target)
    # if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    #     set(BIT_SUFFIX "64bit")
    # else()
    #     set(BIT_SUFFIX "32bit")
    # endif()

    add_custom_command(TARGET ${target} 
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy
        "$<TARGET_FILE:${target}>"
        "${PRO_OUTPUT_DIR}/$<TARGET_FILE_NAME:${target}>"
    )

    add_custom_command(TARGET ${target}
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}"
    "-DCONFIG=$<CONFIGURATION>"
    "-DFNAME=$<TARGET_FILE_NAME:${target}>"
    "-DINPUT=$<TARGET_FILE_DIR:${target}>"
    "-DOUTPUT=${PRO_OUTPUT_DIR}"
    -P "${CMAKE_SOURCE_DIR}/Cmake/Scripts/CopyDebugHelper.cmake"
    )
endfunction()

function(DeployQt target)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(BIT_SUFFIX "64bit")
    else()
        set(BIT_SUFFIX "32bit")
    endif()

    add_custom_command(TARGET ${target}
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}"
    "-DCONFIG=$<CONFIG>"
    "-DQMLDIR=${QT6DIR}/qml"
    "-DEXEDIR=${QT6DIR}/bin"
    "-DOUTPATH=${PRO_OUTPUT_DIR}/$<TARGET_FILE_NAME:${target}>"
    -P "${CMAKE_SOURCE_DIR}/Cmake/Scripts/DeployQtHelper.cmake"
    )
endfunction()