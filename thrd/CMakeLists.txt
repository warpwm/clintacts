#######################################################################
#                   THIRD PARTY LIB CMAKE
#######################################################################
find_package(Git REQUIRED)

#Use fmtlib for formatting
if(${PROJECT_PATH}/src/fmt)
    execute_process(COMMAND git submodule update --init -- thrd/fmt WORKING_DIRECTORY ${PROJECT_PATH})
endif()
add_subdirectory(fmt EXCLUDE_FROM_ALL)
target_set_warnings(fmt DISABLE ALL)              # Treat fmtlib as a system include as to ignore the warnings
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
