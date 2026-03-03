#include "Options.h"
#include "cmdparser.hpp"
#include "Help.h"

void configure_parser(cli::Parser& parser) {
	parser.set_optional<std::string>("C", "COMMAND", "", "");
	parser.set_optional<bool>("IN", "INPUT_NUMBER", false, "");
	parser.set_optional<bool>("ON", "OUTPUT_NUMBER", false, "");
	parser.set_optional<bool>("E", "ENTER", false, "");
	parser.set_optional<int>("V", "VISUAL", 0, "");
	parser.set_optional<int>("VD", "VISUAL_DEBUG", 0, "");
	parser.set_optional<int>("MS", "MAX_STEP", -1, "");
    parser.set_optional<bool>("h", "help", false, "");
    parser.set_optional<bool>("v", "version", false, "");
    parser.set_default<std::string>(false, "", "");
}

void configure_help_parameters(Help &help) {
    help.add_parameter("-h", "--help", "show help");
    help.add_parameter("-v", "--version", "show version");
    help.add_parameter("-C BF_CODE", "--COMMAND BF_CODE", "eval bf code");
    help.add_parameter("-IN", "--INPUT_NUMBER", "use int to input, otherwise input seemed as chars");
    help.add_parameter("-ON", "--OUTPUT_BUMBER", "Use int to show output, otherwise show chars");
    help.add_parameter("-E", "--ENTER", "start a new line when output");
    help.add_parameter("-V N", "--VISUAL N", "Visual mode, N means show N cells.");
    help.add_parameter("-VD N", "--VISUAL_DEBUG N", "Visual debug mode, use with !visual() command, N means show N cells");
    help.add_parameter("-MS STEP", "--MAX_STEP STEP", "Max exec steps");
}

Options get_options_from_parser(const cli::Parser& parser) {
    Options opt;
    opt.command = parser.get<std::string>("C");
    opt.file = parser.get_default<std::string>();
    opt.output_number = parser.get<bool>("ON");
    opt.input_number = parser.get<bool>("IN");
    opt.enter = parser.get<bool>("E");
    opt.visual = parser.get<int>("V");
    opt.visual_debug = parser.get<int>("VD");
    opt.max_step = parser.get<int>("MS");
    opt.help_enable = parser.get<bool>("h");
    opt.show_version = parser.get<bool>("v");
    return opt;
}

Options get_options(int argc, char *argv[], Help &help) {
    cli::Parser parser(argc, argv);
    parser.disable_help();
    configure_parser(parser);
    configure_help_parameters(help);
    parser.run_and_exit_if_error();
    Options opt = get_options_from_parser(parser);
    return opt;
}
