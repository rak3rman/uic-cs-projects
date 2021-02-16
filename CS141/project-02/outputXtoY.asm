REM
REM UIC 2.0 program to output the numbers X to Y using a loop.
REM
REM Author: Prof. Hummel, U. of Illinois Chicago, Fall 2020
REM
REM Note that config file must identify at least 235 memory locations.
REM

load_i   1       REM use memory instead of literals
store_i  M0

out_s    "Enter X: "
in_i
store_i  M234    REM i = x

out_s    "Enter Y: "
in_i
store_i  M233    REM y

jump     +2
out_s    "**ERROR**\n"

load_i   M234    REM i <= Y
cmp_i    M233
jgt      +9      REM jump i>Y

load_i   M234    REM cout i
out_i
out_s    " "
load_i   M234    REM i++
add_i    M0
store_i  M234
add_i    399     REM just change accumulator to make sure jump reloads
jump     -10     REM loop

out_s    "#\n"
out_s    "done\n"

end