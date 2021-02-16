
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
REM
REM UIC 2.0 program to input N integers and output the average.
REM
REM Author: Prof. Hummel, U. of Illinois Chicago, Fall 2020
REM
REM Version: 2.0 (fixed earlier infinite loop)
REM

out_s	"# of integers? "
in_i
store_i	M0    REM store N
load_i	0
store_i	M1    REM store i
store_i	M2    REM store sum

load_i	M1    REM i < N?
cmp_i 	M0
jge	   +9

out_s	  "integer? "
in_i	         REM cin >> x
add_i	   M2    REM sum = sum + x
store_i	 M2
load_i	 M1    REM i++
add_i    1
store_i  M1
jump	  -10

out_s	"Avg: "
load_i	M2
div_i	M0
out_i
out_s	"\n"

end
