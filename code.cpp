#include <array>
#include <iostream>
#include <list>
#include <random>
#include <unistd.h>
#include <vector>

class GameOfLife {
    private:
        int width;
        int height;
        int table_size;
        std::vector<int> table = {};
        std::list<std::vector<int>> list_of_table;
    public:
        GameOfLife(): width(32), height(11), table_size(32 * 11) {
            table.resize(table_size);
        };
        GameOfLife(int width_, int height_): width(width_), height(height_), table_size(width * height) {
            table.resize(table_size);
        };
        void random() {
            std::random_device rd;  
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(0, 1);
            for (int i = 0; i < table_size; i++) {
                table[i] = distrib(gen);
            }
        }
        void step() {
            std::vector <int> res(table_size); 
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    int count = 0;
                    count += (i > 0 && j > 0 && table[width * (i - 1) + (j - 1)] == 1);
                    count += (i > 0 && table[width * (i - 1) + j] == 1);
                    count += (i > 0 && j + 1 < width && table[width * (i - 1) + (j + 1)] == 1);
                    count += (j > 0 && table[width * i + (j - 1)] == 1);
                    count += (j + 1 < width && table[width * i + (j + 1)] == 1);
                    count += (i + 1 < height && j > 0 && table[width * (i + 1) + (j - 1)] == 1);
                    count += (i + 1 < height && table[width * (i + 1) + j] == 1);
                    count += (i + 1 < height && j + 1 < width && table[width * (i + 1) + (j + 1)] == 1);
                    if (table[width * i + j] == 0 && count == 3) {
                        res[width * i + j] = 1;
                    } else if (table[width * i + j] == 1 && (count == 2 || count == 3)) {
                        res[width * i + j] = 1;
                    } else {
                        res[width * i + j] = 0;
                    }
                }
            }
            table = res;  
        }
        bool is_alive() {
            std::vector<int> null_vector = {};
            return table != null_vector;
        }
        bool no_period() {
            std::list<std::vector<int>> mass = list_of_table;
            while (mass.size() != 0) {
                if (mass.front() == table) {
                    return false;
                }
                mass.pop_front();
            }       
            return true;
        }
        void add_to_list_of_mas() {
            list_of_table.push_back(table);
        }
        void print() {
            std::cout << std::endl;
            for (int i = 0; i < width; i++) {
                    std::cout << " ___";
            }
            for (int j = 0; j < height; j++) {
                std::cout << std::endl;
                for (int i = 0; i < width; i++) {
                    std::cout << "|   ";
                }
                std::cout << "|" << std::endl << "|";
                for (int i = 0; i < width; i++) {
                    std::cout << " ";
                    if (table[width * j + i] == 1) {
                        std::cout << "*";
                    } else {
                        std::cout << " ";
                    }
                    std::cout << " ";
                    std::cout << "|";
                }
                std::cout << std::endl;
                for (int i = 0; i < width; i++) {
                    std::cout << "|___";
                }
                std::cout << "|";
            }
            std::cout << std::endl << std::endl;
        }
};

int main() {
    int width1, height1;
    std::cout << "Enter size of table: \n width (max 32) - ";
    std::cin >> width1; 
    std::cout << "height (max 11) - ";
    std::cin >> height1;
    GameOfLife game1(width1, height1);
    game1.random();
    GameOfLife game2 = game1; 
    while (game1.is_alive() && game1.no_period()) {
        sleep(1);
        std::system("clear");
        game1.add_to_list_of_mas();
        game1.step(); 
        game1.print();
    }
    game2.print();
}