; 
; The uC/OS II port for Keil C51 V6
;
; Ported date:     Dec 5, 2001
; By:              John X. Liu, China, (johnxliu@163.com)
; Target platform: Keil C51 V6.20, V6.21

	NAME	OS_CPU_A_ASM

; ?C_XBP is the simulated external stack pointer in large mode, but its origianal
; declare makes it can not be used in c files, so redeclare it in this module 
; insteading of the old one
	PUBLIC	?C_XBP, C_XBP					;

	EXTRN   CODE(_?C_OSCtxSw)

	PUBLIC	_?LoadCtx, Stack, _?OSCtxSw, _?KCOSCtxSw

LoadXBP	MACRO
		MOV	DPH, C_XBP
		MOV	DPL, C_XBP+1
	ENDM

SaveXBP MACRO
		PUSH	IE
		CLR	EA
		MOV	C_XBP,   DPH
		MOV	C_XBP+1, DPL
		POP	IE
	ENDM

LoadReg	MACRO   REG
		MOVX	A,   @DPTR
		MOV	REG, A
	ENDM

SaveReg	MACRO   REG
		MOV	A,	REG
		MOVX	@DPTR,  A
	ENDM

; The PUSHA now emulates the pushing sequence what Keil C does.
PUSHA	MACRO
		IRP	REG,	<ACC, B, DPH, DPL, PSW, 0, 1, 2, 3, 4, 5, 6, 7>
		PUSH	REG
		ENDM
	ENDM

POPA	MACRO
		IRP	REG,	<7, 6, 5, 4, 3, 2, 1, 0, PSW, DPL, DPH, B, ACC>
		POP	REG
		ENDM
	ENDM

; Declare the external stack pointer by ourself, so that we can use it freely.
; you know, in the name of '?C_XBP' it can not be used in c modules but in the 
; name of 'C_XBP' it can do.
DT?C_XBP	SEGMENT	DATA
		RSEG	DT?C_XBP
?C_XBP:					; These two labels point to the same address
C_XBP:					;
	DS	2

; Declare a label 'Stack' in the hardware stack segment so that we know where it begins.
?STACK	SEGMENT IDATA
	RSEG	?STACK
Stack:

; Load context from the external stack pointed by C_XBP
PR?LoadCtx      SEGMENT CODE
	RSEG	PR?LoadCtx
_?LoadCtx:
	LoadXBP					; Load the C_XBP to DPTR

	LoadREG	SP				; Load the hardware stack pointer
	INC	DPTR				;

        MOV     R0, SP				; Now we pop the hardware stack
LC_1:						; from the external one.
	LoadREG	@R0				; Did not use the PUSH ACC instruction for if we want to
	INC     DPTR				; do so, we have to DEC DPTR, which costs much.
	DEC     R0				;
	CJNE    R0, #Stack-1, LC_1		;

	SaveXBP					; after the hardware stack has been popped,
						; the external stack pointer should be adjusted

RestoreCtx:
WANTFASTER	EQU	1
$IF	WANTFASTER
	POP	PSW				; A little bit dangerous but it works. C is PSW.7 and EA is IE.7
	MOV	EA, C				; They are at the same bit location of a byte.
$ELSE
	POP	ACC				; Safe way to do the same thing.
	RLC	A				;
	MOV	EA, C				;
$ENDIF
						; Now that the context has been loaded into hardware
 	POPA					; stack, what we need do is just popping them upto registers.
						;

	RET					; Now everything is ready, a RET will bring the task to run.

; Task level context switch entry point, which is intended to be called by task gracefully. 
_?OSCtxSw:
	PUSHA					; Save current context first into hardware stack
	PUSH	IE

_?KCOSCtxSw:					; Now begin pushing hardware stack to external one
	LoadXBP					; Load the external stack pointer first to prepare storing 
						; data into it.

	MOV	A, SP				; Calculate how much memory in external stack needed
	CLR	C				; so that we can adjust the external stack pointer
	SUBB	A, #Stack-1			; Calculated the length of hardware stack

	MOV	R0, A				; Save the length of hardware stack to R0, which is used as a counter on saving hardware stack.

	INC	A				; Add the space for storing SP

	CLR	C
	XCH	A, DPL				; Now ACC contains the right amount of external stack memory should be used.
	SUBB	A, DPL				; Adjust the external pointer.stored in DPTR to make to point to the new stack top from where we will store hardware stack.
	JNC	SC_1
	DEC	DPH
SC_1:
	MOV	DPL,A				; Now DPTR contains the external stack pointer after pushing context into external stack.

	SaveXBP					; Save to external stack pointer.
						; Keeps the DPTR containing the external stack pointer still.
	SaveREG	SP				; Save hardware stack pointer in the top of external stack

SC_2:
	INC	DPTR				;
	POP	ACC				; Pop the data from hareware stack
	MOVX	@DPTR, A			; and save into external one.
	DJNZ    R0, SC_2			; Remember, R0 contains the hardware stack's length.

	LJMP	_?C_OSCtxSw			; 

	END
