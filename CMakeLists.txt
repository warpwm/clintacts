# -------------------------------------------------------------------------------------------------------------------------------------------
#                 GLOBAL
# -------------------------------------------------------------------------------------------------------------------------------------------
# HUNTER PACKAGE MANAGER
include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
    SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358" )

# VERSION AND NAME
cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
get_filename_component(NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)
set(PROJECT_NAME ${NAME})
project(${PROJECT_NAME})
if((NOT PROJECT_NAME))
    message(FATAL_ERROR "Project name must be specified!")
endif ((NOT PROJECT_NAME))
message ("\nPROJECT: ${CMAKE_PROJECT_NAME}")



# -------------------------------------------------------------------------------------------------------------------------------------------
#               VARIABLES
# -------------------------------------------------------------------------------------------------------------------------------------------
set(${CMAKE_PROJECT_NAME}_SUMMARY               "The ${PROJECT_NAME} project")
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
set(UTL_SRC                                    "${PROJECT_PATH}/utils")
set(TEST_SRC                                   "${PROJECT_PATH}/test")

set(LIB_BUILD                                  "${PROJECT_BUILD}/lib")
set(BIN_BUILD                                  "${PROJECT_BUILD}/bin")
set(DOCS_BUILD                                 "${PROJECT_BUILD}/docs")
set(EXECUTABLE_OUTPUT_PATH                     ${BIN_BUILD})
set(LIBRARY_OUTPUT_PATH                        ${LIB_BUILD})



# -------------------------------------------------------------------------------------------------------------------------------------------
#                 BUILD
# -------------------------------------------------------------------------------------------------------------------------------------------
string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if(NOT cmake_build_type_tolower STREQUAL "debug" AND NOT cmake_build_type_tolower STREQUAL "release" AND NOT cmake_build_type_tolower STREQUAL "fastdebug" AND NOT cmake_build_type_tolower STREQUAL "fastrelease")
    message(FATAL_ERROR "Unknown build type \"${CMAKE_BUILD_TYPE}\". Allowed values are Debug, Release, FastDebug, and FastRelease (case-insensitive).")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()



# -------------------------------------------------------------------------------------------------------------------------------------------
#                 COMPILER
# -------------------------------------------------------------------------------------------------------------------------------------------
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
        option(ENABLE_SANITIZERS                       "Enable clangtidy and cppcheck"   ON)
        option(ENABLE_DOCUMENT                         "Enable documentation"           ON)
        option(ENABLE_MEMCHECK                         "Enable memory leak check"       ON)
    endif()
endif()
message ("BUILD TYPE: ${CMAKE_BUILD_TYPE}\n")



# -------------------------------------------------------------------------------------------------------------------------------------------
#                   EXTERNAL
# -------------------------------------------------------------------------------------------------------------------------------------------
#Use fmtlib for formatting
add_subdirectory(${EXT_SRC}/fmt EXCLUDE_FROM_ALL)
target_set_warnings(fmt DISABLE ALL) # Treat fmtlib as a system include as to ignore the warnings
set_target_properties(fmt PROPERTIES FOLDER "external")

#use yaml-cpp
add_subdirectory(${EXT_SRC}/yaml-cpp EXCLUDE_FROM_ALL)
include_directories(${YAML_CPP_SOURCE_DIR}/include)

add_subdirectory(${EXT_SRC}/FTXUI EXCLUDE_FROM_ALL)
set(FTXUI screen dom component)
include_directories(${EXT_SRC}/FTXUI/include)

set(EXTERN fmt yaml-cpp ${FTXUI})
# set_target_properties(${EXTERN} PROPERTIES COMPILE_OPTIONS "-O2")



# -------------------------------------------------------------------------------------------------------------------------------------------
#                   LOCAL
# -------------------------------------------------------------------------------------------------------------------------------------------
# LET LD SEARCH HERE (avoid, better use find_library())
# link_directories(/usr/lib)

find_package(Curses REQUIRED)
if(CURSES_FOUND)
    message ("CURSES_FOUND")
endif()

#grouping local libraries
set(LOCEXT ncurses)



# -------------------------------------------------------------------------------------------------------------------------------------------
#                   SOURCE
# -------------------------------------------------------------------------------------------------------------------------------------------
add_library(UTILS INTERFACE)
target_include_directories(UTILS INTERFACE ${UTL_SRC}/)

function (add_source_lib NAME)
    file(GLOB HEAD_FILES "${INC_SRC}/${NAME}/*.h" "${INC_SRC}/${NAME}/*.hpp")
    file(GLOB CODE_FILES "${SRC_SRC}/${NAME}/*.c" "${SRC_SRC}/${NAME}/*.cpp")
    add_library(${NAME} ${HEAD_FILES} ${CODE_FILES})
    target_include_directories(${NAME} PRIVATE ${INC_SRC} SYSTEM INTERFACE ${INC_SRC})
    target_include_directories(${NAME} PRIVATE ${UTL_SRC} SYSTEM INTERFACE ${UTL_SRC})
    target_link_libraries(${NAME}
        PRIVATE
            ${UTILS}
            ${EXTERN}
            ${LOCEXT}
    )
    foreach(FILE ${CODE_FILES})
        if(ENABLE_SANITIZERS)
            # add_custom_command(TARGET ${NAME} POST_BUILD COMMAND clang-tidy ${FILE} -checks=*,-clang-diagnostic-unused-command-line-argument -header-filter=.*)
            add_custom_command(TARGET ${NAME} POST_BUILD COMMAND cppcheck --enable=all ${FILE})
        endif()
    endforeach()
endfunction(add_source_lib)

file(GLOB LIBRARIES RELATIVE ${SRC_SRC} "${SRC_SRC}/*")
list(REMOVE_ITEM LIBRARIES main.cpp)

foreach(LIB ${LIBRARIES})
    add_source_lib(${LIB})
endforeach()


# -------------------------------------------------------------------------------------------------------------------------------------------
#                   EXECUTABLE
# -------------------------------------------------------------------------------------------------------------------------------------------
if(BUILD_MAIN)
    add_executable(${PROJECT_NAME}_bin ${SRC_SRC}/main.cpp)
    set_target_properties(${PROJECT_NAME}_bin PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

    target_link_libraries(${PROJECT_NAME}_bin
        PUBLIC
            ${LIBRARIES}
        PRIVATE
            ${UTILS}
            ${EXTERN}
            ${LOCEXT}
    )

    if(ENABLE_SANITIZERS)
        # add_custom_command(TARGET ${PROJECT_NAME}_bin POST_BUILD COMMAND clang-tidy ${SRC_SRC}/main.cpp -checks=*,-clang-diagnostic-unused-command-line-argument -header-filter=.*)
        add_custom_command(TARGET ${PROJECT_NAME}_bin POST_BUILD COMMAND cppcheck --enable=all ${SRC_SRC}/main.cpp)
    endif()
endif()



# -------------------------------------------------------------------------------------------------------------------------------------------
#                   TESTS
# -------------------------------------------------------------------------------------------------------------------------------------------
if(BUILD_TESTS)
    include(CTest)
    enable_testing()
    set(BUILD_TESTING_BCKP ${BUILD_TESTING})
    set(BUILD_TESTING OFF CACHE BOOL "Force disable of tests for external dependencies" FORCE)

    function (add_testing PATH)
        get_filename_component(NAME ${PATH} NAME_WE)
        set(NAME ${PROJECT_NAME}_${NAME})
        add_executable(${NAME} ${PATH})
        target_link_libraries(${NAME} ${UTILS} ${LIBRARIES})
        add_test(NAME ${NAME} COMMAND ${EXECUTABLE_OUTPUT_PATH}/${NAME})
        if(ENABLE_COVERAGE)
            add_custom_command(TARGET ${NAME} POST_BUILD COMMAND kcov --include-pattern=${SRC_SRC} ${PROJECT_BINARY_DIR}/cover ${PROJECT_BINARY_DIR}/bin/${NAME})
        endif()
        if(ENABLE_MEMCHECK)
            find_program( MEMORYCHECK_COMMAND valgrind )
            set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )
            add_custom_command(TARGET ${NAME} POST_BUILD COMMAND valgrind --leak-check=yes ${PROJECT_BINARY_DIR}/bin/${NAME})
        endif()
    endfunction(add_testing)

    file(GLOB TEST_FILES "test/*.c" "test/*.cpp")
    if(BUILD_TESTS)
        foreach(A_FILE ${TEST_FILES})
            add_testing(${A_FILE})
        endforeach()
    endif()
endif()



# -------------------------------------------------------------------------------------------------------------------------------------------
#                   DOCUMENTATION
# -------------------------------------------------------------------------------------------------------------------------------------------
file(MAKE_DIRECTORY "${DOCS_BUILD}")
if(ENABLE_DOCUMENT)
    # add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND standardese --output-format=html --input.blacklist_file=CMakeLists.txt ${SRC_SRC} WORKING_DIRECTORY ${DOCS_BUILD})
endif()



# -------------------------------------------------------------------------------------------------------------------------------------------
#                   INSTALLATION
# -------------------------------------------------------------------------------------------------------------------------------------------
include(GNUInstallDirs)
# Install files.

if(BUILD_MAIN)
    install(TARGETS ${PROJECT_NAME}_bin DESTINATION /usr/local/bin)
endif()
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/lib)
install(DIRECTORY "${INC_SRC}/" DESTINATION /usr/local/include)
# Uninstall files.
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_MODULE_PATH}/Uninstall.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake"
        IMMEDIATE @ONLY)
    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake)
endif()

# Set up packager.
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${${CMAKE_PROJECT_NAME}_SUMMARY}")
set(CPACK_PACKAGE_VENDOR              "${${CMAKE_PROJECT_NAME}_VENDOR_NAME}")
set(CPACK_PACKAGE_DESCRIPTION_FILE    "${PROJECT_PATH}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE       "${PROJECT_PATH}/LICENSE.md")
set(CPACK_PACKAGE_VERSION_MAJOR       "${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR       "${${CMAKE_PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH       "${${CMAKE_PROJECT_NAME}_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY   "${CMAKE_PROJECT_NAME}")

SET(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER   "${${CMAKE_PROJECT_NAME}_VENDOR_NAME}")
include(CPack)
