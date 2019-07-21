add_library(helper STATIC inc/helpers.cpp)
add_library(contact STATIC inc/commands.cpp)


add_executable(main main.cpp)

target_link_libraries(contact helper)
target_link_libraries(main
    helper
    contact
)
