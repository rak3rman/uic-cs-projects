REM
REM UIC 2.0 program to fill an array with 150 numbers.  If
REM all is well, you'll see a 10x15 grid of numbers on the
REM screen.
REM
REM Author: Prof. Hummel, U. of Illinois Chicago, Fall 2020
REM
REM NOTE: assumes a config file where memory size >= 1000.
REM

REM
REM let's test and make sure clear works, and that we can
REM access M0..M999:
REM

load_i  123     REM store some junk values so we test clear
store_i M0
store_i M250
store_i M500
store_i M750
store_i M999

jump   +2
out_s  "**ERROR**\n"
clear

load_i   M0
add_i    M250
add_i    M500
add_i    M750
add_i    M999
add_i    1      REM ACC should be 1
cmp_i    1
jeq     +2      REM jump if eq (i.e. no error)
out_s    "**Error: clear did not zero all of memory.\n"

REM
REM let's build a 150-element array in memory using
REM indirect addressing, where the elements will be
REM 2, 4, 6, ...
REM

load_i	   1     REM i = 1
store_i	   M999
load_i     0     REM A = 0
store_i    M998

jump       +2
out_s      "**ERROR 2**\n"

load_i     M998  REM compute &A[i]
add_i      M999
sub_i      1
store_i    M997

loada_i    M997  REM A[i] += 2i
loadind_i
add_i      M999
mult_i     2
storeind_i

load_i     M999  REM i++
add_i      1
store_i    M999

load_i     M999  REM while (i <= 150)
cmp_i      150
load_i     12345   REM change ACC to make sure jump lands on load
jle       -15

REM
REM now let's output on the screen in a 10x15 matrix:
REM

load_i	   1     REM i = 1
store_i	   M999

load_i     M998  REM compute &A[i]
add_i      M999
sub_i      1
store_i    M997

loada_i    M997  REM cout << A[i] << " ";
loadind_i
out_i
out_s      " "

load_i     M999
mod_i      10    REM if (i%10==0) cout << endl;
cmp_i      0
jne       +2
out_s      "\n"

load_i     M999  REM i++
add_i      1
store_i    M999

load_i     M999  REM while (i <= 150)
cmp_i      150
jle       -18

out_s     "done\n"
end