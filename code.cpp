#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>

const int length = 32;
const int hight = 11; 
const int tabl_size = length * hight;

std::array<int,tabl_size> null_array() { 
    std::array<int,tabl_size> null;
    for (int i = 0; i < tabl_size; i++) {
        null[i] = 0;
    }
    return null;
}

struct ListNode {
    std::array<int,tabl_size> val;
    ListNode* next;
    ListNode(): val(null_array()), next(nullptr) {}
    ListNode(std::array<int,tabl_size> x): val(x), next(nullptr) {}
    ListNode(std::array<int,tabl_size> x, ListNode* n): val(x), next(n) {}
};

std::array<int,tabl_size> step(std::array<int,tabl_size> arr) {
    std::array<int, tabl_size> res; 
    for (int i = 0; i < hight; i++) {
        for (int j = 0; j < length; j++) {
            int count = 0;
            int k = 0, n = 0;
            int l = 3, m = 3;
            if (i == 0) {
                k = 1;
            }
            if (i == hight - 1) {
                l = 2;
            }
            for (k; k < l; k++) {
                if (j == 0) {
                    n = 1;
                } else {
                    n = 0;
                }
                if (j == length - 1) {
                    m = 2;
                } else {
                    m = 3;
                }
                for (n; n < m; n++) {
                    if (arr[length * (i + k - 1) + j + n - 1] == 1) {
                        count++;
                    }
                }
            }
            if (arr[length * i + j] == 0 && count == 3){
                res[length * i + j] = 1;
            } else if (arr[length * i + j] == 1 && (count == 3 || count == 4)){
                res [length * i + j] = 1;
            } else {
                res[length * i + j] = 0;
            }
        }
    }
    return res; 
}

bool alive(std::array<int,tabl_size> arr) {
    if (arr != null_array()) {
        return true;
    }
    return false;
}

bool no_period(std::array<int,tabl_size> arr, ListNode* mass){
    while (mass != nullptr) {
        if (mass->val == arr) {
            return false;
        }
        mass = mass->next;
    }
    return true;
}

void print(std::array<int,tabl_size> arr) {
    std::cout << std::endl;
    for (int i = 0; i < length; i++) {
            std::cout << " ___";
        }
    for (int j = 0; j < hight; j++) {
        std::cout << std::endl;
        for (int i = 0; i < length; i++) {
            std::cout << "|   ";
        }
        std::cout << "|" << std::endl << "|";
        for (int i = 0; i < length; i++) {
            std::cout << " ";
            if (arr[length * j + i] == 1) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
            std::cout << " ";
            std::cout << "|";
        }
        std::cout << std::endl;
        for (int i = 0; i < length; i++) {
            std::cout << "|___";
        }
        std::cout << "|";
    }
    std::cout << std::endl << std::endl;
}

ListNode* add_array(std::array<int,tabl_size> arr, ListNode* head) {
    ListNode* result = new ListNode(arr, head);
    return result;
}


int main() {
    ListNode* head = nullptr;
    std::array <int, tabl_size> start = null_array();
    for (int i = 0; i < tabl_size; i++) {
        start[i] = std::rand() % 2;
    }
    while (alive(start) && no_period(start, head)) {
        sleep(1);
        std::system("clear");
        head = add_array(start, head);
        start = step(start); 
        print(start);
    }
}