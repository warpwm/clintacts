#include "inc/player.h"
#include "inc/Log.h"

#define LOG(x) std::cout << x << std::endl

int main() {
    Log log;
    log.setLevel(Log::LevelInfo);
    log.INFO("Sarting info here");
    log.WARN("starting warning here");
    log.ERROR("starting error here");

    //Player player(5, 5, 2);
    //player.Move(3, 5);
    //increment();
    //increment();
    //increment();
    //increment();

}