find_program(DEPLOYQT_EXECUTABLE NAMES windeployqt HINTS "${EXEDIR}")
if(EXISTS "${OUTPATH}")
    execute_process(COMMAND ${DEPLOYQT_EXECUTABLE} "${OUTPATH}" "--debug" "--qmldir" "${QMLDIR}")
endif()