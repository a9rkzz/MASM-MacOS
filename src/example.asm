; Example assembly language program -- adds two numbers
; Author:  R. Detmer
; Date:    1/2008

.586
.MODEL FLAT

INCLUDE io.h            				; header file for input/output

.STACK 4096

.DATA
number1 DWORD   ?
number2 DWORD   ?
prompt1 BYTE    "Enter first number", 0
prompt2 BYTE    "Enter second number", 0
string  BYTE    40 DUP (?)
resultLbl BYTE  "The sum is", 0
sum     BYTE    11 DUP (?), 0

.CODE
_MainProc PROC
        input   prompt1, string, 40     ; read ASCII characters
        atod    string          		; convert to integer
        mov     number1, eax    		; store in memory

        input   prompt2, string, 40     ; repeat for second number
        atod    string
        mov     number2, eax

        mov     eax, number1    		; first number to EAX
        add     eax, number2    		; add second number
        dtoa    sum, eax        		; convert to ASCII characters
        output  resultLbl, sum      	; output label and sum

		mov eax, 0
        ret
_MainProc ENDP
END                             		; end of source code
