# INPUT 
# if (CONFITION) { STATEMENT1 } 
# else { STAMENT2 } 

# mem[0] = CONDITION
,

# set mem[1] = 1 
# if enter if body set it to 0
>+<


# if mem[0] not 0 enter loop
# make sure only loop once
[[-]>> 
    # STATEMENT1
    !include(example/hello.bf)
# mem[1] = 0
<-<]

# if mem[1] is not 0 enter loop
>[->
    //STATEMENT2
    !include(example/name.bf)
<]

# clear
<
