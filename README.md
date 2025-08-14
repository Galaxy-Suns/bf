# bf

A [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) Interpreter.

## Dependencies

- [termcolor](https://github.com/ikalnytskyi/termcolor)

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
   Visual mode.
   This parameter is optional. The default value is '0'.

  	
   File to get input, or use -C.
   This parameter is optional. The default value is ''.
```

## Example


```sh
$ ./build/bf example/mul.bf -ON -IN -E
>>> 9
>>> 8
72
9
8
```
