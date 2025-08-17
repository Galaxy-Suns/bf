#include "bf.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Options.h"


int main(int argc, char *argv[]) {
    const Options opt = get_options(argc, argv);

    if (!opt.command.empty()) {
        bf_handler(opt.command, opt);
    } else if (!opt.file.empty()) {
        std::ifstream ifs{opt.file};
        std::ostringstream oss;
        oss << ifs.rdbuf();
        bf_handler(oss.str(), opt);
    } else {
        std::cerr << "Must pass -C arg or pass a file!" << std::endl;
    }
    return 0;
}
