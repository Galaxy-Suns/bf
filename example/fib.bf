# INPUT N (1 - N)
# OUTPUT fib[N]

# mem[2] = N
>>,-

# mem[1] = 1
<+.

# loop i = 2
>[->+ # mem[i]--, mem[i+1]++
   
   # mem[i+2] <= mem[i+1]
   [->+<]

   # mem[i+1] <= mem[i]
   <[->+<]

   # mem[i] <= mem[i-2]
   <<[->>+<<]

   # mem[i-2] <= mem[i-1] => mem[i]
   >[-<+>>+<]

   # mem[i-1] <= mem[i-2]
   <[->+<]

   # print mem[i]
   >>.

# i++  
>]

#
# clear
# 
<[-]<[-]>>>

[-
    #mem[i-1] <= mem[i]
    [-<+>]

# i--
<]

<<<
