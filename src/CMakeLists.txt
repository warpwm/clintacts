add_library(contact STATIC inc/contacts.cpp)

add_executable(main main.cpp)

# target_link_libraries(contact helper)
target_link_libraries(main
    contact
)
