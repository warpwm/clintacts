add_executable(${PROJECT_NAME} main.cpp)
add_library(contact STATIC inc/contacts.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

link_directories(/usr/lib)

target_link_libraries(contact crypt)
target_link_libraries(contact yaml-cpp${CMAKE_STATIC_LIBRARY_SUFFIX})

# target_include_directories(main PRIVATE /usr/include/cdk)

target_link_libraries(${PROJECT_NAME}
    contact
    # ncurses${CMAKE_STATIC_LIBRARY_SUFFIX}
    cdk${CMAKE_STATIC_LIBRARY_SUFFIX}
)
