cmake_minimum_required(VERSION 3.24)
project(PotatoEngine CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CURSES_LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/ThirdParty/Platform/curses/lib")
set(CURSES_INCLUDE_BASEDIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/ThirdParty/Platform/curses/include")

if (WIN32)
    set(CURSES_LIBRARY "${CURSES_LIBS_DIR}/win/pdcurses.lib")
    set(CURSES_INCLUDE_DIR "${CURSES_INCLUDE_BASEDIR}/win")
elseif(APPLE)
    set(CURSES_LIBRARY "${CURSES_LIBS_DIR}/mac/libncursesw.a")
    set(CURSES_INCLUDE_DIR "${CURSES_INCLUDE_BASEDIR}/mac")
    list(APPEND CURSES_LIBRARY "-ltermcap")
else()
    set(CURSES_LIBRARY 
        "${CURSES_LIBS_DIR}/linux/libncursesw.a"
        "${CURSES_LIBS_DIR}/linux/libtinfo.a"
    )
    set(CURSES_INCLUDE_DIR "${CURSES_INCLUDE_BASEDIR}/linux")
endif()

file(GLOB_RECURSE ENGINE_SOURCES
    "Source/Internal/*.cpp"
    "Source/Internal/*.hpp"
)
file (GLOB_RECURSE THIRDPARTY_SOURCES
    "Source/ThirdParty/*.cpp"
    "Source/ThirdParty/*.cc"
)

add_library(PotatoEngine STATIC ${ENGINE_SOURCES} ${THIRDPARTY_SOURCES})

target_include_directories(PotatoEngine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/Internal/Public>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/ThirdParty/Public>
    $<INSTALL_INTERFACE:include> 
)
target_include_directories(PotatoEngine PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/Internal/Private>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/ThirdParty/Private>
    ${CURSES_INCLUDE_DIR}
)

if (MSVC)
    target_compile_options(PotatoEngine PRIVATE
        /W4 /utf-8 /EHsc /wd4100 /wd4244
        $<$<CONFIG:DEBUG>:/Od>
        $<$<CONFIG:RELEASE>:/O2>
    )
else()
    target_compile_options(PotatoEngine PRIVATE 
        -Wall -Wpedantic -Wno-unknown-pragmas -finput-charset=UTF-8 -fexec-charset=UTF-8
        $<$<CONFIG:DEBUG>:-g -O0>
        $<$<CONFIG:RELEASE>:-O3>
    )
endif()

target_compile_definitions(PotatoEngine PUBLIC
    PDC_STATIC_BUILD
    PDC_WIDE
    _CRT_SECURE_NO_WARNINGS
)

if (NOT WIN32)
    target_compile_definitions(PotatoEngine PUBLIC _XOPEN_SOURCE_EXTENDED)
endif()

target_link_libraries(PotatoEngine PRIVATE "${CURSES_LIBRARY}")
add_library(PotatoEngine::PotatoEngine ALIAS PotatoEngine)

function(PotatoEngineDefaults TARGET_NAME)
    if(NOT TARGET ${TARGET_NAME})
        message(FATAL_ERROR "PotatoEngineDefaults called on non-existent target ${TARGET_NAME}")
    endif()

    set(DATA_SRC "${PotatoEngine_SOURCE_DIR}/Data")
    set(DATA_DST "${PROJECT_SOURCE_DIR}/Data")
    
    set(LOGS_SRC "${PotatoEngine_SOURCE_DIR}/logs")
    set(LOGS_DST "${PROJECT_SOURCE_DIR}/logs")

    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -DSRC_DIR="${DATA_SRC}" -DDST_DIR="${DATA_DST}" 
                -P "${CMAKE_CURRENT_SOURCE_DIR}/CreateMissingDefaults.cmake"

        COMMAND ${CMAKE_COMMAND} -DSRC_DIR="${LOGS_SRC}" -DDST_DIR="${LOGS_DST}" 
                -P "${CMAKE_CURRENT_SOURCE_DIR}/CreateMissingDefaults.cmake"

        COMMAND ${CMAKE_COMMAND} -DCLEAR_LOGS=TRUE -DDST_DIR="${LOGS_DST}" 
                -P "${CMAKE_CURRENT_SOURCE_DIR}/CreateMissingDefaults.cmake"

        COMMENT "PotatoEngine: creating engine defaults..."
    )
endfunction()

if (PROJECT_IS_TOP_LEVEL)
    file(GLOB_RECURSE GAME_SOURCES "Source/Program/*.cpp")

    if (GAME_SOURCES)
        add_executable(Program ${GAME_SOURCES})

        if (MSVC)
            target_compile_options(Program PRIVATE
                /W4 /utf-8 /EHsc /D_CRT_SECURE_NO_WARNINGS /wd4100 /wd4244
                $<$<CONFIG:DEBUG>:/Od>
                $<$<CONFIG:RELEASE>:/O2>
            )
            target_link_options(Program PRIVATE "/NODEFAULTLIB:LIBCMT")
        else()
            target_compile_options(Program PRIVATE 
                -Wall -Wpedantic -Wno-unknown-pragmas -finput-charset=UTF-8 -fexec-charset=UTF-8
                $<$<CONFIG:DEBUG>:-g -O0>
                $<$<CONFIG:RELEASE>:-O3>
            )
        endif()

        target_include_directories(Program PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/Internal/Public>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/ThirdParty/Public>
        )

        target_link_libraries(Program PRIVATE
            "$<LINK_LIBRARY:WHOLE_ARCHIVE,PotatoEngine>"
        )
        PotatoEngineDefaults(Program)
        
    endif()
endif()

# include(GNUInstallDirs)

# install(TARGETS PotatoEngine
#     EXPORT PotatoEngineTargets
#     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )
# install(DIRECTORY Source/Internal/Public/
#     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PotatoEngine
#     FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
# )
# install(EXPORT PotatoEngineTargets
#     FILE PotatoEngineTargets.cmake
#     NAMESPACE PotatoEngine::
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PotatoEngine
# )

