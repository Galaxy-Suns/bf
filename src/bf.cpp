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

std::string remove_comment(const std::string &origin) {
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

void bf_handler(
    std::string bf_code_origin, 
    bool output_number, 
    bool input_number, 
    int visual,
    bool enter,
    int max_step
) {
    std::string bf_code = remove_comment(bf_code_origin);
    uint8_t mem[MEM_SIZE]{0};
    int index = 0;
    int left_order = 0;
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
            if (mem[index] == 0) {
                std::vector<int> stack;
                for (int ti = i + 1; ti < bf_code.size(); ti++) {
                    if (bf_code[ti] == '[') stack.push_back(ti);
                    else if(bf_code[ti] == ']') {
                        if (stack.empty()) {
                            i = ti - 1;
                            break;
                        }
                        else stack.pop_back();
                    }
                }
            }
            break;
        case ']':
            if (mem[index] != 0) {
                i = left.back() - 1;
            }
            left.pop_back();
            break;
        default: continue;
        }
        if (visual) {
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
        
    }
}
