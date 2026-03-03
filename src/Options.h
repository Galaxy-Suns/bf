#pragma once
#include <string>
#include "Help.h"

struct Options {
    std::string command;
    bool input_number;
    bool output_number;
    bool enter;
    int visual;
    int visual_debug;
    int max_step;
    std::string file;
    bool help_enable;
    bool show_version;
};

Options get_options(int argc, char *argv[], Help &help); 
