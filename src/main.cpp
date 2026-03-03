#include "bf.h"
#include <fstream>
#include "Help.h"
#include <sstream>
#include <iostream>
#include "Options.h"

const std::string name = "bf";
const std::string short_description = "An enhanced Brainfuck interpreter";
const std::string usage = "bf [parameters] <BF_FILE | -C BF_CODE>";
const std::string version = "v1.1";
const std::string description = R"(
  bf: An enhanced Brainfuck interpreter with extended UTF-8 encoding support and additional pre-processing directives

  features:
  - All text following the first '#' in a line is considered a comment.
  - Non-comment content starting with `!` is treated as a preprocessor directive, formatted as `! CMDNAME ( ... )`.
    - `!include(/path/to/your/function.bf)` replaces this with the code from the target file, enabling functionality similar to functions.
      - Relative to the interpreter's working directory.
    - `!visual()` works with the command-line option `-VD` to visualize the current memory and pointer state at the code location.
)";

int main(int argc, char *argv[]) {
    Help help {name + " - " + short_description, usage, version, description};
    const Options opt = get_options(argc, argv, help);

    if (opt.help_enable) {
        help.show();
        return 0;
    }

    if (opt.show_version) {
        std::cout << version << std::endl;
        return 0;
    }

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
