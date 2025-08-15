# SET mem[1], mem[0] = mem[0], mem[1]
# USE 0 1 2

# mem[2] = mem[1]; mem[1] = 0
>[>+<-]

# mem[1] = mem[0]; mem{0] = 0
<[>+<-]

# mem[0] = mem[2]; mem[2] = 0
>>[<<+>>-]<<
