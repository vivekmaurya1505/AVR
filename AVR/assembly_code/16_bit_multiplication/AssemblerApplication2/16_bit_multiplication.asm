;
; 16_bit_multiplication
;
; Created: 30-08-2019 11:00:09
; Author :19084013020111,19084013020112 
; version 1.0




.cseg
.org 0x00
ldi r16,$FA         ;add 12 in r16 register
ldi r17,$DC         ;add 12 in r17 register
ldi r18,$2A          ;add 12 in r18 register
ldi r19,$DC           ;add 12 in r19 register
ldi r20,$0
mul r19,r17            ;r1:r0r19*r17
mov r3,r1              ;r3=r1
mov r2,r0              ;r2=r0

mul r19,r16             ;r1:r0r19*r16
mov r5,r1              ;r5=r1

mov r4,r0                ;r4=r0

 
mul r18,r17
mov r7,r1
mov r6,r0
 
mul r18,r16
mov r9,r1
mov r8,r0

add r6,r3
adc r6,r4
adc r8,r5
adc r8,r7
adc r9,r20               
	         
end :jmp end               ;infinite loop
