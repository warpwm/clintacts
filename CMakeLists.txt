##############################################################################################################################################
#                 GLOBAL
##############################################################################################################################################
###### HUNTER PACKAGE MANAGER ######
include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
    SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
)

###### VERSION AND NAME ######
cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(PROJECT_NAME "clintacts")
project(${PROJECT_NAME})
if((NOT PROJECT_NAME))
    message(FATAL_ERROR "Project name must be specified!")
endif ((NOT PROJECT_NAME))
message ("\nPROJECT: ${CMAKE_PROJECT_NAME}")


##############################################################################################################################################
#               VARIABLES
##############################################################################################################################################
set(${CMAKE_PROJECT_NAME}_SUMMARY               "A simple contacts manager for CLI")
set(${CMAKE_PROJECT_NAME}_VENDOR_NAME           "bresilla")
set(${CMAKE_PROJECT_NAME}_VENDOR_CONTACT        "trim.bresilla@gmail.com")
set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR         0)
set(${CMAKE_PROJECT_NAME}_VERSION_MINOR         1)
set(${CMAKE_PROJECT_NAME}_VERSION_PATCH         0)
set(PROJECT_VERSION                             "${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}.${${CMAKE_PROJECT_NAME}_VERSION_MINOR}.${${CMAKE_PROJECT_NAME}_VERSION_PATCH}")
set(CMAKE_MODULE_PATH                          "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(PROJECT_PATH                               "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROJECT_BUILD                              "${PROJECT_PATH}/build")

set(SRC_SRC                                    "${PROJECT_PATH}/source")
set(INC_SRC                                    "${PROJECT_PATH}/include")
set(EXT_SRC                                    "${PROJECT_PATH}/external")
set(UTL_SRC                                    "${PROJECT_PATH}/util")
set(TEST_SRC                                   "${PROJECT_PATH}/test")

set(LIB_BUILD                                  "${PROJECT_BUILD}/lib")
set(BIN_BUILD                                  "${PROJECT_BUILD}/bin")
set(DOCS_BUILD                                 "${PROJECT_BUILD}/docs")
set(EXECUTABLE_OUTPUT_PATH                     ${BIN_BUILD})
set(LIBRARY_OUTPUT_PATH                        ${LIB_BUILD})


##############################################################################################################################################
#                 BUILD
##############################################################################################################################################
string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if(NOT cmake_build_type_tolower STREQUAL "debug" AND NOT cmake_build_type_tolower STREQUAL "release" AND NOT cmake_build_type_tolower STREQUAL "fastdebug" AND NOT cmake_build_type_tolower STREQUAL "fastrelease")
    message(FATAL_ERROR "Unknown build type \"${CMAKE_BUILD_TYPE}\". Allowed values are Debug, Release, FastDebug, and FastRelease (case-insensitive).")
endif()
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()


##############################################################################################################################################
#                 COMPILER
##############################################################################################################################################
include(Warnings)
#CPP STANDARD OPTIONS
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if((cmake_build_type_tolower STREQUAL "release") OR (cmake_build_type_tolower STREQUAL "fastrelease"))
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    include(LTO)
    include(Packaging)
    option(BUILD_MAIN                                  "Build main function"            ON)
    if(cmake_build_type_tolower STREQUAL "release")
        option(ENABLE_DOCUMENT                         "Enable documentation"           ON)
    endif()
elseif((cmake_build_type_tolower STREQUAL "debug") OR (cmake_build_type_tolower STREQUAL "fastdebug"))
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    option(BUILD_MAIN                                  "Build main function"            ON)
    if(cmake_build_type_tolower STREQUAL "debug")
        option(BUILD_TESTS                             "Build test units"               ON)
        option(ENABLE_COVERAGE                         "Enable testing coverage"        ON)
        option(ENABLE_SANITIZERS                       "Enable langtidy and cppcheck"   ON)
        option(ENABLE_DOCUMENT                         "Enable documentation"           ON)
        option(ENABLE_MEMCHECK                         "Enable memory leak check"       ON)
    endif()
endif()
message ("BUILD TYPE: ${CMAKE_BUILD_TYPE}\n")


##############################################################################################################################################
#                   EXTERNAL
##############################################################################################################################################
#Use fmtlib for formatting
add_subdirectory(${EXT_SRC}/fmt EXCLUDE_FROM_ALL)
target_set_warnings(fmt DISABLE ALL) # Treat fmtlib as a system include as to ignore the warnings
set_target_properties(fmt PROPERTIES FOLDER "external")

#Use spdlog for logging, and tell it to use our version of fmtlib
# add_subdirectory(${EXT_SRC}/spdlog ${EXT_SRC}/spdlog EXCLUDE_FROM_ALL)
# target_compile_definitions(spdlog INTERFACE SPDLOG_FMT_EXTERNAL)
# file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")

add_subdirectory(${EXT_SRC}/yaml-cpp EXCLUDE_FROM_ALL)
include_directories(${YAML_CPP_SOURCE_DIR}/include)

add_subdirectory(${EXT_SRC}/FTXUI EXCLUDE_FROM_ALL)
set(FTXUI screen dom component)
include_directories(${EXT_SRC}/FTXUI/include)

set(EXTERN fmt yaml-cpp ${FTXUI})

##############################################################################################################################################
#                   EXTERNAL
##############################################################################################################################################
# LET LD SEARCH HERE (avoid, better use find_library())
# link_directories(/usr/lib)

# EIGEN
# find_package(Eigen3 REQUIRED)
# if(Eigen3_FOUND)
# message ("Eigen3 FOUND")
# target_include_directories(${PROJECT_NAME} PRIVATE ${EIGEN3_INCLUDE_DIR})
# NCURSES
find_package(Curses REQUIRED)
if(CURSES_FOUND)
    message ("CURSES_FOUND")
endif()


##############################################################################################################################################
#                   SOURCE
##############################################################################################################################################

file(GLOB UTIL_FILES "${UTL_SRC}/*.hpp")
file(GLOB HEAD_FILES "${INC_SRC}/${PROJECT_NAME}/*.h" "${INC_SRC}/${PROJECT_NAME}/*.hpp")
file(GLOB CODE_FILES "${SRC_SRC}/*.c" "${SRC_SRC}/*.cpp")

add_library(${PROJECT_NAME} ${UTIL_FILES} ${HEAD_FILES} ${CODE_FILES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
target_include_directories(${PROJECT_NAME} PRIVATE ${INC_SRC} SYSTEM INTERFACE ${INC_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${UTL_SRC} SYSTEM INTERFACE ${UTL_SRC})
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${EXTERN}
)

foreach(FILE ${CODE_FILES})
    if(ENABLE_SANITIZERS)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND clang-tidy ${FILE} -checks=*,-clang-diagnostic-unused-command-line-argument -header-filter=.*)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND cppcheck --enable=all ${FILE})
    endif()
endforeach()

##############################################################################################################################################
#                   EXECUTABLE
##############################################################################################################################################
add_executable(${PROJECT_NAME}_bin ${SRC_SRC}/main.cpp)
set_target_properties(${PROJECT_NAME}_bin PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

if(BUILD_MAIN)
target_link_libraries(${PROJECT_NAME}_bin
    PRIVATE
        ${PROJECT_NAME}
    PUBLIC
        ${EXTERN}
)
endif()

if(ENABLE_SANITIZERS)
    add_custom_command(TARGET ${PROJECT_NAME}_bin POST_BUILD COMMAND clang-tidy ${SRC_SRC}/main.cpp -checks=*,-clang-diagnostic-unused-command-line-argument -header-filter=.*)
    add_custom_command(TARGET ${PROJECT_NAME}_bin POST_BUILD COMMAND cppcheck --enable=all ${SRC_SRC}/main.cpp)
endif()


##############################################################################################################################################
#                   TESTS
###############################################################################################################################################
if(BUILD_TESTS)
    include(CTest)
    enable_testing()
    set(BUILD_TESTING_BCKP ${BUILD_TESTING})
    set(BUILD_TESTING OFF CACHE BOOL "Force disable of tests for external dependencies" FORCE)
    # function to automatically set up testing for specific file
    function (add_testing PATH)
        get_filename_component(NAME ${PATH} NAME_WE)
        set(NAME ${PROJECT_NAME}_${NAME})
        add_executable(${NAME} ${PATH})
        target_link_libraries(${NAME} PRIVATE ${PROJECT_NAME})
        add_test(NAME ${NAME} COMMAND ${EXECUTABLE_OUTPUT_PATH}/${NAME})
        if(ENABLE_COVERAGE)
            add_custom_command(TARGET ${NAME} POST_BUILD COMMAND kcov --include-pattern=${SRC_SRC} ${PROJECT_BINARY_DIR}/cover ${PROJECT_BINARY_DIR}/bin/${NAME})
        endif()
    endfunction(add_testing)
    # find each test and apply testing
    file(GLOB TEST_FILES "test/*.c" "test/*.cpp")
    if(BUILD_TESTS)
        foreach(A_FILE ${TEST_FILES})
            add_testing(${A_FILE})
        endforeach()
    endif()
endif()

###### CHECKING EXECUTABLE FOR MEMORY LEAK ######
if(ENABLE_MEMCHECK)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND valgrind --leak-check=yes ${BIN_BUILD}/${PROJECT_NAME})
endif()


##############################################################################################################################################
#                   DOCUMENTATION
###############################################################################################################################################
file(MAKE_DIRECTORY "${DOCS_BUILD}")
if(ENABLE_DOCUMENT)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND standardese --output-format=html --input.blacklist_file=CMakeLists.txt ${SRC_SRC} WORKING_DIRECTORY ${DOCS_BUILD})
endif()


##############################################################################################################################################
#                   INSTALLATION
###############################################################################################################################################
install(TARGETS ${PROJECT_NAME}_bin DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY "${LIB_BUILD}/" DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY "${INC_SRC}/" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
