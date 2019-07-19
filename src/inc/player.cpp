#include "player.h"

void Player::Move(int xa, int ya){
    x += xa * speed;
    y += ya * speed;
}
Player::Player(int xa, int ya, int sa){
    x = xa;
    y = ya;
    speed = sa;
}
int Player::X(){return x;}
int Player::Y(){return y;}
int Player::S(){return speed;}


void increment(){
    static int i = 0;
    i++;
    std::cout << i << '\n';
}
