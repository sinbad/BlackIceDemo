SC_INDEX    equ 03c4h   ;Sequence Controller Index
CRTC_INDEX  equ 03d4h   ;CRT Controller Index
MISC_OUTPUT     equ 03c2h   ;Miscellaneous Output register
SCREEN_SEG  equ 0a000h  ;segment of display memory in mode X
DAC_INDEX   equ 03c8h   ;DAC registers
GC_INDEX    equ 03ceh   ;Graphics controller

.data

CRTParms label  word
        dw      00d06h  ;vertical total
        dw      03e07h  ;overflow (bit 8 of vertical counts)
        dw      04109h  ;cell height (2 to double-scan)
        dw      0ea10h  ;v sync start
        dw      0ac11h  ;v sync end and protect cr0-cr7
        dw      0df12h  ;vertical displayed
        dw      00014h  ;turn off dword mode
        dw      0e715h  ;v blank start
        dw      00616h  ;v blank end
        dw      0e317h  ;turn on byte mode
CRT_PARM_LENGTH equ     (($-CRTParms)/2)

        .code

; *********************** PROCEDURES ***************************

;------------------- Set Mode X ----------------------
; Must be called after mode 13h is already set
;***PRE-LOAD:
;   cx = horizontal width of virtual screen ( in steps of 8 )
;       ie 320 (1 screen) requires a pre-load of 40

SetModeX    PROC NEAR
    mov     dx, SC_INDEX            ;Sequencer Address register
    mov     ax, 0604h               ;Index 4, unset bit 3
    out     dx, ax                  ;disable Chain 4

    mov     dx, CRTC_INDEX
    mov     al, 13h                 ;mode 13..chain4 dimensions
    out     dx, al
    inc     dx                      ;port 03d5..where we set the size
    mov     al, cl                  ;screen width / 8
    out     dx, al

    mov     dx, CRTC_INDEX
    mov     ax, 0014h               ;disableing doubleword mode
    out     dx, ax

                    ;enableing byte mode
    mov     ax, 0E317h
    out     dx, ax
    ret
SetModeX    ENDP

;----------------------- Clear a Mode X Screen ----------------------
ClearModeX  PROC NEAR

    ;clear a full unchained screen
    mov     dx, 03c4h               ;Map mask register
    mov     al, 2
    out     dx, al
    inc     dx
    mov     al, 00001111b           ;ALL planes
    out     dx, al

    mov     ax, 0a000h
    mov     es, ax
    xor     di,di
    mov     cx, 32768
    mov     ax, 0                   ;colour = black
    cld
    rep     stosw                   ;put zeros 1 word at a time
    ret
ClearModeX  ENDP

;----------------- Set 320 by 240 mode -----------------
; Must be called after Mode X has been set

Set320x240 PROC NEAR
        mov     dx,SC_INDEX
        mov     ax,0100h
        out     dx,ax   ;synchronous reset while switching clocks

;   mov dx, MISC_OUTPUT
;   mov ax, 2c11h
;   out dx, ax      ;turn off write protect

        mov     dx,MISC_OUTPUT
        mov     al,0e3h
        out     dx,al           ;select 28 MHz dot clock & 60 Hz scanning rate

        mov     dx,SC_INDEX
        mov     ax,0300h
        out     dx,ax           ;undo reset (restart sequencer)

        mov     dx,CRTC_INDEX       ;reprogram the CRT Controller
        mov     al,11h          ;VSync End reg contains register write
        out     dx,al           ; protect bit
        inc     dx              ;CRT Controller Data register
        in      al,dx           ;get current VSync End register setting
        and     al,7fh          ;remove write protect on various
        out     dx,al           ; CRTC registers
        dec     dx              ;CRT Controller Index
        cld
        mov     si,offset CRTParms  ;point to CRT parameter table
        mov     cx,CRT_PARM_LENGTH  ;# of table entries
SetCRTParmsLoop:
        lodsw                   ;get the next CRT Index/Data pair
        out     dx,ax           ;set the next CRT Index/Data pair
        loop    SetCRTParmsLoop

        ret
Set320x240  ENDP

;---------------- SET SCAN LINE DUPLICATION ----------------------
; *** PRE-LOAD:
;       CL = No of duplicate scan lines 

SetDScan    PROC NEAR
    mov dx, CRTC_INDEX
    mov     al, 9
    out     dx, al
    inc     dx
    in      al, dx
    and     al, 0e0h                 ; Duplicate each scan ( x4 )
    add     al, cl
    out     dx, al
    ret
SetDScan    ENDP


; ---------------------Set the VGA Start Offset --------------------------
; *** PRE-LOAD:
;       BX = offset of screen (in multiples of 4)

SetVGAOffset    PROC NEAR
    mov dx, 3dah        ;wait for retrace before setting
  l1:
    in  al, dx
    and al, 08h
    jnz     l1
  l2:   
    in  al, dx
    and al,08h
    jz  l2
    
    mov dx, CRTC_INDEX
    mov al, 0ch
    mov ah, bh
    out dx, ax          ;high byte
    mov al, 0dh
    mov ah, bl          ;low byte
    out dx, ax
    ret
SetVGAOffset    ENDP    
    
;-------------------- SET WRITE MODE 1 ----------------------------------
; Sets up WM1 (write pixels from latches)

SetWM1  PROC NEAR
    mov dx, GC_INDEX
    xor ax, ax
    mov al, 08h
    out dx, al
    ret
SetWM1  ENDP

;-------------------- SET WRITE MODE 0 ----------------------------------
; Returns to normal pixel writing

SetWM0  PROC NEAR
    mov dx, GC_INDEX+1
    mov al, 0FFh
    out dx, al
    ret
SetWM0  ENDP

; -------------------------- SET WRITE MODE -------------------------------
; *** PRE-LOAD:
;       AH: Write Mode (0-3)

SetWriteMode    PROC NEAR
    mov     dx, GC_INDEX
    mov     al,5
    out     dx,al
    inc     dx
    in      al,dx
    and     al,11111100b    ;clear out write mode bits
    or      al,ah
    out     dx,al
    ret
SetWriteMode    ENDP

; --------------- LOAD IN MASK FILE ------------------------------ 
; *** PRE-LOAD :
;       DX -  offset of filename
;       DS -  segment of buffer for mask
;       DI -  offset of buffer for mask
;       CX -  size of mask file
    
LoadMask    PROC NEAR

    mov ax, 3d00h               ;Open file, read only
    int 21h
    mov bx, ax          ;store the handle in BX
    
    mov dx, di          ;& offset 
    mov ah, 3Fh             ;read file
    int 21h
    
    mov ah, 3Eh             ;close file (BX already set)
    int 21h
    ret

LoadMask    ENDP        




; ************************ MACROS ***************************************
        
;-------------------------- Set the Map Mask ------------------------------
;*** PRE-LOAD:
;       AH - bit mask (in low nibble)

SetMask     MACRO
    mov     dx, SC_INDEX
        mov     al,02h          ;Map Mask index
        out     dx,ax  
        ENDM
        
