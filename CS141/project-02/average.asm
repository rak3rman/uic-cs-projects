REM
REM UIC 1.0 program to input 2 integers and output the average.
REM
REM Author: Prof. Hummel, U. of Illinois Chicago, Fall 2020
REM

out_s 	"Please enter first integer: "
in_i
store_i	M0

out_s 	"Please enter second integer: "
in_i
store_i	M1

load_i	M0
add_i	M1
div_i	2
store_i	M2

out_s	"Avg: "
load_i	M2
out_i
out_s	"\n"

end
