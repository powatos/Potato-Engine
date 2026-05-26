cmake_minimum_required(VERSION 3.24)
project(PotatoEngine CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_Package(Curses REQUIRED)

if (Curses_FOUND AND NOT TARGET Curses::Curses)
    add_library(Curses::Curses INTERFACE IMPORTED)
    set_target_properties(Curses::Curses PROPERTIES
        INTERFACE_LINK_LIBRARIES "${CURSES_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${CURSES_INCLUDE_PATH}"
    )
endif()

file(GLOB_RECURSE ENGINE_SOURCES
    "Source/Internal/*.cpp"
    "Source/Internal/*.hpp"
)
file (GLOB_RECURSE THIRDPARTY_SOURCES
    "Source/ThirdParty/*.cpp"
    "Source/ThirdParty/*.cc"
    "Source/ThirdParty/*.hpp"
    "Source/ThirdParty/*.h"
)

add_library(PotatoEngine STATIC ${ENGINE_SOURCES} ${THIRDPARTY_SOURCES})

if (MSVC)
    target_compile_options(PotatoEngine PRIVATE
        /W4 /utf-8 /EHsc /D_CRT_SECURE_NO_WARNINGS
        $<$<CONFIG:DEBUG>:/Od>
        $<$<CONFIG:RELEASE>:/O2>
    )
else()
    target_compile_options(PotatoEngine PRIVATE 
        -Wall -Wpedantic
        $<$<CONFIG:DEBUG>:-g -O0>
        $<$<CONFIG:RELEASE>:-O3>
    )
endif()

target_include_directories(PotatoEngine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/Internal/Public>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/ThirdParty>
    $<INSTALL_INTERFACE:include> 
)
target_include_directories(PotatoEngine PRIVATE
    Source/Internal/Private
)

target_link_libraries(PotatoEngine PRIVATE Curses::Curses)
add_library(PotatoEngine::PotatoEngine ALIAS PotatoEngine)

file(GLOB_RECURSE GAME_SOURCES "Source/Program/*.cpp")

if (GAME_SOURCES)
    add_executable(Program ${GAME_SOURCES})

    if (MSVC)
        target_compile_options(Program PRIVATE
            /W4 /utf-8 /EHsc /D_CRT_SECURE_NO_WARNINGS
            $<$<CONFIG:DEBUG>:/Od>
            $<$<CONFIG:RELEASE>:/O2>
        )
    else()
        target_compile_options(Program PRIVATE 
            -Wall -Wpedantic
            $<$<CONFIG:DEBUG>:-g -O0>
            $<$<CONFIG:RELEASE>:-O3>
        )
    endif()

    target_include_directories(Program PRIVATE
        Source/Internal/Public
        Source/ThirdParty 
    )  

    target_link_libraries(Program PRIVATE
        "$<LINK_LIBRARY:WHOLE_ARCHIVE,PotatoEngine>"
        Curses::Curses
    )

    # add_custom_command(TARGET Program POST_BUILD
    # COMMAND ${CMAKE_COMMAND} -E copy_directory
    #         ${CMAKE_CURRENT_SOURCE_DIR}/Data/
    #         $<TARGET_FILE_DIR:Program>/Data/
    # )
    add_custom_command(TARGET Program POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Program>/Data
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/Data"
            "$<TARGET_FILE_DIR:Program>/Data"
    )
    
endif()

include(GNUInstallDirs)

install(TARGETS PotatoEngine
    EXPORT PotatoEngineTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY Source/Internal/Public/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PotatoEngine
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)
install(EXPORT PotatoEngineTargets
    FILE PotatoEngineTargets.cmake
    NAMESPACE PotatoEngine::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PotatoEngine
)

