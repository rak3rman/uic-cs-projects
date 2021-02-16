REM
REM UIC 2.0 program to check that all memory locations are set to 0 with clear command
REM
REM Author: Prof. Hummel, U. of Illinois Chicago, Fall 2020
REM
REM NOTE: config file must have memory of at least 30.
REM

REM load all the memory locations
load_i 66

store_i M0
store_i M1
store_i M2
store_i M3
store_i M4
store_i M5
store_i M6
store_i M7
store_i M8
store_i M9
store_i M10
store_i M11
store_i M12
store_i M13
store_i M14
store_i M15
store_i M16
store_i M17
store_i M18
store_i M19
store_i M20
store_i M21
store_i M22
store_i M23
store_i M24
store_i M25
store_i M26
store_i M27
store_i M28
store_i M29

REM Clear and check that they all are set to 0

clear

in_i

add_i M0
add_i M1
add_i M2
add_i M3
add_i M4
add_i M5
add_i M6
add_i M7
add_i M8
add_i M9
add_i M10
add_i M11
add_i M12
add_i M13
add_i M14
add_i M15
add_i M16
add_i M17
add_i M18
add_i M19
add_i M20
add_i M21
add_i M22
add_i M23
add_i M24
add_i M25
add_i M26
add_i M27
add_i M28
add_i M29

out_i
out_s "\n"

end