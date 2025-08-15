# SET mem[0] = mem[1] or mem[0]
# DEL mem[1]
# USE 0 1 2

# mem[2] <= mem[1]
>[->+<]<

# mem[0] = !mem[0]
!include(example/not.bf)

# mem[1] <= mem[2]
>>[-<+>]<

# mem[1] = !mem[1]
!include(example/not.bf)<

!include(example/and.bf)

!include(example/not.bf)
