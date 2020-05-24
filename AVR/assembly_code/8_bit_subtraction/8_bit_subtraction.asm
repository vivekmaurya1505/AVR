;
; 8_bit_subtraction.asm
;
; Created: 27-08-2019 15:05:09
; Author :19084013020111,19084013020112 
; version 1.0


; Replace with your application code
.cseg
.org 0x00
ldi r16 ,$AA  
ldi r17 ,$55
sub r16,r17
end:jmp end
