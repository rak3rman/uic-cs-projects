REM
REM UIC 2.0 program to output the numbers 1..20 using a loop.
REM
REM Author: Prof. Hummel, U. of Illinois Chicago, Fall 2020
REM

load_i	 1     REM i = 1
store_i	 M0

load_i   M0    REM i <= 20
cmp_i    20
jgt      +8    REM jump i>20

load_i   M0    REM cout i
out_i
out_s    "\n"
load_i   M0    REM i++
add_i    1
store_i  M0
jump     -9    REM loop

end

