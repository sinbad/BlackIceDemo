.model large
.stack 200h
.386

JUMPS

EXTRN  stmik_asm:far
include stand2.inc
include modex2.inc
include sound.inc
include fdemo.inc
include scrdemo3.inc
include scale3.inc
include dist4.inc

.data
PicName     db  "mxblack2.dat", 0
PalName     db  "mxblack2.pal", 0
WordSeg         dw  ?
PicSeg      dw  0
BPalette    db  768 dup (?)
AlphaName   db  "leeslet2.dat", 0
AlphaSeg    dw  ?
MaskName    db  "leeslet2.mas", 0

BitMask     db  5120 dup (?)

OutMemMsg   db  13, 10,"Sorry, you need more memory free to run this!", 13, 10
        db  "If you're really struggling for memory, try running the demo without music,"
        db  13, 10, "but you only need about 500k free!$"

FinalText       db  13, 10, "         -== The Black Ice Demo - An Envy Technologies Release ==-    "  
        db  13, 10
        db      13, 10, "                Code      :  Sinbad        (aka Steve Streeting)"
        db  13, 10, "                Music     :  Sinbad"
        db  13, 10, "                Graphics  :  Wishbone      (aka Lee Harris) "
        db  13, 10, "                Raytracing:  Sinbad"
        db  13, 10                             
        db  13, 10, "Software used to create this demo:"
        db  13, 10, "Borland Turbo Assembler 4.0"
        db  13, 10, "Microsoft Quick C 2.5"
        db  13, 10, "ScreamTracker 3.21"
        db  13, 10, "PC Paintbrush"
        db  13, 10, "Piclab 1.91"
        db  13, 10, "Image Alchemy 1.5"
        db  13, 10, "Persistence of Vision (POV) 2.0"
        db  13, 10, "Moray 1.5"
        db  13, 10, "Adobe Photoshop 3.0"
        db  13, 10
        db  13, 10, "Copyright Envy Technologies 1995$"
.code

STXName        db      "melting2.stx", 0


; ********************* PROCEDURES ***********************************
        
InitStuff   PROC NEAR
    

    mov     bx, (32000 / 16)
    call    GetMem
    jc  MemErr
    mov     [WordSeg], ax            ;save allocated segment
    call    LoadPic

    mov bx, (76800/16)      ;allocate a buffer for the pic      
    call    GetMem
    jc  MemErr
    mov [PicSeg], ax

    mov bx, (40960 / 16)    ;allocate for letters
    call    GetMem
    jc  MemErr
    mov [AlphaSeg], ax
    
    mov dx, offset PicName
    mov ax, [PicSeg]
    xor di, di
    call    LoadData

    mov dx, offset AlphaName
    mov ax, [AlphaSeg]
    xor di, di
    call    LoadData

    mov dx, offset PalName
    mov cx, offset BPalette
    call    LoadPal

    mov dx, offset MaskName
    mov di, offset BitMask
    mov cx, 5120
    call    LoadMask    

    call    SoundSetup
    cmp [OutMemFlag], 1
    je  MemErr
    
    cmp [SBInstalled], 1
    jne NoSB1
    mov bx, [ModSeg]
    StartSTX
  NoSB1:
    ret
  MemErr:
    call    CleanUp1
    mov dx, offset OutMemMsg
    mov ah, 9
    int 21h
    Finish
InitStuff   ENDP

CleanUp2    PROC NEAR
    cmp     [SBInstalled], 1
    jne     skipSBstop
    StopSTX
skipSBstop:
    
    

    mov ax, [ModSeg]
    mov es, ax
    call    FreeMem

    ret
CleanUp2        ENDP


CleanUp1    PROC NEAR
    mov     ax, [WordSeg]
    mov     es, ax
    call    FreeMem
        
    mov ax, [PicSeg]
    mov es, ax
    call    FreeMem

    mov ax, [AlphaSeg]
    mov es, ax
    call    FreeMem
    ret
CleanUp1    ENDP

; ********************** CODE SEG DATA *********************************

tabpos          dw      0                       ;Random number table position


; ********************* MAIN CODE ***************************************
.startup
    MemInit
    

    call    InitStuff
    call    FireDemo
    call    ScrollDemo  
    call    CleanUp1
    call    ScaleDemo
    call    DistDemo
    call    CleanUp2


TheEnd:
    call    SetText
    mov     dx, offset FinalText
    mov     ah, 9
    int     21h
    Finish
END


