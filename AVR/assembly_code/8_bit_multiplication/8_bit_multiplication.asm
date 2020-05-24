;
; 8_bit_multiplication.asm
;
; Created: 27-08-2019 18:08:00
; Author :19084013020111,19084013020112 
; version 1.0
;


; Replace with your application code
.cseg           //Start code segment
.org 0x00       //program origin from 00 location
ldi r16, $88    //08 data load in to r16 register
ldi r17, $88    //08 data load in to r17 register
mul r16, r17    //data r16 multiply wirh  r16 and r17 and store in to r0 and r1

end: jmp end