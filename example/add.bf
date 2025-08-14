/* mem(2) = mem(1) + mem(0) */
/* mem(1) remain */
/* mem(0) remain */

// set mem(0) mem(1)
,>,

// clear mem(2) mem(3)
>[-]>[-]

// mem(2) = mem(3) = mem(0); mem(0) = 0
<<<[->>+>+<<<]

// mem(0) = mem(3); mem(3) = 0
>>>[<<<+>>>-]

// mem(2) += mem(3) = mem(1); mem(1) = 0
<<[->+>+<<]

// mem(1) = mem(3); mem(3) = 0
>>[-<<+>>]

// print mem(2) mem(0) mem(1)
<.<<.>.
