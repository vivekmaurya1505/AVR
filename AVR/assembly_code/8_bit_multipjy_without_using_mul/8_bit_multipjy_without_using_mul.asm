;
; 8_bit_multipjy_without_using_mul.asm
;
; Created: 01-09-2019 10:00:09
; Author :19084013020111,19084013020112 
; version 1.0


; Replace with your application code
.cseg              //Start code segment
.org 0x00          //program origin from 00 location

ldi r16, $09      //09 data load in to r16 register
ldi r17,$10       //10data load in to r16 register
ldi r18,$00       //00 data load in to r16 register(for carry )
ldi r19,$00       //00 data load in to r16 register(as accumulator)

goback:

add r19,r16      // add from r19 and r16 and store in to r19(add continue in loop)
brsh skip        //branch if carry clear
inc r18          //if carry counter
 
skip:           

dec r17        

brne goback     //jump in to goback when r17 is zero

end: jmp end    // infinite loop

