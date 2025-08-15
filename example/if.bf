# INPUT mem[0]
# if (CONFITION) { STATEMENT1 } 
# else { STAMENT2 } 

# mem[0] = CONDITION
,

# set mem[2] = 1 
# if enter if body set it to 0
>>+<<


# if mem[0] not 0 enter loop
# mov mem[0] to mem[1]
# make sure only loop once
[[->+<]>>> 
    # STATEMENT1
    !include(example/hello.bf)
# mov mem[1] to mem[0], mem[2] = 0
<[-]<<]>[+<->]<

# if mem[2] is not 0 enter loop
>>[->
    //STATEMENT2
    !include(example/name.bf)
<]

# clear
<<
