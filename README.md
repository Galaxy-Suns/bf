# bf

A [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) Interpreter.

"An enhanced [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) interpreter with extended UTF-8 encoding support and additional pre-processing directives."

## Usage

```
Available parameters:

  -h	--help
   
   This parameter is optional. The default value is ''.

  -C	--COMMAND
   Input codes, or pass a file to get input.
   This parameter is optional. The default value is ''.

  -IN	--INPUT_NUMBER
   Use int to input, otherwise input seemed as chars.
   This parameter is optional. The default value is '0'.

  -ON	--OUTPUT_NUMBER
   Use int to show output, otherwise show chars.
   This parameter is optional. The default value is '0'.

  -E	--ENTER
   Start a new line when output.
   This parameter is optional. The default value is '0'.

  -V	--VISUAL
   Visual mode, 0 is not enable, N means show N cells.
   This parameter is optional. The default value is '0'.

  -VD	--VISUAL_DEBUG
   Visual debug mode, use with !visual() command, 0 is not enable, N means show N cells.
   This parameter is optional. The default value is '0'.

  -MS	--MAX_STEP
   Max exec steps, -1 is completely run.
   This parameter is optional. The default value is '-1'.

  	
   File to get input, or use -C.
   This parameter is optional. The default value is ''.
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
