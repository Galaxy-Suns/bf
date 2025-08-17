#include "Options.h"
#include "cmdparser.hpp"

void configure_parser(cli::Parser& parser) {
	parser.set_optional<std::string>("C", "COMMAND", "", "Input codes, or pass a file to get input.");
	parser.set_optional<bool>("IN", "INPUT_NUMBER", false, "Use int to input, otherwise input seemed as chars.");
	parser.set_optional<bool>("ON", "OUTPUT_NUMBER", false, "Use int to show output, otherwise show chars.");
	parser.set_optional<bool>("E", "ENTER", false, "Start a new line when output.");
	parser.set_optional<int>("V", "VISUAL", 0, "Visual mode, 0 is not enable, N means show N cells.");
	parser.set_optional<int>("VD", "VISUAL_DEBUG", 0, "Visual debug mode, use with !v() command, 0 is not enable, N means show N cells.");
	parser.set_optional<int>("MS", "MAX_STEP", -1, "Max exec steps, -1 is completely run.");
    parser.set_default<std::string>(false, "File to get input, or use -C.", "");
}

Options get_options_from_parser(const cli::Parser& parser) {
    Options opt;
    opt.command = parser.get<std::string>("C");
    opt.file = parser.get_default<std::string>();
    opt.output_number = parser.get<bool>("ON");
    opt.input_number = parser.get<bool>("IN");
    opt.enter = parser.get<bool>("E");
    opt.visual = parser.get<int>("V");
    opt.visual_debug = parser.get<int>("V");
    opt.max_step = parser.get<int>("MS");
    return opt;
}

Options get_options(int argc, char *argv[]) {
    cli::Parser parser(argc, argv);
    configure_parser(parser);
    parser.run_and_exit_if_error();
    Options opt = get_options_from_parser(parser);
    return opt;
}
