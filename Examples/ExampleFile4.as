; file ps.as
.entry LOOP
.entry LENGTH
.extern L3
.extern W
MAIN: mov S1.1, W
 add r2,STR
LOOP: jmp W
macro m2
inc K
endmacro
 prn #-5
 sub r1, r4
m2
mov S1.2, r3
 bne L3
END: hlt
STR: .string "abcdef"
LENGTH: .data 6,-9,15
K: .data 22
S1: .struct 8, "ab"
