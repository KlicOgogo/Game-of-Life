#include <iostream>
#include <array>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <vector>


std::array<int,64> null_array() { 
    std::array<int,64> null;
    for (int i = 0; i < 64; i++) {
        null[i] = 0;
    }
    return null;
}


struct ListNode {
    std::array<int,64> val;
    ListNode* next;
    ListNode(): val(null_array()), next(nullptr) {}
    ListNode(std::array<int,64> x): val(x), next(nullptr) {}
    ListNode(std::array<int,64> x, ListNode* n): val(x), next(n) {}
};

std::array<int, 64> step(std::array<int, 64> arr) {
    std::array<int, arr.size()> res; 
    int s = sqrt(arr.size());
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            int count = 0;
            int k = 0, n = 0;
            int l = 3, m = 3;
            if (i == 0) {
                k = 1;
            }
            if (i == s - 1) {
                l = 2;
            }
            for (k; k < l; k++) {
                if (j == 0) {
                    n = 1;
                } else {
                    n = 0;
                }
                if (j == s - 1) {
                    m = 2;
                } else {
                    m = 3;
                }
                for (n; n < m; n++) {
                    if (arr[s * (i + k - 1) + j + n - 1] == 1) {
                        count++;
                    }
                }
            }
            if (arr[s * i + j] == 0 && count == 3){
                res[s * i + j] = 1;
            } else if (arr[s * i + j] == 1 && (count == 3 || count == 4)){
                res [s * i + j] = 1;
            } else {
                res[s * i + j] = 0;
            }
        }
    }
    return res; 
}

bool alive(std::array<int,64> arr) {
    if (arr != null_array()) {
        return true;
    }
    return false;
}


bool not_period(std::array<int,64> arr, ListNode* mass){
    while (mass != nullptr) {
        if (mass->val == arr) {
            return false;
        }
        mass = mass->next;
    }
    return true;
}

void print(std::array<int,64> arr) {
    int MeshSize = sqrt(arr.size());
    std::cout << std::endl;
    for (int i = 0; i < MeshSize; i++){
            std::cout << " ___";
        }
    for (int j = 0; j < MeshSize; j++) {
        std::cout << std::endl;
        for (int i = 0; i < MeshSize; i++) {
            std::cout << "|   ";
        }
        std::cout << "|" << std::endl << "|";
        for (int i = 0; i < MeshSize;i++) {
            std::cout << " ";
            if (arr[MeshSize * j + i] == 1) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
            std::cout << " ";
            std::cout << "|";
        }
        std::cout << std::endl;
        for (int i = 0; i < MeshSize; i++) {
            std::cout << "|___";
        }
        std::cout << "|";
    }
    std::cout << std::endl << std::endl;
}

ListNode* add_array(std::array<int,64> arr, ListNode* head) {
    ListNode* result = new ListNode(arr, head);
    return result;
}


int main() {
    const int size = 8;
    ListNode* head = nullptr;
    std::array<int,9> a = {1,2,4,0,1,3,4,5,1};
    std::array<int,9> b = {0,1,1,2,2,4,4,4,5};
    std::array <int, size * size> start = null_array();
    for (int i = 0; i < 9; i++){
        start[size * b[i] + a[i]] = 1;
    }
    /*for (int i = 0; i < size * size; i++) {
        start[i] = std::rand() % 2;
    }*/
    print(start);
    while (alive(start) && not_period(start, head)) {
        sleep(2);
        std::system("clear");
        head = add_array(start, head);
        start = step(start); 
        print(start);
    }
}