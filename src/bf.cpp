#include "bf.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <termcolor/termcolor.hpp>
#include <cctype>
#include <filesystem>
#include "Options.h"

const int MEM_SIZE = 30000;
const int MATCH_BUFFER_SIZE = 1000;

std::string valid_code(const std::string &origin); 
std::string replace_command(const std::string &code_ncomment_nspace); 
std::string cmd_handler(const std::string &cmd_name, const std::string &cmd_body); 
void output(uint8_t c, const Options &opt); 
uint8_t input(const Options &opt); 
int loop_left(std::vector<int> &left, uint8_t c, int i, const std::string &bf_code); 
int find_right_loop(const std::string &bf_code, int i); 
int loop_right(std::vector<int> &left, uint8_t c, int i); 
void visualize(const std::string &bf_code, uint8_t *mem, int vi, int index, const Options &opt); 

void bf_handler(std::string bf_code_origin, const Options &opt) {
    std::string bf_code = valid_code(bf_code_origin);
    uint8_t mem[MEM_SIZE]{0};
    int index = 0;
    std::vector<int> left;

    int max_step = opt.max_step;
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
            output(mem[index], opt);
            break;
        case ',':
            mem[index] = input(opt);
            break;
        case '[':
            i = loop_left(left, mem[index], i, bf_code);
            break;
        case ']':
            i = loop_right(left, mem[index], i);
            break;
        }
        if (opt.visual) visualize(bf_code, mem, vi, index, opt);
    }
}

void output(uint8_t c, const Options &opt) {
    if (opt.output_number) std::cout << (int) c << std::flush;
    else std::cout << (char) c << std::flush;
    if (opt.enter) std::cout << std::endl;
}

uint8_t input(const Options &opt) { 
    std::cout << ">>> ";
    if (opt.input_number) {
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
        i = find_right_loop(bf_code, i) - 1;
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

void visualize(const std::string &bf_code, uint8_t *mem, int vi, int index, const Options &opt) {
    for (int j = 0; j < bf_code.size(); j++) {
        if (vi == j) std::cout << termcolor::green;
        std::cout << bf_code[j];
        if (vi == j) std::cout << termcolor::reset;
    }
    std::cout << std::endl;
    for (int i = 0; i < opt.visual; i++) {
        if (index == i) std::cout << termcolor::green;
        std::cout << (int) mem[i] << '\t';
        if (index == i) std::cout << termcolor::reset;
    }
    std::cout << std::endl;
    std::cout << termcolor::blue;
    std::ostringstream oss;
    bool printFlag = false;
    for (int i = 0; i < opt.visual; i++) {
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
    std::ostringstream code_ncomment_nspace, valid_code;
    std::string line;
    while(std::getline(iss, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '#') break;
            if (!std::isspace(line[i])) code_ncomment_nspace << line[i];
        }
    }
    std::string code_ncmt_nsp_ncmd = replace_command(code_ncomment_nspace.str());
    for (int i = 0; i < code_ncmt_nsp_ncmd.size(); i++) {
        if (std::string{".,+-<>[]"}.find(code_ncmt_nsp_ncmd[i]) != std::string::npos) {
            valid_code << code_ncmt_nsp_ncmd[i];
        }
    }
    return valid_code.str();
}

std::string replace_command(const std::string &code_ncomment_nspace) {
    int find_start = 0;
    std::ostringstream code_ncmt_nsp_ncmd;
    
    auto cmd_start = code_ncomment_nspace.find('!', find_start); // !
    if (cmd_start == std::string::npos) return code_ncomment_nspace;
    while (cmd_start != std::string::npos) {
        code_ncmt_nsp_ncmd << code_ncomment_nspace.substr(find_start, cmd_start + 1 - find_start);
        int cmd_name_end = code_ncomment_nspace.find('(', cmd_start + 1); // (
        std::string cmd_name = code_ncomment_nspace.substr(cmd_start + 1, cmd_name_end - cmd_start - 1);
        int cmd_end = code_ncomment_nspace.find(')', cmd_name_end + 1); // )
        std::string cmd_body = code_ncomment_nspace.substr(cmd_name_end + 1, cmd_end - cmd_name_end - 1);
        code_ncmt_nsp_ncmd << cmd_handler(cmd_name, cmd_body);
        find_start = cmd_end + 1;
        cmd_start = code_ncomment_nspace.find('!', find_start);
    }
    code_ncmt_nsp_ncmd << code_ncomment_nspace.substr(find_start, cmd_start + 1 - find_start);
    return code_ncmt_nsp_ncmd.str();
}


std::string cmd_handler(const std::string &cmd_name, const std::string &cmd_body) {
    std::ostringstream code;
    if(cmd_name ==  "include") {
        auto real_path = std::filesystem::current_path() / cmd_body;
        std::ifstream file{real_path};
        code << file.rdbuf();
        return valid_code(code.str());
    }
    return code.str();
}
