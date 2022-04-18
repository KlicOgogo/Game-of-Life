#include "game_of_life.h"

GameOfLife::GameOfLife(): width_(32), height_(11), table_size_(32 * 11) {
    table.resize(table_size_);
    random();
};
        
GameOfLife::GameOfLife(int width, int height): width_(width), height_(height), table_size_(width * height) {
    table.resize(table_size_);
    random();
};

void GameOfLife::step() { 
    add_to_list_of_mas();
    std::vector <int> res(table_size_); 
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            int count = 0;
            count += (i > 0 && j > 0 && table[width_ * (i - 1) + (j - 1)] == 1);
            count += (i > 0 && table[width_ * (i - 1) + j] == 1);
            count += (i > 0 && j + 1 < width_ && table[width_ * (i - 1) + (j + 1)] == 1);
            count += (j > 0 && table[width_ * i + (j - 1)] == 1);
            count += (j + 1 < width_ && table[width_ * i + (j + 1)] == 1);
            count += (i + 1 < height_ && j > 0 && table[width_ * (i + 1) + (j - 1)] == 1);
            count += (i + 1 < height_ && table[width_ * (i + 1) + j] == 1);
            count += (i + 1 < height_ && j + 1 < width_ && table[width_ * (i + 1) + (j + 1)] == 1);
            if (table[width_ * i + j] == 0 && count == 3) {
                res[width_ * i + j] = 1;
            } else if (table[width_ * i + j] == 1 && (count == 2 || count == 3)) {
                res[width_ * i + j] = 1;
            } else {
                res[width_ * i + j] = 0;
            }
        }
    }
    table = res; 
}

bool GameOfLife::can_step() const {
    if (is_alive() && no_period()) {
        return true;
    } else {
        return false;
    }
}

void GameOfLife::print() const {
    std::cout << std::endl;
    for (int i = 0; i < width_; i++) {
        std::cout << " ___";
    }
    for (int j = 0; j < height_; j++) {
        std::cout << std::endl;
        for (int i = 0; i < width_; i++) {
            std::cout << "|   ";
        }
        std::cout << "|" << std::endl << "|";
        for (int i = 0; i < width_; i++) {
            std::cout << " ";
            if (table[width_ * j + i] == 1) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
            std::cout << " ";
            std::cout << "|";
        }
        std::cout << std::endl;
        for (int i = 0; i < width_; i++) {
            std::cout << "|___";
        }
        std::cout << "|";
    }
    std::cout << std::endl << std::endl;
} 

void GameOfLife::random() {
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);
    for (int i = 0; i < table_size_; i++) {
        table[i] = distrib(gen);
    }
}

void GameOfLife::add_to_list_of_mas() {
    state_history_.push_back(table);
}
        
bool GameOfLife::is_alive() const {
    std::vector<int> null_vector(table_size_);
    return table != null_vector;
}

bool GameOfLife:: no_period() const {
    std::list<std::vector<int>> mass = state_history_;
    while (mass.size() != 0) {
        if (mass.front() == table) {
            return false;
        }
        mass.pop_front();
    }       
    return true;
}
