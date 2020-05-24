;
; 10_byte_addition.asm
;
; Created:31-08-2019 16:00:09
; Author :19084013020111,19084013020112 
; version 1.0


; Replace with your application code
.cseg                   //Start code segment
.org 0x00               //program origin from 00 location
ldi xl,$00              //lower address load into lower x register
ldi xh,$01              // higher address load into higher x register
ldi r16,$00            // 00 data load in to r16 register (result)
ldi r17,$00            // 00 data load in to r17 register (for carry)
ldi r19,$0A				//0A data load in to r19 register (counter)


loop:
ld r18,x+              // loading current address value in r18
add r16,r18            // add r16 with r18 and result store in r16
brcc skip              // branch if carry clear
inc r17                 //for carry 

skip:  

dec r19                //counter
brne loop              // branch if counter not zero

end: jmp end          // infite loop
