cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(enduro2d-bootstrap)

#
# linking
#

if(MSVC)
    option(BUILD_WITH_STATIC_CRT "Use static C runtime library" ON)
    if(BUILD_WITH_STATIC_CRT)
        foreach(flag CMAKE_C_FLAGS
                     CMAKE_C_FLAGS_DEBUG
                     CMAKE_C_FLAGS_RELEASE
                     CMAKE_C_FLAGS_MINSIZEREL
                     CMAKE_C_FLAGS_RELWITHDEBINFO
                     CMAKE_CXX_FLAGS
                     CMAKE_CXX_FLAGS_DEBUG
                     CMAKE_CXX_FLAGS_RELEASE
                     CMAKE_CXX_FLAGS_MINSIZEREL
                     CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
            endif()
            if(${flag} MATCHES "/MDd")
                string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
            endif()
        endforeach()
    endif()
endif()

#
# enduro2d
#

set(E2D_BUILD_SAMPLES OFF CACHE INTERNAL "" FORCE)
set(E2D_BUILD_UNTESTS OFF CACHE INTERNAL "" FORCE)
set(E2D_BUILD_WITH_STATIC_CRT ${BUILD_WITH_STATIC_CRT} CACHE INTERNAL "" FORCE)
add_subdirectory(modules/enduro2d)

#
# sources
#

file(GLOB_RECURSE PROJECT_SOURCES
    sources/*.*)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    ${PROJECT_SOURCES})

#
# executable
#

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} enduro2d)

#
# resources
#

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/bin
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/bin)
add_e2d_shared_libraries_to_target(${PROJECT_NAME})
