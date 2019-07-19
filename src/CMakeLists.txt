add_library(player STATIC inc/player.cpp)
add_library(log STATIC inc/Log.cpp)


add_executable(main main.cpp)

target_link_libraries(main
    player
    log
)
