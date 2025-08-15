# SET mem[0] = mem[1] * mem[0] 
# DEL mem[1]
# USE 0 1 2 3

# loop mem[1] times, mem[1]--
>[-
    # mem[2] += mem[3] <= mem[0]
    <[->>+>+<<<]

    # mem[0] <= mem[3]
    >>>[-<<<+>>>]
<<]

# clear mem[0]
<[-]

# mem[0] <= mem[2]
>>[-<<+>>]

# clear
<<
