; file ps.as
.extern L1
.entry L123$

;should activate wrong symbol error
.entry L12
 add r9,STR
;should activate not real symbol



LOOP: 		jmp     WWWW
;should activate symbol not found error
 prn #-5.43
;should activate not a number error
 sub r1     	    r4
;should activate no comma error
 sun r1     	    r4
;should activate no command error
 inc K, K
;should activate too many params error
VRT: inc
;should activate not enough params error
mov S1.2, r3
 bne L3
END: hlt
;this is fine!
STR: .string "abcdef"
;this is fine!
STR: .string abcdef
;should activate no apostrophs error
LENGTH: .data 6,-9,15
K: .data
;should activate not enough params error
S1: .struct 8, "ab", "ab"
;should activate too many params error
S2: .struct 8, "ab"
;this is fine!
S2: .struct 8, "ab"
;should activate double symbol decleration error
L1: .struct 8, "ab"
;should activate double symbol decleration error
S3: .struct
;should activate not enough params error

S344:struct S17
;should activate no command error

S344333:.struct S17
;should activate not enough params error

S312: .data
;should activate not enough params error

S323: .string
;should activate not enough params error

.extern
;should activate not enough params error

.entry
;should activate not enough params error

