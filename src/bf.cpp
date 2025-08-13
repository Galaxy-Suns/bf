#include "bf.h"
#include <iostream>
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

void bf_handler(
    std::string bf_code, 
    bool output_number, 
    bool input_number, 
    int visual,
    bool enter
) {
    uint8_t mem[MEM_SIZE]{0};
    int index = 0;
    int left_i = 0;
    int left_order = 0;
    int match_buf[MATCH_BUFFER_SIZE];
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
            if (input_number) {
                int tmp;
                std::cin >> tmp;
                mem[index] = (char) tmp;
            } else {
                char tmp;
                std::cout << ">>> ";
                std::cin >> tmp;
                mem[index] = tmp;
            }
            break;
        case '[':
            left_i = i;
            if (mem[index] == 0) i = match_buf[left_order];// jmp to ]
            left_order++;
            break;
        case ']':
            if (mem[index] != 0) {
                left_order--;
                i = left_i; // jmp to [
            }
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
