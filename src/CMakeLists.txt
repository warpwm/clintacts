add_library(contact STATIC inc/contacts.cpp)
add_executable(main main.cpp)

target_include_directories(main PUBLIC ${PROJECT_SOURCE_DIR}/src)
link_directories(/usr/lib)

target_link_libraries(contact crypt)
target_link_libraries(contact yaml-cpp)

target_link_libraries(main
    contact
    ncurses
)
