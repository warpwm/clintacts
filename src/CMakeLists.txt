#######################################################################
#                   SOURCE CMAKE
#######################################################################
###### ADD THE MAIN FILE as EXECUTABLE ######
add_executable(${PROJECT_NAME} main.cpp)
file(MAKE_DIRECTORY "${INCLUDE_BUILD}")

file(GLOB HEAD_FILES "inc/*.h" "inc/*.hpp")
file(GLOB CODE_FILES "inc/*.c" "inc/*.cpp")
file(GLOB SINGLE_FILES "sgl/*.hpp")


###### INTERNAL LIBRARIES ######
#function to add internal libs and copy headers
function (add_filelib FILE)
    get_filename_component(NAME ${FILE} NAME_WE)
    get_filename_component(PATH ${FILE} DIRECTORY)
    set(CODE ${PATH}/${NAME}.cpp)
    set(HEAD ${PATH}/${NAME}.h)
    add_library(${NAME} STATIC ${CODE})
    file(COPY "${HEAD}" DESTINATION "${INCLUDE_BUILD}")
    if(ENABLE_SANITIZERS)
        add_custom_command(TARGET ${NAME} POST_BUILD COMMAND clang-tidy ${FILE} -checks=*,-clang-diagnostic-unused-command-line-argument -header-filter=.*)
        # add_custom_command(TARGET ${NAME} POST_BUILD COMMAND iwyu ${FILE})
        add_custom_command(TARGET ${NAME} POST_BUILD COMMAND cppcheck --enable=all ${FILE})
    endif()
endfunction(add_filelib)
#function to add header only internal libraries
function (add_filehead FILE )
    get_filename_component(NAME ${FILE} NAME_WE)
    get_filename_component(PATH ${FILE} DIRECTORY)
    set(HEAD ${PATH}/${NAME}.hpp)
    add_library(${NAME} INTERFACE)
    target_sources(${NAME} INTERFACE ${HEAD})
endfunction(add_filehead)

#automatically add all libraries in /src
foreach(A_FILE ${CODE_FILES})
    # add_filelib(${PROJECT_PATH}/src/inc/classic.cpp)
    add_filelib(${A_FILE})
    message(STATUS "added library: ${A_FILE}")
endforeach()
#automatically add all header-onl-libraries in /sgl
foreach(A_FILE ${SINGLE_FILES})
    # add_filehead(${PROJECT_PATH}/src/sgl/utils.hpp)
    add_filehead(${A_FILE})
    message(STATUS "added header: ${A_FILE}")
endforeach()


###### EXTERNAL PACKAGES ######
# LET LD SEARCH HERE (avoid, better use find_library())
# link_directories(/usr/lib)

# EIGEN
# find_package(Eigen3 REQUIRED)
# if(Eigen3_FOUND)
    # message ("Eigen3 FOUND")
    # target_include_directories(${PROJECT_NAME} PRIVATE ${EIGEN3_INCLUDE_DIR})
# else()
    # message (FATAL_ERROR "Cannot find Eigen3")
# endif()


##### INCLUDE HEADERS
#per target include
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
#or all in src include
include_directories(${PROJECT_SOURCE_DIR}/src})


###### LINK OTHER LIBRARIES ######
###### LINK OTHER LIBRARIES ######
target_link_libraries(contacts
    INTERFACE
        # utl
        rang
        crypt
    PRIVATE
        fmt
        yaml-cpp${CMAKE_STATIC_LIBRARY_SUFFIX}
        doctest)


    ###### LAST LINK WITH EXECUTABLE ######
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        contacts
        args
        # ncurses${CMAKE_STATIC_LIBRARY_SUFFIX}
        # cdk${CMAKE_STATIC_LIBRARY_SUFFIX}
    )


#### TESGIN ############
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
        target_link_libraries(${NAME} PRIVATE doctest)
        add_test(NAME ${NAME} COMMAND ${EXECUTABLE_OUTPUT_PATH}/${NAME})
        if(ENABLE_COVERAGE)
            add_custom_command(TARGET ${NAME} POST_BUILD COMMAND kcov --include-pattern=${MAIN_SRC} ${PROJECT_BINARY_DIR}/cover ${PROJECT_BINARY_DIR}/bin/${NAME})
        endif()
    endfunction(add_testing)
    # find each test and apply testing
    file(GLOB TEST_FILES "../test/*.c" "../test/*.cpp")
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
#### DOCUMENTATION ######
file(MAKE_DIRECTORY "${DOCS_BUILD}")
if(ENABLE_DOCUMENT)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND standardese --output-format=html --input.blacklist_file=CMakeLists.txt ${MAIN_SRC} WORKING_DIRECTORY ${DOCS_BUILD})
endif()


###### INSTALL ######
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY "${LIB_BUILD}/" DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY "${INCLUDE_BUILD}/" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
