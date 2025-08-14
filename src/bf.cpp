#include "bf.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <termcolor/termcolor.hpp>

const int MEM_SIZE = 30000;
const int MATCH_BUFFER_SIZE = 1000;

void loop_match(std::string bf_code, int *match_buf) {
    std::vector<int> stack;
    int push_order = 0;
    for (int i = 0; i < bf_code.size(); i++) {
        char c = bf_code[i];
        if (c == '[') {
            stack.push_back(push_order);
            push_order++;
        }
        else if(c == ']') {
            int top = stack.back();
            stack.pop_back();
            match_buf[top] = i;
        }
    }
}

std::string remove_comment(std::string origin) {
    std::istringstream iss{origin};
    std::ostringstream oss;
    std::string line;
    while(std::getline(iss, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '/') break;
            oss << line[i];
        }
    }
    return oss.str();
}

void bf_handler(
    std::string bf_code_origin, 
    bool output_number, 
    bool input_number, 
    int visual,
    bool enter
) {
    std::string bf_code = remove_comment(bf_code_origin);
    uint8_t mem[MEM_SIZE]{0};
    int index = 0;
    int left_order = 0;
    int match_buf[MATCH_BUFFER_SIZE];
    std::vector<int> left;
    loop_match(bf_code, match_buf);
    for(int i = 0; i < bf_code.size(); i++) {
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
            if (output_number) std::cout << (int) mem[index] << std::flush;
            else std::cout << (char) mem[index] << std::flush;
            if (enter) std::cout << std::endl;
            break;
        case ',':
            std::cout << ">>> ";
            if (input_number) {
                int tmp;
                std::cin >> tmp;
                mem[index] = (char) tmp;
            } else {
                char tmp;
                std::cin >> tmp;
                mem[index] = tmp;
            }
            break;
        case '[':
            left.push_back(i);
            if (mem[index] == 0) i = match_buf[left_order] - 1;// jmp to ]
            left_order++;
            break;
        case ']':
            if (mem[index] != 0) {
                left_order--;
                i = left.back() - 1;
            }
            left.pop_back();
            break;
        default: continue;
        }
        if (visual) {
            std::cout << c << "\t\t";
            for (int i = 0; i < visual; i++) {
                if (index == i) std::cout << termcolor::green;
                std::cout << (int) mem[i] << '\t';
                if (index == i) std::cout << termcolor::reset;
            }
            std::cout << std::endl;
            std::cout << "----" << std::endl;
        }
        
    }
}
