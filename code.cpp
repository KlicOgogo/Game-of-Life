#include <array>
#include <iostream>
#include <list>
#include <unistd.h>

class Table{
    public:
        static const int width = 32;
        static const int height = 11;
        static const int table_size =  width * height;
};


std::array<int,Table::table_size> step(std::array<int,Table::table_size>& arr) {
    std::array<int, Table::table_size> res; 
    for (int i = 0; i < Table::height; i++) {
        for (int j = 0; j < Table::width; j++) {
            int count = 0;
            int k = 0, n = 0;
            int l = 3, m = 3;
            if (i == 0) {
                k = 1;
            }
            if (i == Table::height - 1) {
                l = 2;
            }
            for (k; k < l; k++) {
                if (j == 0) {
                    n = 1;
                } else {
                    n = 0;
                }
                if (j == Table::width - 1) {
                    m = 2;
                } else {
                    m = 3;
                }
                for (n; n < m; n++) {
                    if (arr[Table::width * (i + k - 1) + j + n - 1] == 1) {
                        count++;
                    }
                }
            }
            if (arr[Table::width * i + j] == 0 && count == 3){
                res[Table::width * i + j] = 1;
            } else if (arr[Table::width * i + j] == 1 && (count == 3 || count == 4)){
                res[Table::width * i + j] = 1;
            } else {
                res[Table::width * i + j] = 0;
            }
        }
    }
    return res; 
}

bool is_alive(std::array<int,Table::table_size>& arr) {
    std::array<int,Table::table_size> null_array = {};
    if (arr != null_array) {
        return true;
    }
    return false;
}

bool no_period(std::array<int,Table::table_size>& arr, std::list<std::array<int,Table::table_size>> mass){
    while (mass.size() != 0) {
        if (mass.front() == arr) {
            return false;
        }
        mass.pop_front();
    }
    return true;
}

void print(std::array<int,Table::table_size>& arr) {
    std::cout << std::endl;
    for (int i = 0; i < Table::width; i++) {
            std::cout << " ___";
        }
    for (int j = 0; j < Table::height; j++) {
        std::cout << std::endl;
        for (int i = 0; i < Table::width; i++) {
            std::cout << "|   ";
        }
        std::cout << "|" << std::endl << "|";
        for (int i = 0; i < Table::width; i++) {
            std::cout << " ";
            if (arr[Table::width * j + i] == 1) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
            std::cout << " ";
            std::cout << "|";
        }
        std::cout << std::endl;
        for (int i = 0; i < Table::width; i++) {
            std::cout << "|___";
        }
        std::cout << "|";
    }
    std::cout << std::endl << std::endl;
}

int main() {
    std::list<std::array<int,Table::table_size>> head;
    std::array <int, Table::table_size> start = {};
    for (int i = 0; i < Table::table_size; i++) {
        start[i] = std::rand() % 2;
    }
    while (is_alive(start) && no_period(start, head)) {
        sleep(1);
        std::system("clear");
        head.push_back(start);
        start = step(start); 
        print(start);
    }
}