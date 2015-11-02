; *************************************************************************
; ** Filename : "STAND2.INC"                         **
; ** Purpose  : Include file of standard ASM procedures (version 2)  **
; *************************************************************************

; Contents:
; ---------

; (P) = PROC  (M) = MACRO

; VIDEO MODE CONTROL
;   Set13h      (P) Sets standard 320x200 256 colour mode
;   SetText     (P) Returns to standard text mode
;   SetPal      (P) Set a palette

; MEMORY ALLOCATION
;   MemInit     (M) Set up variables before memory allocation
;               NB - MUST be the first thing after .startup
;                  - calls ResizeMem automatically
;   ResizeMem   (P) Frees up all unused memory for allocation
;   GetMem      (P) Allocates a memory block
;   FreeMem     (P) Deallocates a memory block

; FILE ACCESS
;   LoadData    (P) Load graphics info from an uncompressed file
;             NB - Autodetects a sprite or background file,
;               the size of the file and deals with files
;               over 64k in size automatically. The buffer
;               must be large enough though.
;   LoadPal     (P) Load palette information

; GENERAL
;   WaitKey     (P) Wait for a keypress
;   Finish      (M) Exits cleanly to DOS

            
; All code Copyright Steve Streeting 1995
;************************************************************************

.data
ProgStartSeg    dw  0
ProgEndSeg  dw  0
OldInt6Seg  dw  0
OldInt6Off  dw  0
OutMemFlag  dw  0


;*** Load graphics info
GFXHeader   LABEL BYTE
WidthL      db  ?   ;separate high/low bytes as loaded in in
WidthH      db  ?   ; little endian format, low byte first
HeightL     db  ?
HeightH     db  ?
SpriteWidthL    db  ?
SpriteWidthH    db  ?
SpriteHeightL   db  ?
SpriteHeightH   db  ?
NoSpritesL  db  ?
NoSpritesH  db  ?
FileType    db  ?
Empty       db  5 dup(?)

.code

FileSize    dd  ?

;************************ PROCEDURES ***************************

;------------------ Free up memory grabbed by EXE-------------
; *** MUST SET UP SEGS FIRST *****        
ResizeMem       PROC NEAR


    mov     bx,[ProgEndSeg]
        sub     bx,[ProgStartSeg]
        mov     es,[ProgStartSeg]
        mov     ah,4ah          ;resize mem block (EXE's grabbed all
        int     21h         ;the memory! The git!! 8-))
    ret
ResizeMem   ENDP


; ----------------- ALLOCATE MEMORY BLOCK ----------------------
; *** PRE-LOAD BX WITH SIZE OF BLOCK IN PARAS (BYTES / 16) ***
; *** RETURNS AX = SEG OF ALLOCATED BLOCK ***
; *** IMPORTANT - CHECK CARRY FLAG ON RETURN

GetMem      PROC NEAR
    

    mov ah, 48h         ;DOS mem allocate
    int 21h
    ret
GetMem  ENDP


; ------------------- FREE A MEMORY BLOCK --------------------
; *** PRE-LOAD ES WITH SEG OF BLOCK TO FREE ***
FreeMem     PROC NEAR

    mov ah, 49h
    int 21h
    ret
FreeMem     ENDP


; --------------- LOAD IN GFX ------------------------------ 
; *** PRE-LOAD :
;       DX -  offset of filename
;       AX -  segment of buffer for graphics
;       DI -  offset of buffer for graphics
    
LoadData    PROC NEAR
    push    ax
    mov ax, 3d00h               ;Open file, read only
                    ;DX already loaded with name off
    int 21h
    mov bx, ax          ;store the handle in BX
    
    mov dx, offset GFXHeader
    mov cx, 16          ;read header
    mov ah, 3Fh             
    int 21h

    cmp FileType, '2'
    je  SpriteFile
    cmp FileType, '4'
    je  SpriteFile
        
    xor eax, eax
    xor ecx, ecx
    mov ah, [WidthH]
    mov al, [WidthL]
    mov ch, [HeightH]
    mov cl, [HeightL]
    mul ecx         ;size of the file
    jmp loadit
SpriteFile:
    xor eax, eax
    xor ecx, ecx
    mov ah, [SpriteWidthH]
    mov al, [SpriteWidthL]
    mov ch, [SpriteHeightH]
    mov cl, [SpriteHeightL]
    mul ecx         ;size of the Sprite
    xor ecx, ecx        
    mov cl, [NoSpritesL]
    mov ch, [NoSpritesH]
    mul ecx         ; * number of sprites   
                    ; = size of file
loadit: 
    mov CS:[FileSize], eax
    
    pop ax
    push    ds
    mov ds, ax          ;load the destination segment
    mov dx, di          ;& offset 
    
    
    
  readloop:     
    cmp CS:[FileSize], 38400
    jb  lastone
    sub CS:[FileSize], 38400
    mov     cx, 38400               ;standard load size
    jmp load
   lastone:
    mov ecx, CS:[FileSize]      ;the remainder of the file
    mov CS:[FileSize], 0
   load:        
    mov ah, 3Fh             ;read file
    int 21h
    
    mov ax, ds
    add ax, (38400 / 16)    ;shift up the seg (in paras)
    mov ds, ax
    mov dx, di          ;keep using the offset

    cmp CS:[FileSize], 0
    jne readloop        ;continue if there's some left

    mov ah, 3Eh             ;close file (BX already set)
    int 21h

    pop ds          ;get DS back
    ret

LoadData    ENDP        


; ----------------- LOAD A PALETTE -------------------------------------
LoadPal         PROC NEAR
    
;*** PRE-LOAD:
;       DX = Offset of Palette file name
;       CX = Offset of Palette buffer

; (Palettes are assumed to be in the data segment)

    push ds
    mov ax, @data
    mov ds, ax
    
    mov ax, 3d00h               ;Open file, read only
                    ;DX already loaded with name off
    int 21h
    mov bx, ax          ;store the handle in BX
    
    mov dx, cx          ;put palette buffer offset in DX
    
    mov cx, 768                 ;size of palette file
        
    mov ah, 3Fh             ;read file
    int 21h
    
    mov ah, 3Eh             ;close file (BX already set)
    int 21h
    
    pop ds
    ret
LoadPal         ENDP

; ---------------- SET A PALETTE ----------------------------------------
;*** PRE-LOAD:
;       SI = offset of palette to be used

SetPal          PROC NEAR
                        ;set the palette up
    cld

    mov     dx, 3c8h                        ;colour NO selector
    xor     al, al                          ;zero AL
    out     dx, al                          ;select it
    inc     dx                              ;DX+1 = RGB writing location

    ;mov     si, offset palette              ;back to start of palette
    mov     cx, 768                         ;256*3 colours again
    cli                                     ;clear interrupts
    rep     outsb                           ;write all colours
    sti                                     ;allow interrupts
    ret
SetPal          ENDP

;----------------- FADE A PALETTE DOWN -------------------------------------
; *** PRE-LOAD:
;       SI = Offset of palette to fade
;       BX = Value to decrement by
DecPalette  PROC NEAR
    mov dx, DAC_INDEX
    xor ax, ax
    out dx, al      ;select colour 0
    inc dx      ;where we set RGB values    

    mov cx, 768 
  decloop:  
    xor ax, ax
    mov al, [si]
    sub ax, bx      ;word value as no byte penalty
    jnc StillOK     ;if carry, has gone negative
    xor ax, ax
  StillOk:      
    mov [si], al
    out dx, al       ;set the colour    
    inc si
  loop decloop
    ret
DecPalette  ENDP

;----------------- FADE A PALETTE UP -------------------------------------
; *** PRE-LOAD:
;       SI = Offset of temp palette (BLACK)
;       DI = Offset of destination palette
IncPalette  PROC NEAR
    mov dx, DAC_INDEX
    xor ax, ax
    out dx, al      ;select colour 0
    inc dx      ;where we set RGB values    

    mov cx, 768 
  incloop:  
    xor ax, ax
    mov al, [si]
    cmp [di], al
    je  NoInc
    inc al

NoInc:
    mov [si], al    ;save it
    out dx, al       ;set the colour    
    inc si
    inc di
  loop incloop
    ret
IncPalette  ENDP


; ---------------- SET A BLACK PALETTE ----------------------------------------
;*** PRE-LOAD:  None

BlackPal          PROC NEAR
                        ;set the palette up
    cld

    mov     dx, 3c8h                        ;colour NO selector
    xor     al, al                          ;zero AL
    out     dx, al                          ;select it
    inc     dx                              ;DX+1 = RGB writing location

    mov     cx, 768                         ;256*3 colours again
    xor ax, ax
    cli                                     ;clear interrupts
    rep     out dx, al                      ;write all colours
    sti                                     ;allow interrupts
    ret
BlackPal          ENDP

; ---------------------- WAIT FOR A VERTICAL RETRACE ---------------------
WaitRetrace PROC NEAR
    mov dx, 3dah
  ret1:
    in  al, dx
    and al, 08h
    jnz ret1
  ret2:
    in  al, dx
    and al, 08h
    jz  ret2
 
    ret
WaitRetrace ENDP

; ------------------ WAIT FOR A KEYPRESS ---------------------------------
WaitKey     PROC NEAR
    waiting:
    mov     ah, 1           ;Wait for keypress
    int     16h
    jz      waiting
    
    mov ah, 0           ;discard it from buffer
    int 16h
    
    ret
WaitKey     ENDP
        
; ------------------- SET VIDEO MODES ------------------------
Set13h          PROC NEAR
    mov     ax, 13h
    int     10h
    ret
Set13h          ENDP

SetText         PROC NEAR
    mov     ax, 03h
    int     10h
    ret
SetText         ENDP

;--------------------CLEAR SCREEN--------------------------------
ClearScreen PROC NEAR
    mov ax, 0a000h
    mov es, ax
    xor eax, eax
    xor edi, edi
    mov cx, 65535       ;clear the whole VGA
    rep stosd           ;386 only
    ret
ClearScreen ENDP




; ************************* MACROS ****************************

; ------------------ CLEAN EXIT TO DOS ------------------------
Finish  MACRO
    mov ax, 4c00h
    int 21h
    ENDM

; ------------------- SET UP DETAILS FOR RESIZE MEM -------------
;***  Must be called STRAIGHT AFTER startup!!
MemInit     MACRO       
    mov [ProgStartSeg], ES      ;save the PSP
    mov ax, ss              ;stack seg
    mov bx, sp              ;stack pointer
    shr bx, 4               ;in Paragraphs
    inc bx              ;plus 1 (safe)
    add ax, bx              ;make ONE good one!
    mov [ProgEndSeg], ax        ;store it
    call    ResizeMem
        ENDM
