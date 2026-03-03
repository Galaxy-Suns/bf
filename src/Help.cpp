#include "Help.h"
#include <iomanip>
#include <iostream>

Help::Help(std::string title, std::string usage, std::string version, std::string description) : title(title), usage(usage), version(version), description(description) {}

void Help::show() {
    std::cout << '\n'
              << "  " << title << '\n'
              << '\n'
              << "USAGE:\n"
              << "  " << usage << '\n'
              << '\n'
              << "VERSION:\n"
              << "  " << version << '\n'
              << '\n'
              << "DESCRIPTION\n"
              << description << '\n'
              << "AVAILABLE PARAMETERS\n";
    for (Parameter p : parameters) {
        std::cout << std::left;
        std::cout << "  " << std::setw(30) << p.short_name + ", " 
            + p.long_name <<  p.description << '\n';
    };
    std::cout << std::endl;
}

void Help::add_parameter(std::string short_name, std::string long_name, std::string description) {
    parameters.push_back(Parameter{short_name, long_name, description});
}
