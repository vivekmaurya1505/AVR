;
; 16_bit_subtraction.asm
;
; Created: 29-08-2019 12:00:09
; Author :19084013020111,19084013020112 
; version 1.0
;


; Replace with your application code
.cseg 
.org 0x00
ldi r17,$10      //09 data load in to r17 register
ldi r16,$10      //09 data load in to r16 register
ldi r19,$09      //09 data load in to r19 register     
ldi r18,$09      //09 data load in to r18 register      
sub r16,r18      //r16 add with r18 and store in r16   
sbc r17,r19       //r17 add with r19 and store in r17         
end:jmp end           //infinite loop
