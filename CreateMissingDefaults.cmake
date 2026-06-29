# Run at build time 

if(NOT EXISTS "${DST_DIR}")
    message(STATUS "PotatoEngine: Directory missing. Creating defaults at ${DST_DIR}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${SRC_DIR}" "${DST_DIR}")
endif()

if (CLEAR_LOGS AND EXISTS "${DST_DIR}")
    file(GLOB_RECURSE LOG_FILES "${DST_DIR}/*")
    foreach(LOG_FILE IN LISTS LOG_FILES)
        if(NOT IS_DIRECTORY "${LOG_FILE}")
            file(WRITE "${LOG_FILE}" "")
        endif()
    endforeach()
endif()