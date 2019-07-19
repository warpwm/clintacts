#pragma once
#include <iostream>

class Player{
    private:
    int x, y;
    int speed;

    public:
    Player(int x, int y, int speed);
    void Move(int xa, int ya);
    int X();
    int Y();
    int S();
};

void increment();