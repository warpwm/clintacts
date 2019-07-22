add_library(contact STATIC inc/contacts.cpp)
add_executable(main main.cpp)

link_directories(/usr/lib)


target_link_libraries(contact yaml-cpp)

target_link_libraries(main
    contact
    ncurses
)
