;
; 8_bit_division.asm
;
; Created: 27-08-2019 11:00:00
; Author :19084013020111,19084013020112 
; version 1.0


; Replace with your application code
.cseg                //Start code segment
.org 0x00            //program origin from 00 location
ldi r16 ,$09         //09 data load in to r16 register  
ldi r17 ,$02         //02 data load in to r17 register
ldi r18,$FF          //FF data load in to r18 register (using as a counter)
goback:              
inc r18              //r18 register used for counter(r18 is an ans)
sub r16,r17          //subtract data from r16 to r17 and save to r16 
brsh gobacK           //branch if r16 is greater and equal
ADD R16,R17           // r16 register is remender

end:jmp end           // infinite loop