#include <array>
#include <iostream>
#include <list>
#include <unistd.h>

const int width = 32;
const int height = 11; 
const int table_size = width * height;

/*std::array<int,table_size> null_array() { 
    std::array<int,table_size> null;
    for (int i = 0; i < table_size; i++) {
        null[i] = 0;
    }
    return null;
}*/

struct ListNode {
    std::array<int,table_size> val;
    ListNode* next;
    ListNode(): val({}), next(nullptr) {}
    ListNode(std::array<int,table_size> x): val(x), next(nullptr) {}
    ListNode(std::array<int,table_size> x, ListNode* n): val(x), next(n) {}
};

std::array<int,table_size> step(std::array<int,table_size> arr) {
    std::array<int, table_size> res; 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int count = 0;
            int k = 0, n = 0;
            int l = 3, m = 3;
            if (i == 0) {
                k = 1;
            }
            if (i == height - 1) {
                l = 2;
            }
            for (k; k < l; k++) {
                if (j == 0) {
                    n = 1;
                } else {
                    n = 0;
                }
                if (j == width - 1) {
                    m = 2;
                } else {
                    m = 3;
                }
                for (n; n < m; n++) {
                    if (arr[width * (i + k - 1) + j + n - 1] == 1) {
                        count++;
                    }
                }
            }
            if (arr[width * i + j] == 0 && count == 3){
                res[width * i + j] = 1;
            } else if (arr[width * i + j] == 1 && (count == 3 || count == 4)){
                res [width * i + j] = 1;
            } else {
                res[width * i + j] = 0;
            }
        }
    }
    return res; 
}

bool is_alive(std::array<int,table_size> arr) {
    std::array<int,table_size> null_array = {};
    if (arr != null_array) {
        return true;
    }
    return false;
}

bool no_period(std::array<int,table_size> arr, ListNode* mass){
    while (mass != nullptr) {
        if (mass->val == arr) {
            return false;
        }
        mass = mass->next;
    }
    return true;
}

void print(std::array<int,table_size> arr) {
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
            if (arr[width * j + i] == 1) {
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

ListNode* add_array(std::array<int,table_size> arr, ListNode* head) {
    ListNode* result = new ListNode(arr, head);
    return result;
}

int main() {
    ListNode* head = nullptr;
    std::array <int, table_size> start = {};
    for (int i = 0; i < table_size; i++) {
        start[i] = std::rand() % 2;
    }
    /*while (is_alive(start) && no_period(start, head)) {
        sleep(1);
        std::system("clear");
        head = add_array(start, head);
        start = step(start); 
        print(start);
    }*/
}