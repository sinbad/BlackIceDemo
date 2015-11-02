;*** Fire part of Black Ice demo



.data
EVEN
FireBuf db      72*160 dup (0)

RandPos         dw      (0)
RandOff         dw      (0)
DatName         db      "FIREWORD.DAT", 0

EVEN
RandTab LABEL BYTE
    db      0, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0
    db      255, 0, 255, 255, 0, 255, 0, 255, 0, 255, 0, 0
    db      255, 0, 255, 255, 0, 0, 255, 0, 0, 0, 255, 255
    db      0, 255, 0, 255, 255, 255, 0, 255, 255, 0, 0, 255
    db      255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255
    db      0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 255, 255
    db      255, 0, 0, 255, 0, 255, 255, 0, 0, 255, 255, 0
    db      255, 255, 0, 0, 255, 0, 255, 0, 255, 0, 255, 255
    db      0, 255, 0, 0, 0, 0, 255, 255, 0, 255, 0, 0
    db      255, 255, 0, 255, 0, 0, 255, 255, 255, 0, 0, 0
    db      255, 0, 255, 255, 255, 0, 255, 0, 0, 255, 0, 0
    db      255, 255, 255, 0, 255, 255, 255, 0, 255, 0, 255, 255
    db      0, 255, 255, 0, 0, 255, 255, 255, 0, 0, 255, 0
    db      0, 255, 0, 0, 255, 0, 255, 0, 255, 0, 255, 255
    db      255, 0, 0, 0, 255, 255, 255, 255, 0, 255, 0, 255
    db      0, 255, 255, 255, 0, 255, 0, 0, 0, 255, 255, 255
    db      0, 255, 0, 255, 0, 0, 255, 0, 0, 0, 255, 255
    db      255, 255, 255, 255, 255, 0, 255, 255, 255, 0, 255, 255
    db      0, 255, 255, 0, 0, 0, 0, 0, 255, 0, 255, 255
    db      0, 0, 255, 0, 0, 255, 0, 255, 0, 0, 0, 0
    db      255, 0, 255, 255, 0, 0, 255, 0, 0, 0, 0, 255
    db      255, 255, 0, 255, 0, 255, 255, 255, 255, 255, 255, 0
    db      0, 255, 255, 255, 0, 0, 0, 0, 255, 0, 0, 255
    db      0, 0, 255, 0, 255, 0, 0, 0, 255, 255, 255, 0
    db      255, 255, 255, 0, 0, 255, 0, 255, 255, 0, 255, 255
    db      255, 255, 255, 255, 255, 0, 0, 255, 0, 0, 255, 255
    db      0, 255, 0, 255, 0, 255, 255, 0, 0, 0, 255, 255
    db      255, 255, 0, 255, 255, 0, 255, 0, 255, 255, 0, 255
    db      0, 255, 255, 255, 0, 0, 0, 255, 255, 0, 0, 0
    db      255, 0, 0, 255, 0, 0, 255, 0, 255, 255, 255, 255
    db      0, 255, 0, 0, 255, 255, 255, 0, 0, 0, 255, 0
    db      255, 255, 0, 0, 0, 255, 0, 0, 0, 0, 0, 255
    db      255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 255, 255
    db      255, 255, 255, 0, 255, 255, 255, 0, 0, 0, 0, 255
    db      0, 255, 0, 255, 0, 0, 0, 255, 0, 0, 0, 0
    db      255, 255, 0, 255, 255, 0, 0, 0, 0, 0, 0, 255
    db      255, 0, 0, 0, 255, 0, 255, 255, 255, 255, 0, 255
    db      0, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0
    db      0, 0, 255, 0, 0, 0, 255, 255, 255, 0, 0, 255
    db      255, 0, 0, 0, 255, 255, 0, 0, 255, 255, 0, 255
    db      255, 255, 0, 0, 255, 0, 0, 255, 0, 255, 0, 0
    db      0, 0, 255, 0, 0, 0, 255, 0, 0, 255, 255, 255
    db      0, 0, 255, 0, 0, 0, 255, 255, 255, 0, 0, 255
    db      0, 0, 0, 0, 255, 255, 255, 255, 255, 0, 255, 0
    db      0, 0, 0, 0, 255, 0, 255, 0, 0, 0, 255, 0
    db      0, 255, 0, 255, 255, 255, 255, 0, 0, 0, 255, 255
    db      0, 0, 255, 0, 255, 255, 255, 0, 255, 255, 255, 0
    db      255, 0, 255, 255, 0, 0, 255, 255, 0, 255, 0, 0
    db      255, 0, 255, 255, 0, 255, 0, 0, 0, 255, 255, 255
    db      0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 255
    db      255, 0, 0, 0, 255, 255, 255, 0, 255, 255, 0, 255
    db      255, 255, 0, 255, 0, 255, 0, 255, 0, 0, 0, 0
    db      255, 255, 255, 0, 0, 0, 255, 0, 255, 0, 0, 255
    db      255, 0, 0, 0, 255, 0, 255, 0, 0, 255, 0, 0
    db      0, 255, 0, 0, 255, 255, 255, 0, 255, 0, 0, 0
    db      255, 0, 0, 0, 255, 255, 0, 255, 255, 0, 0, 0
    db      0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255
    db      255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255
    db      255, 0, 255, 0, 0, 255, 255, 0, 255, 0, 255, 0
    db      0, 0, 255, 255, 0, 255, 255, 255, 0, 255, 255, 255
    db      0, 255, 0, 255, 0, 0, 0, 0, 255, 255, 255, 255
    db      255, 0, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255
    db      0, 255, 255, 0, 0, 255, 0, 255, 255, 0, 255, 0
    db      255, 255, 255, 255, 255, 0, 255, 0, 0, 0, 0, 0
    db      255, 0, 0, 0, 0, 0, 255, 255, 0, 255, 0, 0
    db      0, 255, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255
    db      0, 0, 255, 0, 0, 0, 0, 0, 255, 255, 0, 255
    db      0, 0, 0, 255, 0, 0, 255, 255, 255, 255, 0, 255
    db      0, 0, 255, 0, 0, 255, 0, 255, 0, 255, 255, 255
    db      0, 0, 0, 255, 0, 0, 0, 255, 255, 0, 255, 0
    db      0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0
    db      0, 255, 0, 0, 255, 255, 0, 255, 255, 255, 255, 0
    db      0, 0, 255, 255, 0, 0, 255, 255, 0, 255, 255, 0
    db      0, 255, 0, 255, 255, 0, 0, 0, 0, 255, 0, 255
    db      255, 255, 255, 0, 0, 255, 255, 0, 255, 0, 255, 0
    db      255, 0, 0, 0, 255, 255, 255, 255, 0, 255, 255, 0
    db      0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0
    db      255, 0, 0, 255, 0, 0, 255, 255, 255, 0, 255, 0
    db      255, 255, 255, 0, 0, 0, 255, 0, 0, 255, 255, 255
    db      0, 255, 0, 0, 255, 0, 0

EVEN
palette LABEL BYTE
    db      0, 0, 0, 0, 0, 6, 0, 0, 6, 0, 0, 7
    db      0, 0, 8, 0, 0, 8, 0, 0, 9, 0, 0, 10
    db      2, 0, 10, 4, 0, 9, 6, 0, 9, 8, 0, 8
    db      10, 0, 7, 12, 0, 7, 14, 0, 6, 16, 0, 5
    db      18, 0, 5, 20, 0, 4, 22, 0, 4, 24, 0, 3
    db      26, 0, 2, 28, 0, 2, 30, 0, 1, 32, 0, 0
    db      32, 0, 0, 33, 0, 0, 34, 0, 0, 35, 0, 0
    db      36, 0, 0, 36, 0, 0, 37, 0, 0, 38, 0, 0
    db      39, 0, 0, 40, 0, 0, 40, 0, 0, 41, 0, 0
    db      42, 0, 0, 43, 0, 0, 44, 0, 0, 45, 0, 0
    db      46, 1, 0, 47, 1, 0, 48, 2, 0, 49, 2, 0
    db      50, 3, 0, 51, 3, 0, 52, 4, 0, 53, 4, 0
    db      54, 5, 0, 55, 5, 0, 56, 6, 0, 57, 6, 0
    db      58, 7, 0, 59, 7, 0, 60, 8, 0, 61, 8, 0
    db      63, 9, 0, 63, 9, 0, 63, 10, 0, 63, 10, 0
    db      63, 11, 0, 63, 11, 0, 63, 12, 0, 63, 12, 0
    db      63, 13, 0, 63, 13, 0, 63, 14, 0, 63, 14, 0
    db      63, 15, 0, 63, 15, 0, 63, 16, 0, 63, 16, 0
    db      63, 17, 0, 63, 17, 0, 63, 18, 0, 63, 18, 0
    db      63, 19, 0, 63, 19, 0, 63, 20, 0, 63, 20, 0
    db      63, 21, 0, 63, 21, 0, 63, 22, 0, 63, 22, 0
    db      63, 23, 0, 63, 24, 0, 63, 24, 0, 63, 25, 0
    db      63, 25, 0, 63, 26, 0, 63, 26, 0, 63, 27, 0
    db      63, 27, 0, 63, 28, 0, 63, 28, 0, 63, 29, 0
    db      63, 29, 0, 63, 30, 0, 63, 30, 0, 63, 31, 0
    db      63, 31, 0, 63, 32, 0, 63, 32, 0, 63, 33, 0
    db      63, 33, 0, 63, 34, 0, 63, 34, 0, 63, 35, 0
    db      63, 35, 0, 63, 36, 0, 63, 36, 0, 63, 37, 0
    db      63, 38, 0, 63, 38, 0, 63, 39, 0, 63, 39, 0
    db      63, 40, 0, 63, 40, 0, 63, 41, 0, 63, 41, 0
    db      63, 42, 0, 63, 42, 0, 63, 43, 0, 63, 43, 0
    db      63, 44, 0, 63, 44, 0, 63, 45, 0, 63, 45, 0
    db      63, 46, 0, 63, 46, 0, 63, 47, 0, 63, 47, 0
    db      63, 48, 0, 63, 48, 0, 63, 49, 0, 63, 49, 0
    db      63, 50, 0, 63, 50, 0, 63, 51, 0, 63, 52, 0
    db      63, 52, 0, 63, 52, 0, 63, 52, 0, 63, 52, 0
    db      63, 53, 0, 63, 53, 0, 63, 53, 0, 63, 53, 0
    db      63, 54, 0, 63, 54, 0, 63, 54, 0, 63, 54, 0
    db      63, 54, 0, 63, 55, 0, 63, 55, 0, 63, 55, 0
    db      63, 55, 0, 63, 56, 0, 63, 56, 0, 63, 56, 0
    db      63, 56, 0, 63, 57, 0, 63, 57, 0, 63, 57, 0
    db      63, 57, 0, 63, 57, 0, 63, 58, 0, 63, 58, 0
    db      63, 58, 0, 63, 58, 0, 63, 59, 0, 63, 59, 0
    db      63, 59, 0, 63, 59, 0, 63, 60, 0, 63, 60, 0
    db      63, 60, 0, 63, 60, 0, 63, 60, 0, 63, 61, 0
    db      63, 61, 0, 63, 61, 0, 63, 61, 0, 63, 62, 0
    db      63, 62, 0, 63, 62, 0, 63, 62, 0, 63, 63, 0
    db      63, 63, 1, 63, 63, 2, 63, 63, 3, 63, 63, 4
    db      63, 63, 5, 63, 63, 6, 63, 63, 7, 63, 63, 8
    db      63, 63, 9, 63, 63, 10, 63, 63, 10, 63, 63, 11
    db      63, 63, 12, 63, 63, 13, 63, 63, 14, 63, 63, 15
    db      63, 63, 16, 63, 63, 17, 63, 63, 18, 63, 63, 19
    db      63, 63, 20, 63, 63, 21, 63, 63, 21, 63, 63, 22
    db      63, 63, 23, 63, 63, 24, 63, 63, 25, 63, 63, 26
    db      63, 63, 27, 63, 63, 28, 63, 63, 29, 63, 63, 30
    db      63, 63, 31, 63, 63, 31, 63, 63, 32, 63, 63, 33
    db      63, 63, 34, 63, 63, 35, 63, 63, 36, 63, 63, 37
    db      63, 63, 38, 63, 63, 39, 63, 63, 40, 63, 63, 41
    db      63, 63, 42, 63, 63, 42, 63, 63, 43, 63, 63, 44
    db      63, 63, 45, 63, 63, 46, 63, 63, 47, 63, 63, 48
    db      63, 63, 49, 63, 63, 50, 63, 63, 51, 63, 63, 52
    db      63, 63, 52, 63, 63, 53, 63, 63, 54, 63, 63, 55
    db      63, 63, 56, 63, 63, 57, 63, 63, 58, 63, 63, 59
    db      63, 63, 60, 63, 63, 61, 63, 63, 62, 0, 0, 0

.code

mainbit         PROC NEAR
    
    call    WaitRetrace


    mov     dx, 3c4h                        ;Sequencer Register
    mov     al, 2                           ;Index 2
    mov     ah, 0011b                       ;Enable planes 1 and 2
    out     dx, ax

    mov     ax, 0a000h                      ;ES -> VGA
    mov     es, ax
    mov     si, offset FireBuf              ;DS:SI -> Fire buffer
    
    mov     di, (320/4) * 15               ;ES:DI -> 25 lines down VGA
    
    
    mov     cx, ((68*160) / 2) / 4         ; 1/2 of the buffer, in DWORDS
    rep     movsd
    
    mov     dx, 3c4h                        ;Sequencer Register
    mov     al, 2                           ;Index 2
    mov     ah, 1100b                       ;Enable planes 3 and 4
    out     dx, ax

    ;mov     si, offset FireBuf              ;DS:SI -> Fire Buffer +1
    ;inc     si
    add     si, 80 * 4                      ;skip 2 seed lines - TEST!!!
    
    mov     di, (320/4) * 15               ;ES:DI -> 25 lines down VGA 
        
    mov     cx, ((68*160) / 2) / 4         ; 1/2 of the buffer in DWORDS
    rep     movsd


    mov     ax, ds
    mov     es, ax                          ;ES = DS
    mov     si, offset RandTab              ;pointer to Random numbers
    add     si, [RandPos]                   ;offset the position
    mov     di, offset FireBuf              ;pointer to Fire Buffer
    add     di, 70*80                       ;put DI at the last 2 lines

    mov     cx, 80                          ;80 pixels across buffer
                        ;(for planes 1&2)                                               
    seedloop:
    movsb                                   ;mov SI -> DI
    inc     [RandPos]                       ;Store RandPos (add 3)
    inc     [RandPos]
    inc     [RandPos]
    inc     si                              ;Inc source (only 2 req'd)
    inc     si
    cmp     [RandPos], 700                  ;Have we read 400 randoms?
    jb      noreset

    mov     [RandPos], 0                    ;Reset RandPos
    mov     ax, [RandOff]
    add     [RandPos], ax                   ;Random no. offset adjust
    mov     si, offset RandTab              ;pointer to Random numbers
    add     si, ax                          ;add the offset adjust

    inc     [RandOff]                       ;increase the offset
    and     [RandOff], 255                  ;limit offset 0-255
    ;sub     si, 700                         ;And SI
    noreset:
    loop    seedloop

    mov     si, offset FireBuf              ;Source in Fire Buffer
    add     si, 70*80                       ;SI = 2 lines from bottom
    mov     di, si                          ;Dest also there
    add     di, 80                          ;but one line down

    mov     cx, 80 / 4                      ;copy one 80 pixel seed line
    rep     movsd                           ;down to the next
                ;(Important to have 2 seed lines to get the
                ; proper fire effect)

    ;Now do the same with planes 3&4
    
    mov     si, offset RandTab              ;pointer to Random numbers
    add     si, [RandPos]                   ;offset the position

    mov     di, offset FireBuf              ;pointer to Fire Buffer
    add     di, 142*80                      ;put DI at the last 2 lines

    mov     cx, 80                          ;80 pixels across buffer
                        ;(for planes 1&2)                                               
    seedloop1:
    movsb                                   ;mov SI -> DI
    inc     [RandPos]                       ;Store RandPos (add 3)
    inc     [RandPos]
    inc     [RandPos]
    inc     si                              ;Inc source (only 2 req'd)
    inc     si
    cmp     [RandPos], 700                  ;Have we read 400 randoms?
    jb      noreset1

    mov     [RandPos], 0                    ;Reset RandPos
    mov     ax, [RandOff]

    add     [RandPos], ax                   ;Random no. offset adjust
    mov     si, offset RandTab              ;pointer to Random numbers
    add     si, ax                          ;add the offset adjust

    inc     [RandOff]                       ;increase the offset
    and     [RandOff], 255                  ;limit offset 0-255
    ;sub     si, 700                         ;And SI
    noreset1:
    loop    seedloop1

    mov     si, offset FireBuf              ;Source in Fire Buffer
    add     si, 142*80                      ;SI = 2 lines from bottom
    mov     di, si                          ;Dest also there
    add     di, 80                          ;but one line down

    mov     cx, 80 / 4                      ;copy one 160 pixel seed line
    rep     movsd                           ;down to the next
                ;(Important to have 2 seed lines to get the
                ; proper fire effect)

    ; *** NOW AVERAGE THE PIXELS TO GIVE A FIRE EFFECT ! ***


    mov     cx, 70*80                       ;average 50 lines * 80 pixels
    
    mov     di, offset FireBuf
    
    xor     ax, ax                          ;ONE individual one (the first
    xor     dx, dx                          ;element)
                        ;otherwise it includes one
                        ;of the seed line elements!
                        ;(because its the first, and
                        ;therefore no element to its
                        ;left.                                          
    mov     dl, [di+5760]                   ;<- see that? No LEFT pixel!
    add     ax, dx                          ;source 1 line below so fire
    mov     dl, [di+80]                     ;'scrolls' up
    add     ax, dx
    mov     dl, [di+5760]                   
    add     ax, dx                          
    mov     dl, [di+160]                    
    add     ax, dx
    shr     ax, 2                           ;divide by 4 to get average
    jz      nodec                           ;skip decrement if already 0
    dec     ax
    jz      nodec
    dec     ax
    ;jz      onenodec
    ;dec     ax
    
    onenodec:
    mov     [di], ax                        ;put averaged pixel in di
    inc     di                              ;next one
    dec     cx

    avloop:
    xor     ax, ax
    xor     dx, dx
    mov     dl, [di+5759]                   ;add 4 surrounding pixels
    add     ax, dx                          ;source 1 line below so fire
    mov     dl, [di+80]                     ;'scrolls' up
    add     ax, dx
    mov     dl, [di+5760]
    add     ax, dx
    mov     dl, [di+160]
    add     ax, dx
    shr     ax, 2                           ;divide by 4 to get average
    jz      nodec                           ;skip decrement if already 0
    dec     ax
    ;jz      nodec
    ;dec     ax
    ;jz      nodec
    ;dec     ax
    
    nodec:
    mov     [di], ax                        ;put averaged pixel in di
    inc     di                              ;next one
    loop    avloop                          ;loop to top, decrement cx

    mov     cx, 70*80                      ;average 50 lines * 80 pixels
    ;mov     di, offset FireBuf            ;leave DI as it is
    
    add     di, 80*2                        ;skip 2 seed lines
    avloop1:
    xor     ax, ax
    xor     dx, dx
    mov     dl, [di-5760]                   ;add 4 surrounding pixels
    add     ax, dx                          ;source 1 line below so fire
    mov     dl, [di+80]                     ;'scrolls' up
    add     ax, dx
    mov     dl, [di-5759]
    add     ax, dx
    mov     dl, [di+160]
    add     ax, dx
    shr     ax, 2                           ;divide by 4 to get average
    jz      nodec1                          ;skip decrement if already 0
    dec     ax
    ;jz      nodec1
    ;dec     ax
    ;jz      nodec1
    ;dec     ax
    
    nodec1:
    mov     [di], ax                        ;put averaged pixel in di
    inc     di                              ;next one
    loop    avloop1                         ;loop to top, decrement cx

    PollSB                  ;poll the music


    
    ret
mainbit         ENDP

LoadPic         PROC NEAR

    push    ds
    mov     ax, 3d00h                       ;Open file, read only
    mov     dx, offset DatName
    int     21h
    mov     bx, ax                          ;store the handle in BX
    
    mov     ax, [WordSeg]           ;allocated segment
    mov     ds, ax
    xor     dx, dx
    
    mov     cx, 32000                       ;size of data file
        
    mov     ah, 3Fh                         ;read file
    int     21h
    
    mov     ah, 3Eh                         ;close file (BX already set)
    int     21h

    pop     ds
    ret
LoadPic         ENDP

WriteBuffer     PROC NEAR
    ;CX = offset into Pic Buffer (ie the text line)
    push    ds
    mov     ax, ds
    mov     es, ax

    mov     ax, [WordSeg]
    mov     ds, ax
    
    xor     si, si 
    add     si, cx                          ;line offset
    mov     di, offset FireBuf
    add     di, (55 * 80) + 5               ;offset into fire (plane 1)
    
    mov     cx, (160 * 10) / 2              ;half of one sentence
     xorloop:   
    mov     al, [si]                        ;get byte from Picture Buffer               
    or      es:[di], al                     ;OR it with FireBuffer
    inc     si
    inc     di
    loop    xorloop

    mov     di, offset FireBuf
    add     di, (72 * 80) + (55 * 80) + 5   ;offset into fire (plane 2)
    mov     cx, (160 * 10) / 2
     xorloop1:   
    mov     al, [si]                        ;get byte from Picture Buffer               
    or      es:[di], al                     ;OR it with FireBuffer
    inc     si
    inc     di
    loop    xorloop1


    pop     ds
    ret
WriteBuffer     ENDP

FillBack        PROC NEAR
    
    mov     ax, 0a000h                      ;Set up VGA pointer
    mov     es, ax
    xor     di,di
    mov     dx, 3c4h                        ;Seq Address
    mov     ah, 1111b                       ;ALL planes
    mov     al, 2                           ;Map Mask
    out     dx, ax
    
    mov     ah, 8                           ;Fill with blue
    mov     al, 8
    mov     cx, (25*80) / 2                 ;Fill 25 lines, word at a time
                        ;(80*4 = 320 | Unchained)
    rep     stosw                           ;Fill it
    add     di, (48 * 80)                   ;skip over the fire part
    mov     cx, (25 * 80)                   ;Another 25 lines
    rep     stosw
    ret
FillBack        ENDP

FireDemo    PROC NEAR

    call    Set13h
    mov cx, 40          ;320 wide
    call    SetModeX
    mov cx, 3
    call    SetDScan        ;set doublescan
    
    call    ClearModeX
    mov     si, offset palette
    call    setpal

    call    FillBack
    mov ecx, 2000000h
    waitkey2:
    call    mainbit
    
    sub ecx, 10000h 
    jnz     waitkey2


    call    WriteBuffer
     
    mov     cx, 150
     funkloop:
    push    cx
    call    mainbit
    xor     cx, cx                          ;Line 1 of text
    call    WriteBuffer
    pop     cx
    loop    funkloop

    mov     cx, 30
     funkloop2:
    push    cx
    call    mainbit
    pop     cx
    loop    funkloop2
    
    mov     cx, 150
     funkloop3:
    push    cx
    call    mainbit
    mov     cx, (1 * (160*10) )             ;1 line down
    call    WriteBuffer
    pop     cx
    loop    funkloop3
    
    mov     cx, 200
     funkloop4:
    push    cx
    call    mainbit
    pop     cx
    loop    funkloop4
    
    mov ecx, 400000h        ;64 decrements  
  fadeloop:
    mov si, offset Palette 
    mov bx, 1
    call    DecPalette
    call    mainbit
    sub ecx, 10000h
    jnz fadeloop


    ret
FireDemo    ENDP

