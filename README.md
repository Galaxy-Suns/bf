# bf

An enhanced [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) interpreter with extended UTF-8 encoding support and additional pre-processing directives.

## Usage

```
USAGE:
  bf [parameters] <BF_FILE | -C BF_CODE>

AVAILABLE PARAMETERS
  -h, --help                    show help
  -v, --version                 show version
  -C BF_CODE, --COMMAND BF_CODE eval bf code
  -IN, --INPUT_NUMBER           use int to input, otherwise input seemed as chars
  -ON, --OUTPUT_BUMBER          Use int to show output, otherwise show chars
  -E, --ENTER                   start a new line when output
  -V N, --VISUAL N              Visual mode, N means show N cells.
  -VD N, --VISUAL_DEBUG N       Visual debug mode, use with !visual() command, N means show N cells
  -MS STEP, --MAX_STEP STEP     Max exec steps
```

## Example

```sh
$ ./build/bf example/utf8.bf 
你好 世界🤖
```

## Features

* All text following the first `#` in a line is considered a comment.
* Non-comment content starting with `!` is treated as a preprocessor directive, formatted as `! CMDNAME ( ... )`.

  * `!include(/path/to/your/function.bf)` replaces this with the code from the target file, enabling functionality similar to functions.

    * Relative to the interpreter's working directory.
  * `!visual()` works with the command-line option `-VD` to visualize the current memory and pointer state at the code location.
