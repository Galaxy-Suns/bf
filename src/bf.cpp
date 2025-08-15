#include "bf.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <termcolor/termcolor.hpp>
#include <cctype>

const int MEM_SIZE = 30000;
const int MATCH_BUFFER_SIZE = 1000;

std::string valid_code(const std::string &origin); 
void output(uint8_t c, bool output_number, bool enter); 
uint8_t input(bool input_number); 
int loop_left(std::vector<int> &left, uint8_t c, int i, const std::string &bf_code); 
int find_right_loop(const std::string &bf_code, int i); 
int loop_right(std::vector<int> &left, uint8_t c, int i); 
void visualize(const std::string &bf_code, uint8_t *mem, int visual, int vi, int index); 

void bf_handler(
    std::string bf_code_origin, 
    bool output_number, 
    bool input_number, 
    int visual,
    bool enter,
    int max_step
) {
    std::string bf_code = valid_code(bf_code_origin);
    uint8_t mem[MEM_SIZE]{0};
    int index = 0;
    std::vector<int> left;

    for(int i = 0; i < bf_code.size() && max_step != 0; i++, max_step--) {
        int vi = i;
        char c = bf_code[i];
        switch (c) {
        case '+':
            mem[index]++;
            break;
        case '-':
            mem[index]--;
            break;
        case '<':
            index--;
            break;
        case '>':
            index++;
            break;
        case '.':
            output(mem[index], output_number, enter);
            break;
        case ',':
            mem[index] = input(input_number);
            break;
        case '[':
            i = loop_left(left, mem[index], i, bf_code);
            break;
        case ']':
            i = loop_right(left, mem[index], i);
            break;
        }
        if (visual) visualize(bf_code, mem, visual, vi, index);
    }
}

void output(uint8_t c, bool output_number, bool enter) {
    if (output_number) std::cout << (int) c << std::flush;
    else std::cout << (char) c << std::flush;
    if (enter) std::cout << std::endl;
}

uint8_t input(bool input_number) { 
    std::cout << ">>> ";
    if (input_number) {
        int tmp;
        std::cin >> tmp;
        return tmp;
    } else {
        char tmp;
        std::cin >> tmp;
        return tmp;
    }
}

int loop_left(std::vector<int> &left, uint8_t c, int i, const std::string &bf_code) {
    left.push_back(i);
    if (c == 0) {
        i = find_right_loop(bf_code, i);
    }
    return i;
}

int find_right_loop(const std::string &bf_code, int i) {
    std::vector<int> stack;
    for (int ti = i + 1; ti < bf_code.size(); ti++) {
        if (bf_code[ti] == '[') stack.push_back(ti);
        else if(bf_code[ti] == ']') {
            if (stack.empty()) {
                return ti;
            }
            else stack.pop_back();
        }
    }
    return -1;
}

int loop_right(std::vector<int> &left, uint8_t c, int i) {
    if (c != 0) {
        i = left.back() - 1;
    }
    left.pop_back();
    return i;
}

void visualize(const std::string &bf_code, uint8_t *mem, int visual, int vi, int index) {
    for (int j = 0; j < bf_code.size(); j++) {
        if (vi == j) std::cout << termcolor::green;
        std::cout << bf_code[j];
        if (vi == j) std::cout << termcolor::reset;
    }
    std::cout << std::endl;
    for (int i = 0; i < visual; i++) {
        if (index == i) std::cout << termcolor::green;
        std::cout << (int) mem[i] << '\t';
        if (index == i) std::cout << termcolor::reset;
    }
    std::cout << std::endl;
    std::cout << termcolor::blue;
    std::ostringstream oss;
    bool printFlag = false;
    for (int i = 0; i < visual; i++) {
        char c = (char) mem[i];
        if(std::isprint(c)) {
            oss<< (char) mem[i] << '\t';
            printFlag = true;
        }
        else oss << ' ' << '\t';
    }
    if (printFlag) std::cout << oss.str() << std::endl;
    std::cout << termcolor::reset;
    std::cout << "----" << std::endl;
}

std::string valid_code(const std::string &origin) {
    std::istringstream iss{origin};
    std::ostringstream oss;
    std::string line;
    while(std::getline(iss, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '/') break;
            if (std::string{".,+-<>[]"}.find(line[i]) != std::string::npos) oss << line[i];
        }
    }
    return oss.str();
}
