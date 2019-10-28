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

#argument passing
add_library(args INTERFACE)
target_include_directories(
    args
    INTERFACE
    args # note : will expose the parts/ folder...
)

#YAML parsing
add_library(yaml-cpp INTERFACE)
target_include_directories(
    yaml-cpp
    INTERFACE
    yaml-cpp/include/yaml-cpp # note : will expose the parts/ folder...
)
include_directories(${YAML_CPP_SOURCE_DIR}/include)
