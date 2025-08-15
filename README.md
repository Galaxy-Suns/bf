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

  -MS	--MAX_STEP
   Max exec steps, -1 is completely run.
   This parameter is optional. The default value is '-1'.

  	
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

## 扩展

### 建议

推荐 brainfuck 程序具备以下特征 以良好体验扩展

- 在程序结束时总是清除用到的所有非必要单元（除了功能就是改变某些单元的内容）
- 假设程序开始时指针位于单元0
- 不要向假想的单元0左侧访问或赋值
- 在文件开头以`# ...`进行文档描述 
  - 如 `cell[1] = cell[1] + cell[0]`
  - 程序结束时 除了 `cell[2]` `cell[0]` `cell[1]` 任何后续单元值为0
  - 程序结束时 指针指回开始的位置

### 内容

- 一行中第一个`#`之后的所有文字被视为注释 
- 以`!`开头的非注释内容被视为预处理指令 格式为 `! CMDNAME ( ... ) `
  - `!include(/path/to/your/function.bf)` 用目标中的代码替换此处 可以实现类似函数的功能
    - 相对于 解释器的工作目录
