REM
REM CS141 - Lab 02 - 9/1/2020
REM
REM Author: Radison Akerman
REM Affiliation: University of Illinois at Chicago
REM

out_s 	"Enter your age: "
in_i
store_i	M0

load_i	M0
add_i	-220
mult_i  -1
out_s 	"Maximum safe heart rate: "
out_i
out_s	"\n"
store_i	M1

load_i	M1
div_i	2
out_s 	"Minimum target heart rate: "
out_i
out_s	"\n"

load_i	M1
mult_i	64
div_i   100
out_s 	"Moderate intensity targets: "
out_i
out_s 	"-"
load_i	M1
mult_i	76
div_i   100
out_i
out_s	"\n"

load_i	M1
mult_i	77
div_i   100
out_s 	"High intensity targets: "
out_i
out_s 	"-"
load_i	M1
mult_i	93
div_i   100
out_i
out_s	"\n"

out_s 	"Done"
out_s	"\n"

end


