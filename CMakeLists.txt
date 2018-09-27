cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)
project(enduro2d-bootstrap)

#
# linking mode
#

if(MSVC)
    option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC runtime library DLL" OFF)
    if(NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
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
# include enduro2d
#

set(E2D_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(E2D_BUILD_UNTESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(modules/enduro2d)

#
# project sources
#

file(GLOB_RECURSE PROJECT_SOURCES
    sources/*.*)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    ${PROJECT_SOURCES})

#
# project executable
#

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME}
    ${E2D_LIBRARIES})
target_include_directories(${PROJECT_NAME}
    PRIVATE ${E2D_INCLUDE_DIRS})
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)
