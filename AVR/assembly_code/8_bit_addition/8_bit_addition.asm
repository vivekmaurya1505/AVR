;
; 8_bit_addition.asm
;
; Created: 30-08-2019 14:00:09
; Author :19084013020111,19084013020112 
; version 1.0


.cseg            //Start code segment
.org 0x00        //program origin from 00 location
ldi r16 ,$AA     //AA data load in to r16 register
ldi r17 ,$55     //55 data load in to r17 register
add r16,r17      //data add from r16 and r17 and store in to r16
end:jmp end      //infinite loop
