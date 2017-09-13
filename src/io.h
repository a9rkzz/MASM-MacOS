; IO.H -- header file for I/O macros (listing suppressed)
.NOLIST      ; turn off listing

; 32-bit version with windows I/O
; must be used with project framework defining showOutput and getInput
; R. Detmer   October 2007
.586
EXTRN _getInput:NEAR32, _showOutput:NEAR32, atodproc:NEAR32, dtoaproc:NEAR32, wtoaproc:NEAR32, atowproc:NEAR32

dtoa        MACRO  dest,source
            push   ebx
            lea    ebx, dest
            push   ebx
            mov    ebx, [esp+4]		; in case source was EBX
            mov    ebx, source
            push   ebx
            call   dtoaproc
            add    esp, 8
            pop    ebx
            ENDM

atod        MACRO  source
            lea    eax,source
            push   eax
            call   atodproc
            add    esp, 4
            ENDM

wtoa        MACRO  dest,source
            push   ebx
            lea    ebx,dest
            push   ebx
            mov    ebx, [esp+4]
            mov    bx, source
            push   ebx
            call   wtoaproc
            add    esp, 8
            pop    ebx
            ENDM

atow        MACRO  source
            lea    eax,source
            push   eax
            call   atowproc
            add    esp, 4
            ENDM

output      MACRO  outLbl, outStr
            pushad						; save general registers
			sub esp, 4					; Align the stack
            lea    eax, outStr
            push   eax
            lea    eax, outLbl
            push   eax
            call   _showOutput
			pop    eax					; And pull the items back off the stack
			pop    eax
			add esp, 4
            popad
            ENDM

input       MACRO  inPrompt, inStr, maxLength
	        pushad
            mov    ebx, maxLength
            push   ebx
            lea    ebx, inStr
            push   ebx
			lea    ebx, inPrompt
            push   ebx
            call   _getInput
			pop ebx
			pop ebx
			pop ebx
            popad
            ENDM

.NOLISTMACRO ; suppress macro expansion listings
.LIST        ; begin listing
