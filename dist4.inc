; distortion part of demo

.data

BorderName  db  "border.dat", 0
DistName    db  "mid.dat",0
DistPal     db  "mid.pal",0
CredName    db  "creds.dat",0
CredPal     db  "creds.pal",0
Tab1Ptr     dw  0
Tab2Ptr     dw  0
TempPal     db  768 dup (0)

EVEN
Sinetable1 LABEL BYTE
DW 0, 0, 1, 2, 2, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 8, 9, 9, 9, 9, 9
DW 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 2, 2, 1 
DW 0, 0, 0, -1, -2, -2, -3, -4, -4, -5, -5, -6, -6, -7, -7, -8, -8, -8, -9, -9, -9, -9
DW -9, -9, -9, -9, -9, -9, -9, -9, -8, -8, -8, -7, -7, -6, -6, -5, -5, -4, -4, -3, -2, -2
DW -1, 0
Stop1   dw $
Sinetable2 LABEL BYTE
DW  0, 0, 128, 128, 256, 256, 384, 384, 512, 512, 512, 640, 640, 768, 768, 896, 896, 896, 1024, 1024, 1024, 1024
DW 1152, 1152, 1152, 1152, 1152, 1152, 1152, 1152, 1280, 1152, 1152, 1152, 1152, 1152, 1152, 1152, 1152, 1024, 1024, 1024, 1024, 896
DW 896, 896, 768, 768, 640, 640, 640, 512, 512, 384, 384, 256, 256, 128, 128, 0, 0, 0, -128, -128, -256, -256
DW -384, -384, -512, -512, -512, -640, -640, -768, -768, -896, -896, -896, -1024, -1024, -1024, -1024, -1152, -1152, -1152, -1152, -1152, -1152
DW -1152, -1152, -1280, -1152, -1152, -1152, -1152, -1152, -1152, -1152, -1152, -1024, -1024, -1024, -1024, -896, -896, -896, -768, -768, -640, -640
DW -640, -512, -512, -384, -384, -256, -256, -128, -128, 0 
Stop2 dw $


.code

DistMap PROC NEAR
  xor   di, di
  xor   edx, edx
  mov   bx, [Tab1Ptr]       ;horizontal wave (change every line down)
                    ;reset at start only
  PollSB    
  mov   ecx, 800000h        ;128 lines in high word
  maplineloop:

    mov cx, 64          ;128/2 - less loops
    mov dx, [Tab2Ptr]       ;vertical wave (change per pixel across)
                    ;reset every line
    maploop:        

;@@1    
    mov si, [bx]
    add si, [edx]       ;BX+edx (this is the full wave offset)
    add si, di          ;add offset of where we are now
    and si, 3FFFh       ;modulus 16384
    
            
;   add bx, 2           ;do this here to give the 486 pipeline
    add dx, 2           ;time to pre-calc address 
    cmp [Stop2], dx     ;end of list 2?
    je  ResetTab2       ;jump only if equal - less branching
       Comeback2:

    mov al, FS:[si]     
    mov FS:[di+16384], al       
    inc di
; @@2
    mov si, [bx]
    add si, [edx]       ;BX+edx (this is the full wave offset)
    add si, di          ;add offset of where we are now
    and si, 3FFFh       ;modulus 16384

;   add bx, 2           ;do this here to give the 486 pipeline
    add dx, 2           ;time to pre-calc address 
    cmp [Stop2], dx     ;end of list 2?
    je  ResetTab4       ;jump only if equal - less branching
       Comeback4:
    mov al, FS:[si]     
    mov FS:[di+16384], al   
    inc di
    

    dec cx
    jnz maploop

    add bx, 2    
    cmp [Stop1], bx     ;end of list 1?
    je  ResetTab1       ;jump only if equal - less branching
   Comeback1:

    sub ecx, 10000h
    jnz maplineloop     ;next line down

    ret


ResetTab1:
    mov bx, offset SineTable1   ;reset the ol' pointer
    jmp Comeback1
ResetTab2:
    mov dx, offset SineTable2   ;reset
    jmp Comeback2
ResetTab4:
    mov dx, offset SineTable2   ;reset
    jmp Comeback4

DistMap ENDP


WriteMap    PROC NEAR
    push    ds
    mov ax, fs
    mov ds, ax 
    mov si, 16384       ;start of distorted map
    mov di, 11616
    
    mov ecx, 800000h    ;128 in high 2 bytes
 mapline:
    mov cx, 32      ;32x4=128
    rep movsd
    add di, 192
    sub ecx, 10000h
    jnz mapline
    
    pop ds
    ret
WriteMap    ENDP

WriteBorder PROC NEAR
    push    ds
    mov ax, 0a000h
    mov es, ax
    mov ax, fs
    mov ds, ax
    xor si, si
    xor di, di
    
    mov cx, 16000   ;64000 / 4
    rep movsd
            
    
    pop ds
    ret
WriteBorder ENDP


DistDemo    PROC NEAR
    PollSB
    mov bx, 4000    ;short-term 64k buffer disk->mem->VGA
    call    GetMem
    mov fs, ax      ;save seg
    mov dx, offset BorderName
    mov di, 0       ;ax already set to seg by GetMem
    call    LoadData    

    PollSB
    mov dx, offset DistPal
    mov cx, offset BPalette
    call    LoadPal
    
    mov si, offset BPalette
    call    SetPal

    call    WriteBorder 
    
    
    mov ax, fs
    mov es, ax
    call    FreeMem     ;free temporary segment
    
    
    PollSB
    mov bx, 2048    ;16384 bytes - 128x128
                ;x2 - one source, one dest
    call    GetMem      ;allocate memory (no mem checking, will
                ;be enuf if it's got this far)
    mov fs, ax      ;set FS to picture segment
    mov [Tab1Ptr], offset SineTable1
    mov [Tab2Ptr], offset SineTable2    

    
    mov dx, offset DistName
    mov di, 0       ;placing in buffer - ax already set     
    call    LoadData


    mov ax, 0a000h
    mov es, ax
    
DistortionLoop:
    call    DistMap
    call    WriteMap
    mov ax, [Tab1Ptr]
    add ax, 2
    cmp [Stop1], ax
    ja  NoTabReset1
    mov ax, offset SineTable1
NoTabReset1:
    mov [Tab1Ptr], ax

    mov ax, [Tab2Ptr]
    add ax, 2
    cmp [Stop2], ax
    ja  NoTabReset2     ;change this!!!
    mov ax, offset SineTable2
NoTabReset2:
    mov [Tab2Ptr], ax

    call    DistMap         ;this part repeated so Tab2Ptr
    call    WriteMap        ;is incremented at 1/2 the speed
    mov ax, [Tab1Ptr]
    add ax, 2
    cmp [Stop1], ax 
    ja  NoTabReset3
    mov ax, offset SineTable1
NoTabReset3:
    mov [Tab1Ptr], ax
    
    mov ah, 1
    int 16h
    jz  DistortionLoop
    
    mov ah, 0
    int 16h 

    mov cx, 100
DistFadeLoop:
    push    cx
    mov bx, 1
    mov si, offset BPalette
    call    DecPalette

    call    DistMap
    call    WriteMap
    mov ax, [Tab1Ptr]
    add ax, 2
    cmp [Stop1], ax
    ja  FNoTabReset1
    mov ax, offset SineTable1
FNoTabReset1:
    mov [Tab1Ptr], ax

    mov ax, [Tab2Ptr]
    add ax, 2
    cmp [Stop2], ax
    ja  FNoTabReset2        ;change this!!!
    mov ax, offset SineTable2
FNoTabReset2:
    mov [Tab2Ptr], ax

    call    DistMap         ;this part repeated so Tab2Ptr
    call    WriteMap        ;is incremented at 1/2 the speed
    mov ax, [Tab1Ptr]
    add ax, 2
    cmp [Stop1], ax 
    ja  FNoTabReset3
    mov ax, offset SineTable1
FNoTabReset3:
    mov [Tab1Ptr], ax
    
    pop cx
    dec cx
    jnz DistFadeLoop    
        
    mov ax, fs
    mov es, ax
    call    FreeMem
    
    PollSB
    mov bx, 4000        
    call    GetMem          ;reserve 64k mem
    mov fs, ax
    
    mov dx, offset CredName
    mov di, 0
    call    LoadData
    
    PollSB
    mov dx, offset CredPal
    mov cx, offset BPalette
    call    LoadPal
    
    call    BlackPal        ;zero palette (incase fade ont complete)
    
    
    call    WriteBorder
    
    mov cx, 100
ICredLoop:
    push    cx
    call    WaitRetrace     
    mov si, offset TempPal
    mov di, offset BPalette
    call    IncPalette

    PollSB
    pop cx
    loop    ICredLoop   


    mov cx, 500
CredLoop:
    call    WaitRetrace     ;delay

    PollSB
    loop    CredLoop    

    
    mov cx, 100 
FCredLoop:
    push    cx
    call    WaitRetrace
    mov bx, 1
    mov si, offset BPalette ;not optimised - doesn't need it
    call    DecPalette
    PollSB
    pop cx
    loop    FCredLoop   
    
    ret
DistDemo    ENDP