#include "bf.h"
#include "cmdparser.hpp"
#include <string>
#include <fstream>
#include <sstream>

void configure_parser(cli::Parser& parser) {
	parser.set_optional<std::string>("C", "COMMAND", "", "Input codes, or pass a file to get input.");
	parser.set_optional<bool>("IN", "INPUT_NUMBER", false, "Use int to input, otherwise input seemed as chars.");
	parser.set_optional<bool>("ON", "OUTPUT_NUMBER", false, "Use int to show output, otherwise show chars.");
	parser.set_optional<bool>("E", "ENTER", false, "Start a new line when output.");
	parser.set_optional<int>("V", "VISUAL", 0, "Visual mode.");
	parser.set_optional<int>("MS", "MAX_STEP", -1, "Max exec steps, -1 is completely run.");
    parser.set_default<std::string>(false, "File to get input, or use -C.", "");
}

int main(int argc, char *argv[]) {
    cli::Parser parser(argc, argv);
    configure_parser(parser);
    parser.run_and_exit_if_error();

    std::string command = parser.get<std::string>("C");
    std::string file = parser.get_default<std::string>();
    bool on = parser.get<bool>("ON");
    bool in = parser.get<bool>("IN");
    bool e = parser.get<bool>("E");
    int v = parser.get<int>("V");
    int ms = parser.get<int>("MS");
    if (!command.empty()) {
        bf_handler(command, on, in, v, e, ms);
    } else if (!file.empty()) {
        std::ifstream ifs{file};
        std::ostringstream oss;
        oss << ifs.rdbuf();
        bf_handler(oss.str(), on, in, v, e, ms);
    } else {
        std::cerr << "Must pass -C arg or pass a file!" << std::endl;
    }
    return 0;
}
