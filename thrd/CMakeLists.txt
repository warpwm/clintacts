#######################################################################
#                   THIRD PARTY LIB CMAKE
#######################################################################
##### UPDATE GIT-SUBMODULES
find_package(Git REQUIRED)
if(GIT_FOUND AND EXISTS "${PROJECT_PATH}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT)
        execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            OUTPUT_VARIABLE PACKAGE_GIT_VERSION
            ERROR_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()


#Use fmtlib for formatting
if(${PROJECT_PATH}/src/fmt)
    execute_process(COMMAND git submodule update --init -- thrd/fmt WORKING_DIRECTORY ${PROJECT_PATH})
endif()
add_subdirectory(fmt EXCLUDE_FROM_ALL)
target_set_warnings(fmt DISABLE ALL)
# Add new external (non-interface) targets to this list
set_target_properties(fmt PROPERTIES FOLDER "external")


#Use spdlog for logging, and tell it to use our version of fmtlib
if(${PROJECT_PATH}/src/spdlog)
    execute_process(COMMAND git submodule update --init -- thrd/spdlog WORKING_DIRECTORY ${PROJECT_PATH})
endif()
add_subdirectory(spdlog EXCLUDE_FROM_ALL)
target_compile_definitions(spdlog INTERFACE SPDLOG_FMT_EXTERNAL)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")


#Doctest for unit tests
if(${PROJECT_PATH}/src/doctest)
    execute_process(COMMAND git submodule update --init -- thrd/doctest WORKING_DIRECTORY ${PROJECT_PATH})
endif()
add_library(doctest INTERFACE)
target_include_directories(
    doctest
    INTERFACE
    doctest/doctest # note : will expose the parts/ folder...
)
target_compile_features(doctest INTERFACE cxx_std_11)
include_directories(${DOCTEST_INCLUDE_DIR})

#argument passing
if(${PROJECT_PATH}/src/args)
    execute_process(COMMAND git submodule update --init -- thrd/args WORKING_DIRECTORY ${PROJECT_PATH})
endif()
add_library(args INTERFACE)
target_include_directories(
    args
    INTERFACE
    args # note : will expose the parts/ folder...
)

#argument passing
if(${PROJECT_PATH}/src/rang)
    execute_process(COMMAND git submodule update --init -- thrd/rang WORKING_DIRECTORY ${PROJECT_PATH})
endif()
add_library(rang INTERFACE)
target_include_directories(
    rang
    INTERFACE
    rang/include # note : will expose the parts/ folder...
)
