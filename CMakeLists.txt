#######################################################################
#                 CMAKE
#######################################################################
###### HUNTER PACKAGE MANAGER ######
include(cmake/Hunter.cmake)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.111.tar.gz"
    SHA1 "4189bbd869abe4eb69b5303d3f916c03d34dc154"
)

###### GENERAL SETTINGS ######
cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(PROJECT_NAME "clintacts")
project(${PROJECT_NAME})
if((NOT PROJECT_NAME))
  message(FATAL_ERROR "Project name must be specified!")
else()
    message ("\nPROJECT: ${CMAKE_PROJECT_NAME}")
endif ((NOT PROJECT_NAME))

#CPP STANDARD OPTIONS
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

######  VARIABLES  ######
set(${CMAKE_PROJECT_NAME}_SUMMARY               "A simple CXX contacts app")
set(${CMAKE_PROJECT_NAME}_VENDOR_NAME           "bresilla")
set(${CMAKE_PROJECT_NAME}_VENDOR_CONTACT        "trim.bresilla@gmail.com")
set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR         0)
set(${CMAKE_PROJECT_NAME}_VERSION_MINOR         1)
set(${CMAKE_PROJECT_NAME}_VERSION_PATCH         0)
set(PROJECT_VERSION                             "${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}.${${CMAKE_PROJECT_NAME}_VERSION_MINOR}.${${CMAKE_PROJECT_NAME}_VERSION_PATCH}")
set(PROJECT_PATH                               "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}     "${PROJECT_PATH}/cmake")
set(INCLUDE_PATH                               "${PROJECT_PATH}/src")
set(SRC_PATH                                   "${PROJECT_PATH}/src")
set(TEST_SRC_PATH                              "${PROJECT_PATH}/test")
set(EXTERNAL_PATH                              "${PROJECT_PATH}/thrd")
set(DOXYGEN_PATH                               "${PROJECT_PATH}/docs")
set(LIB_PATH                                   "${PROJECT_BINARY_DIR}/lib")
set(BIN_PATH                                   "${PROJECT_BINARY_DIR}/bin")
set(TEST_PATH                                  "${PROJECT_BINARY_DIR}/test")
set(TEST_NAME                                  "test_${PROJECT_NAME}")
set(EXECUTABLE_OUTPUT_PATH                      ${BIN_PATH})
set(LIBRARY_OUTPUT_PATH                         ${LIB_PATH})

######  FLAGS  ######
OPTION(BUILD_MAIN                              "Build main function"            ON)
OPTION(BUILD_TESTS                             "Build test packages"            OFF)
OPTION(BUILD_DOXYGEN_DOCS                      "Build Doxygen docs"             OFF)
OPTION(BUILD_SPHINX_DOCS                       "Build Doxygen docs with Sphinx" OFF)
OPTION(BUILD_DEPENDENCIES                      "Force build of dependencies"    OFF)
OPTION(ENABLE_COVERAGE                         "Enable teating coverage"        ON)
OPTION(CPPCHECK_ENABLE                         "Enable cpp checking"            ON)


####### BUILD TYPE #######
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()
string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if(NOT cmake_build_type_tolower STREQUAL "debug" AND
   NOT cmake_build_type_tolower STREQUAL "release" AND
   NOT cmake_build_type_tolower STREQUAL "minsizerel" AND
   NOT cmake_build_type_tolower STREQUAL "relwithdebinfo")
    message(FATAL_ERROR "Unknown build type \"${CMAKE_BUILD_TYPE}\". Allowed values are Debug, Release, RelWithDebInfo, and MinSizeRel (case-insensitive).")
endif()

if(cmake_build_type_tolower STREQUAL "debug")
    OPTION(DEBUGGING  "check if it's in debug mode"  ON)
else()
    OPTION(DEBUGGING  "check if it's in debug mode"  OFF)
endif()


####### COMPILER ######
include(Warnings)
if(NOT DEBUGGING)
    message ("BUILD TYPE: ${CMAKE_BUILD_TYPE}\n")
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    include(LTO)
    include(Packaging)
else()
    message ("BUILD TYPE: ${CMAKE_BUILD_TYPE}\n")
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    include(CTest)
    find_package(codecov)
endif()


#SUBDIRECTORIES (they must have their own CMakeLists.txt)

if(DEBUGGING)
    enable_testing()
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
    add_subdirectory(${PROJECT_SOURCE_DIR}/docs)
endif()
add_subdirectory(${PROJECT_SOURCE_DIR}/thrd EXCLUDE_FROM_ALL)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)



##### WIP
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


