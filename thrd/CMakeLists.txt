#######################################################################
#                   THIRD PARTY LIB CMAKE
#######################################################################
# Doctest for unit tests
add_library(doctest INTERFACE)
target_include_directories(
    doctest
    INTERFACE
    doctest/doctest # note : will expose the parts/ folder...
)
include_directories(${DOCTEST_INCLUDE_DIR})

#YAML parsing
add_subdirectory(${THRD_SRC}/yaml-cpp EXCLUDE_FROM_ALL)
include_directories(${YAML_CPP_SOURCE_DIR}/include)
