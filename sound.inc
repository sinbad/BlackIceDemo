;************************************************************************
;* Filename : SOUND.INC                                                 *
;* Purpose  : Include file for SB interface STMIK                       *
;************************************************************************


.data

ModSeg          dw      ?
SBInstalled     db      0
SBirq           db      0
BaseAddr        dw      0
MixRate         dw      0
SBText1         db      13, 10, "            -=  Sinbad's Sound Card Setup =-"                                                                                
        db      13, 10, 13, 10, "Do you have a SB compatible sound card? (Y/N)$"
SBText2         db      13, 10, "What's the IRQ setting?$ "
SBText3         db      13, 10, "What's the base address? Choose:"
        db      13, 10, "Press: [0] - 200h"
        db      13, 10, "       [1] - 210h"
        db      13, 10, "       [2] - 220h"
        db      13, 10, "       [3] - 230h"
        db      13, 10, "       [4] - 240h", 13, 10, "$"
SBText4         db      13, 10, "What Mixing Rate? (higher = better) Choose:"
        db      13, 10, "Press: [0] - 5000Hz"
        db      13, 10, "       [1] - 10000Hz"
        db      13, 10, "       [2] - 16000Hz", 13, 10, "$"



.code


;--------------------- LOAD A STX FILE ----------------------------------
; *** PRE-LOAD:
;              [FileName] = ASCIIZ filename
;              DX = offset to filename
;              AX = minimum paragraphs reserved
;*** RETURNS: 
;              DX = segment of MOD


tmpseg  dw      0
filerquit db    1
LoadSTX         PROC    NEAR
        push    ds
        mov     bp,ax
        mov     ax,cs
        mov     ds,ax ;set ds=cs
        mov     ah,3dh ;open file
        mov     al,0 ;read only
        int     21h
        jc      ferror
        mov     bx,ax ;store filehandle to bx
        ;get length of file (seek to end)
        mov     ah,42h
        mov     al,2
        mov     cx,0
        mov     dx,0
        int     21h
        jc      ferror
        ;get memory
        push    bx
        shr     dx,1
        rcr     ax,1
        shr     dx,1
        rcr     ax,1
        shr     dx,1
        rcr     ax,1
        shr     dx,1
        rcr     ax,1
        mov     bx,ax
        inc     bx ;one extra, just in case :-)
        cmp     bx,bp
        ja      loff1
        mov     bx,bp
loff1:          
        call    GetMem
        ;mov     ah,48h
        ;int     21h
        jc      ferror
        mov     cs:tmpseg,ax
        pop     bx
        ;Seek file back to the beginning
        mov     ah,42h
        mov     al,0
        mov     cx,0
        mov     dx,0
        int     21h
        jc      ferror
        ;read file
        mov     ds,cs:tmpseg
faga:           mov     ah,3fh
        mov     cx,32768
        mov     dx,0
        int     21h
        jc      ferror
        mov     dx,ds
        add     dx,800h
        mov     ds,dx
        cmp     ax,32768
        je      faga
        ;close file
        mov     ah,3eh
        int     21h
        mov     dx,cs:tmpseg ;segment
        xor     ax,ax
        pop     ds
        ret
ferror2:        mov     ax,1
        pop     ds
        ret
ferror:         cmp     cs:filerquit,0
        je      ferror2
        pop bx          ;get rid of bx
        pop     ds
        inc [OutMemFlag]        ;note out of memory
        ret         
LoadSTX         ENDP


SoundSetup      PROC NEAR
    mov     dx, offset SBText1
    mov     ah, 9
    int     21h
    
    mov     ah, 1
    int     21h
    cmp     al, 'y'
    je      GotSB
    cmp     al, 'Y'
    je      GotSB
    ret                             ;no SB installed - exit
 GotSB:
    inc     [SBInstalled]           ;note SB is installed
    mov     dx, offset SBText2
    mov     ah, 9
    int     21h
    
    mov     ah, 1                   ;get IRQ
    int     21h
    sub     al, '0'                 ;ASCII -> decimal
    mov     [SBirq], al             ;save irq
    
    mov     dx, offset SBText3
    mov     ah, 9
    int     21h

 GetBase:
    mov     ah, 1                   ;get base address
    int     21h             
    cmp     al, '6'
    jae     GetBase                 ;invalid answer
    sub     al, '0'                 ;ASCII -> decimal       
    xor     ah, ah
    shl     ax, 4                   ;mult by 16 (2x0h)
    add     ax, 200h                ;final base address
    mov     [BaseAddr], ax          ;save base address
    
 GetMix:
    mov     dx, offset SBText4
    mov     ah, 9
    int     21h
    
    mov     ah, 1                   ;get Mixing rate
    int     21h
    cmp     al, '3'
    jae     GetMix                  ;invalid response
    cmp     al, '2'
    jb      mix2
    mov     [MixRate], 16000        
    jmp     endmix
 mix2:
    cmp     al, '1'
    jb      mix3
    mov     [MixRate], 10000
    jmp     endmix
 mix3:  
    mov     [MixRate], 5000
 endmix:


    cmp     [SBInstalled], 1
    jne     skipSBsetup             ;skip the next bit if no SB
    mov     dx, offset STXName
    mov     ax, 0
    call    LoadSTX                
    mov     [ModSeg], dx            ;save segment of MOD
    
    mov     ax, 0                   ;function - init SB
    mov     bh, [SBirq]             ;IRQ x, mode 1 (SB)
    mov     bl, 1
    mov     cx, [BaseAddr]          ;address
    mov     dx, [MixRate]           ;mix speed
    call    stmik_asm

    mov     ax, 3
    mov     bx, 1
    call    stmik_asm               ;manual polling
skipSBsetup:

    ret
SoundSetup      ENDP

StartSTX    MACRO
    ;** pre-load: BX = segment of mod to play
    mov     ax, 1                   ;play MOD
    call    stmik_asm
    ret
    ENDM

StopSTX     MACRO
    mov     ax, 2                   ;stop MOD
    call    stmik_asm               
    ENDM

PollSB  MACRO
    mov     ax, 4
    call    stmik_asm                       ;poll music     
    ENDM