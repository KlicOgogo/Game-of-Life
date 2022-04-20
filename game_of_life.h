#pragma once

#include <iostream>
#include <list>
#include <random>
#include <unistd.h>
#include <vector>

class GameOfLife {
    public:
        GameOfLife();
        GameOfLife(int width, int height);
        void step();
        bool can_step() const;
        void print() const;
    private:
        int width_;
        int height_;
        int table_size_;
        std::vector<int> table = {};
        std::list<std::vector<int>> state_history_;
        void random();
        bool is_alive() const;
        bool no_period() const;
};
