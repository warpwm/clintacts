#add_executable(${PROJECT_NAME} main.cpp)

#######################################################################
#                   SOURCE CMAKE
#######################################################################
###### ADD THE MAIN FILE as EXECUTABLE ######
add_executable(${PROJECT_NAME} main.cpp)


###### INTERNAL LIBRARIES ######
add_library(contact STATIC ${PROJECT_SOURCE_DIR}/src/inc/contacts.cpp)

# add_library(utl INTERFACE)
# target_sources(utl INTERFACE ${PROJECT_SOURCE_DIR}/src/inc/utl/utils.hpp)

#per target include
# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
#or all in src include
include_directories(${PROJECT_SOURCE_DIR}/src})


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


###### LINK OTHER LIBRARIES ######
target_link_libraries(contact
    INTERFACE
        # utl
        crypt
    PRIVATE
        fmt
        yaml-cpp${CMAKE_STATIC_LIBRARY_SUFFIX}
        doctest)


target_link_libraries(${PROJECT_NAME}
    contact
    # ncurses${CMAKE_STATIC_LIBRARY_SUFFIX}
    # cdk${CMAKE_STATIC_LIBRARY_SUFFIX}
    )

###### INSTALL ######
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
