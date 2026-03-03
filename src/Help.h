#pragma once
#include <string>
#include <vector>

class Help {
private:
    struct Parameter {
        std::string short_name;
        std::string long_name;
        std::string description;
    };
    std::string title;
    std::string usage;
    std::string version;
    std::string description;
    std::vector<Parameter> parameters;

public:
    Help(std::string title, std::string usage, std::string version, std::string description);
    void show();
    void add_parameter(std::string short_name, std::string long_name, std::string description);
};
