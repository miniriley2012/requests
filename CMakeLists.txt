cmake_minimum_required(VERSION 3.18)
project(requests)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)

include(ThisProject)

add_library("${PROJECT_NAME}_HEADERS" INTERFACE)
target_include_directories("${PROJECT_NAME}_HEADERS" INTERFACE "${PROJECT_SOURCE_DIR}/include")

if (THIS_PROJECT)
    if (STRICT_COMPILE)
        if (MSVC)
            # warning level 4 and all warnings as errors
            add_compile_options(/W4 /WX)
        else ()
            # lots of warnings and all warnings as errors
            add_compile_options(-Wall -Wextra -pedantic -Werror)
        endif ()
    endif ()

    if (BUILD_TESTING)
        add_subdirectory(tests)
    endif ()
endif ()

add_subdirectory(src)