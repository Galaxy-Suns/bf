# SET mem[0] = !mem[0]
# USE 0 1

# mem[1] = 1
>+<

# enter loop if mem[0]
# mem[0] = 0
[[-]
    # mem[1] = 0
    >-<
]

# enter loop if mem[1]
# mem[1] = 0
>[-
    # mem[0] = 1
    <+>
]

# clear
<
