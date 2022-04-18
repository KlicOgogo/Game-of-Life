#include "game_of_life.h"

int main() {
    int width1, height1;
    std::cout << "Enter size of table: \n width (max 32) - ";
    std::cin >> width1; 
    std::cout << "height (max 11) - ";
    std::cin >> height1;
    GameOfLife game1(width1, height1);
    while (game1.can_step()) {
        sleep(1);
        std::system("clear");
        game1.step(); 
        game1.print();
    }
    return 0;
}
