/* mem[2] = mem[1] * mem[0] */
/* mem[0], mem[1] remain */

// set mem[0], mem[1]
,>,

// clear mem[2], mem[3], mem[4]
>[-]>[-]>[-]

// loop mem[0] times, 
// mem[3] = mem[0]; mem[0] = 0
<<<<[->>>+<<<
    // mem[2] += mem[4] = mem[1]; mem[1] = 0
    >[->+>>+<<<]

    // mem[1] = mem[4]; mem[4] = 0
    >>>[-<<<+>>>]
<<<<]

// mem[0] = mem[3]; mem[3] = 0
>>>[-<<<+>>>]

// print mem[2], mem[0], mem[1]
<.<<.>.
