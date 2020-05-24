;
; program name: Sorting in Ascending.asm
;
; Created: 28-08-2019 14:00:09
; Author :19084013020111,19084013020112 
; version 1.0


.cseg                                ;this is to indicate that following code is in code segment            
.org 0x00                            ;stating address of code

ldi r18, $00   
ldi r20, $00                      ;temp reg intializes to 00 which is used in swapping


ldi r21, $00                         ;this is to indicate 
ldi r22, $0b                          



loop:
ldi r19, $04

ldi xl, $00                          ;this initializes the pointer xl,where xl is register r26
ldi xh, $01                          ;this initializes the pointer xh,where xh is register r27

loopin:                              ;internal loops start here


ld r16,x+                            ;This instruction loads the value of memory location pointed by x in r16 and incrementing the pointer
ld r17,x                             ;This instruction loads the value of memory location pointed by x in r17 

cp r17,r16                           ;comparing two numbers in registers 

brlt  skipswap                       ;when 1st no is greater than 2nd then jump to skipswap

  mov r18,r16                        ;swapping using temp register r18
  mov r16,r17
  mov r17,r18                                                     

skipswap:

st -x,r16                           ;stores value of register in memory location pointed by x and decreaments the value of x
inc xl                              ; increamenting value of x so that it will pointed to the next memory location
st x,r17                            ; value in register is stored back in memory location pointed by x

 
dec r19                             ;decrementing inner loop counter
cp r19,r20                          ;comparing registers for deciding if we have to jump in loop or not
brne loopin                         ;when zero flag is set then jump to loopin otherwise continue

dec r21                             ;decrementing outer loop counter
cp r21,r22                          ;comparing registers for deciding if we have to jump in loop or not
brne loop                           ;when zero flag is set then jump to loopin otherwise continue

end:jmp end                         ; this instruction calls itself infinite times.



