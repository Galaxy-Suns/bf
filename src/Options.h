#pragma once
#include <string>

struct Options {
    std::string command;
    bool input_number;
    bool output_number;
    bool enter;
    int visual;
    int visual_debug;
    int max_step;
    std::string file;
};

Options get_options(int argc, char *argv[]); 
