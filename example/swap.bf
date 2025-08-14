/* swap mem[0] & mem[1] */

// clear mem[2]
>>[-]

// set mem[0], mem[1]
<<,>,

// mem[2] = mem[1]; mem[1] = 0
[>+<-]

// mem[1] = mem[0]; mem{0] = 0
<[>+<-]

// mem[0] = mem[2]; mem[2] = 0
>>[<<+>>-]

// print mem[0] mem[1]
<<.>.
