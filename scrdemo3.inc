;*** Scrolly part of demo
.data

TestX       dw  0

Gravity     EQU 1
Floor       EQU 430
PAGE2       EQU 32320

ScrollyMsg  LABEL BYTE ; ^ =short delay, & = longer delay
DB "CALL  BLACK ICE& GUERNSEY'S   HOTTEST  ^ BBS...  OVER 2GB OF FILES"
DB " PLUS CD'S ROTATED!  DUAL 28K8 NODES... 0148139633& 0148135323& "
DB "OVER 200 ECHOMAIL AREAS FROM  FIDONET  ^ AND  MERCURY ^  INTERNET E-MAIL"
DB "   BLACKICE.CONQUEROR.CO.UK   EURO DIST SITE FOR LORE & ENVY TECHNOLOGY"
DB " RELEASES....  BACK TO SINBAD....CHEERS FOR THE INTRO DAMIEN.... "
DB "..BIG THANKS FROM THE AUTHOR GO OUT TO VARIOUS GURUS...MIKE ABRASH"
DB "....DRAEDEN.....LITHIUM......TRAN.....ID SOFTWARE..FUTURE CREW."
DB "...BULLFROG....PLUS GREETS TO FRONTMAN.....TA FOR YOUR GREET M8!!...SCUBED...DENTHOR....WISHBONE AND EVERYBODY"
DB " ON BLACK ICE.....AND OF COURSE THANKS TO DAMIEN GUARD FOR SETTING UP THE"
DB "LEADING BBS IN GUERNSEY....THERE IS NO SUBSTITUTE!! WHERE BLACK ICE GOES.."
DB "THE REST FOLLOW....."
DB "...ARE YOU REALLY STILL READING THIS? OK THEN...IT'S YOUR TIME...SOME "
DB "BACKGROUND ON ME THEN...LEAVE NOW WHILE YOU CAN...BTW I'M JUST WRITING"
DB " THIS AFTER WATCHING 'FIELD OF DREAMS' AGAIN ON T.V...I STILL CAN'T"
DB " WATCH IT WITHOUT BAWLING MY EYES OUT...DAMN....THIS IS THE FIRST DEMO "
DB "I HAVE PRODUCED...NOT INCLUDING A FEW MINOR EFFECT THANGS...SO COMMENTS "
DB "ARE WELCOME! I'VE CODED IN C FOR A WHILE AND MOVED TO ASM ABOUT 8 MONTHS "
DB "AGO.....AT 21 I HAVE SOME RUNNING TO DO TO CATCH UP WITH FUTURE CREW!! "
DB "   I PLAN TO CONCENTRATE ON GAMES DEVELOPMENT FROM NOW ON...BUT I EXPECT "
DB "THERE'LL BE A FEW SNIPPETS TO RELEASE AS DEMOS..  B.T.W. IF YOU WANT THE "
DB "SOURCE CODE TO THIS DEMO IT IS INCLUDED WITH THE ZIP...I BELIEVE STRONGLY "
DB "IN FREE RELEASE OF KNOWLEDGE....ALL YOU CODERS WHO CHARGE SHAREWARE FEES"
DB " FOR THE FULL VERSIONS OF YOUR CODE..SHAME ON YOU!!! I LEARNED A LOT FROM"
DB " OTHER PEOPLE'S RELEASED CODE, AND I INTEND TO RETURN THE FAVOUR...IF YOU "
DB "CAN CALL MY DISORGANISED JUMBLE OF CODE A FAVOUR!! WHICH REMINDS ME...BIG "
DB "THANKS TO FRONTMAN FOR RELEASING HIS EXCELLENT 8 CHANNEL MOD PLAYING "
DB "CODE..EVEN THOUGH I COULDN'T USE IT 'COS TASM 4 DOESN'T LIKE IT...BUT YOU'RE"
DB " THE ONLY PERSON I'VE KNOWN TO RELEASE MOD CODE OF THIS QUALITY FOR FREE."
DB " RESPECT DULY EARNED...YOU'RE A STAR. CREDIT GOES TO FUTURE CREW FOR THE "
DB "4 CHANNEL MOD CODE IN THIS DEMO...EVEN THOUGH IT IS A LITTLE OLD. I PLAN "
DB "TO WRITE MY OWN SOMETIME, IF I EVER GET THE TIME!!"
DB "   SO...YOU'RE STILL HERE? HMM...WHAT NEXT? STRANGELY ENOUGH FOR A DEMO "
DB "CODER I'M NOT FROM THE NETHERLANDS NOR AM I AT UNI. I'M STUDYING A DEGREE "
DB "IN MATHS AND COMPUTER SCIENCE IN MY SPARE TIME THOUGH...HENCE THE LACK OF "
DB "TIME FOR CODING!!    ADVICE TO NEW CODERS...FIRSTLY GET THE EXCELLENT "
DB "'PC GAMES PROGRAMMERS ENCYCLOPEDIA' AVAILABLE ON ANY GOOD BBS...WHEN "
DB "YOU'RE LOOKING FOR TIPS ON REALLY FAST CODE GO OUT AND BUY MIKE ABRASH'S "
DB "'ZEN OF CODE OPTIMIZATION'..I GOT IT AFTER WRITING THIS DEMO AND I'VE "
DB "LEARNT LOADS FROM IT....THIRDLY THE ONLY WAY TO BE A GOOD CODER IS TO "
DB "SPEND LOADS OF TIME CODING. THERE IS NO OTHER WAY. SORRY. "
DB "JEEZ YOU'RE STILL READING THIS CRAP?!? TIME FOR SOME FASCINATING..NOT..FACTS!"
DB "   1. SINBAD IS THE SECOND NAME I'VE HAD..THE OTHER WAS 'WARLOCK'...AND IS "
DB "DUE TO MY INEXPLICABLE LOVE OF ANY OLD FANTASY FILM FEATURING STOP FRAME "
DB "ANIMATION MONSTERS...ESPECIALLY SINBAD FILMS....PLUS IF I HAD THE EARRING"
DB " I RECKON I'D BE A PRETTY GOOD LIKENESS! HEHE..   2. I'M A "
DB "BIG FAN OF SCIENCE FICTION AND FANTASY NOVELS OR T.V. SHOWS...BIG FAVES "
DB "ARE DEEP SPACE 9 AND THE X FILES... 3. I HAVE NO LIFE...HEHE..  4. I "
DB "REALLY AM RUNNING OUT OF THINGS TO SAY NOW.... 5. DON'T YOU HATE IT "
DB "WHEN YOU FIND A BIT OF SHELL IN YOUR EGG SANDWICH?   6. PRINGLES CRISPS "
DB "ARE DEFINITELY IMPREGNATED WITH AN ADDICTIVE CHEMICAL...  7. DOES HEATHER"
DB " LOCKLEAR LIVE IN A DIFFERENT TIME CONTINUUM? 8. WHY THE HELL DON'T I "
DB "SHUT THE !?!?! UP? 9. WHAT'S THE CAPITAL OF INDIA? 10. DID YOU FALL ASLEEP "
DB "AT THE KEYBOARD OR SOMETHING?      THIS IS GONNA REPEAT PRETTY SOON...YOU'D "
DB "BETTER STOP IT OR PUT MASKING TAPE OVER THE SCREEN TO STOP YOUR TIMELINE "
DB "BEING INTERFERED WITH!     ARMADILLOS!!!   FRESH FRUIT!   POINTED STICKS! "
DB "   SOD IT...HERE COME THE WARDENS...GOTTA PACK THIS IN NOW!"
DB "  THANKS FOR READING....YOU MUST BE MORE NUTS THAN I AM....SEEEEEEEEEEEYA!!          $"

StartParams LABEL BYTE      ;make a smoother 'wave'                      
dw  0, 400
dw  2, 403
dw  4, 410
dw  6, 421
dw  -7,421 
dw  -5,410
dw  -3,403
dw  -1,400
dw  1, 401
dw  3, 406
dw  5, 415
dw  7, 428
dw  -6,415  
dw  -4,406
dw  -2,401
dw  999

MsgPtr      dw  ?       ;pointer to current letter in message
ParamPtr    dw  ?       ;pointer to sprite start parameters
APage       dw  0       ;Active page
Clip        dw  1       ;no of writes to do (for clipping)
DelayCount  dw  0       
Paused      dw  0       ;toggle - cannot use DelayCount as
                    ;that may have changed in the frame

Sprite STRUC
CurrentY    dw  0       ;Y momentum
XPos        dw  0       ;literal X value + 40 (to allow clipping)
YPos        dw  0       ;virtual Y value
CurrentPos  dw  0       ;for drawing
OldPos      dw  0       ;for erasing
GFXPtr      dw  0       ;offset of graphics for this letter
MaskPtr     dw  0       ;offset of mask for this letter
    ENDS

Letter  Sprite  11 dup ({CurrentY = 0})
DummyMask   db  (32*8) dup (0)  ;for spaces
FarRight    dw  0
FarLeft     dw  0

.code

SetUpSprites    PROC NEAR
    xor bx, bx
    mov cx, 11
    mov ax, 40          ;equiv to 0 X value on screen
  sloop:
    mov FS:[Letter[bx].XPos], ax
    mov FS:[Letter[bx].MaskPtr], offset DummyMask
    sub ax, 40
    mov FS:[Letter[bx].OldPos], ax      ;for background restoration
    mov FS:[Letter[bx].YPos], 400       ;starting Y
    add ax, 40
    add ax, 8           ;(8*4 = 32 pix wide)
    add bx, 14          ;size of struc
    loop    sloop

    mov FS:[FarRight], (10 * 14)    ;make last sprite far-right
    mov FS:[FarLeft], 0         ;make first sprite far-left

    mov FS:[MsgPtr], offset ScrollyMsg  ;set up pointer to message  
    mov FS:[ParamPtr], offset StartParams
    ret
SetUpSprites    ENDP
    
    

WriteBack   PROC NEAR

    mov ax, 0a000h
    mov es, ax
    mov bx, [APage]

    push    ds
    mov ax, [PicSeg]
    mov ds, ax
    xor si, si
    xor di, di  
    add di, bx          ;for when writing second page

    call    WaitRetrace
    mov ah, 0001b       ;plane 0
    SetMask
    mov cx, (19200 / 4)     ;1/4 of full screen (dwords)
    rep movsd
    
    xor di, di
    add di, bx          ;for when writing second page
    mov ah, 0010b       ;plane 1
    SetMask
    mov cx, (19200 / 4)
    rep movsd
    
    xor di, di
    add di, bx          ;for when writing second page
    xor si, si          ;si back to 0 too (ds to be altered)                
    mov ax, ds
    add ax, (38400 / 16)    ;increment ds (in paras)
    mov ds, ax
    mov ah, 0100b       ;plane 2
    SetMask
    mov cx, (19200 / 4)
    rep movsd
    
    xor di, di
    add di, bx          ;for when writing second page
    mov ah, 1000b       ;plane 3
    SetMask
    mov cx, (19200 / 4)
    rep movsd
    
    pop ds
    ret

WriteBack   ENDP

ScrollOn    PROC NEAR
    mov bx, 242*80


   scrlloop:
    call    SetVGAOffset
    PollSB
    sub     bx, 160
    jnz scrlloop
        
    xor bx, bx
    call    SetVGAOffset        ;make sure at row 0
    ret
ScrollOn    ENDP

WriteLetters    PROC NEAR
    ; write the letters into the off-screen VGA
    push    ds
    mov ax, [AlphaSeg]
    mov ds, ax          ;ES already set up
    xor si, si
    mov di, (76800 / 4)     ;just after picture
    PollSB              ;keep music going
    mov ah, 0001b       ;Plane 0
    SetMask
    mov cx, (10240 / 4)     ;(32 * 32 * 40) / 4 
    rep movsd               

    mov di, (76800 / 4)     ;just after picture
    PollSB              ;keep music going
    mov ah, 0010b       ;Plane 1
    SetMask
    mov cx, (10240 / 4)     ;(32 * 32 * 40) / 4 
    rep movsd               

    mov di, (76800 / 4)     ;just after picture
    PollSB              ;keep music going
    mov ah, 0100b       ;Plane 2
    SetMask
    mov cx, (10240 / 4)     ;(32 * 32 * 40) / 4 
    rep movsd               

    mov di, (76800 / 4)     ;just after picture
    PollSB              ;keep music going
    mov ah, 1000b       ;Plane 3
    SetMask
    mov cx, (10240 / 4)     ;(32 * 32 * 40) / 4 
    rep movsd
    pop ds              
    ret
WriteLetters    ENDP

CopyLetters PROC NEAR
    xor bx, bx      
    mov cx, 11      ;11 letters 
  cpyletloop:
    push    cx
    
    cmp bx, FS:[FarLeft]        ;left clip?
    jne notleft
    call    ClippedWriteL                   
    jmp skip
  notleft:  
    cmp bx, FS:[FarRight]
    jne notright
    call    ClippedWriteR
    jmp skip 
    ; Normal write if here
  notright:
    push    bx
    mov di, FS:[Letter[bx].CurrentPos]
    add di, FS:[APage]          ;adjust for active page
    mov si, FS:[Letter[bx].GFXPtr]
    mov bx, FS:[Letter[bx].MaskPtr]

    mov ecx, 200000h        ;32 lines
   cline:
    mov cx, fs:[bx]     ;get word from bx (masks for 2*2*4=16 pix)
    
    inc bx      
    inc bx
    mov ah, cl          
    SetMask
    mov al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov ah, cl          ;bottom part to go
    shr ax, 4
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si

    mov ah, ch          
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov ah, ch          ;bottom part to go
    shr ax, 4
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si

    mov cx, fs:[bx]     ;get word from bx (masks for 2*2*4=16 pix)
    
    inc bx      
    inc bx
    mov ah, cl          
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov ah, cl          ;bottom part to go
    shr ax, 4
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si

    mov ah, ch          
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov ah, ch          ;bottom part to go
    shr ax, 4
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
        add di, (80-8)
    xor cx, cx
    sub ecx, 10000h
    jnz cline
    
    pop bx
skip:                   ;arrive here if from a clipped write
    add bx, 14          ;next letter
    pop cx
    loop    cpyletloop


    ret
CopyLetters ENDP

ClippedWriteR   PROC NEAR
    push    bx

    cmp     FS:[Clip], 0
    je  All_clipped     ;if clip = 0 then no writes to do

    mov di, FS:[Letter[bx].CurrentPos]
    add di, FS:[APage]          ;adjust for active page
    mov si, FS:[Letter[bx].GFXPtr]
    mov bx, FS:[Letter[bx].MaskPtr]


    mov ecx, 200000h        ;32 lines
   CRcline:
    mov cx, fs:[bx]     ;get word from bx (masks for 2*2*4=16 pix)
    
    inc bx      
    inc bx
                        
    mov ah, cl          
    SetMask
    mov al, ds:[si]     ;no clip test - at least 1 write
    mov     es:[di], al 
    inc di
    inc si
    
    cmp FS:[Clip], 2        ;end of write?
    jb  ClipItR1        ;if so, skip the write
                    ;mask file already in sinc but SI/DI
                    ;are not - cannot skip the rest
    mov ah, cl          ;bottom part to go
    shr ax, 4
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItR1:
    inc di
    inc si

    cmp FS:[Clip], 3        ;end of write?
    jb  ClipItR2        ;if so, skip the write
    mov ah, ch          
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItR2:
    inc di
    inc si

    cmp FS:[Clip], 4        ;end of write?
    jb  ClipItR3        ;if so, skip the write
    mov ah, ch          ;bottom part to go
    shr ax, 4
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItR3:
    inc di
    inc si

    mov cx, fs:[bx]     ;get word from bx (masks for 2*2*4=16 pix)
    inc bx      
    inc bx
    
    cmp FS:[Clip], 5        ;end of write?
    jb  ClipItR4        ;if so, skip the write
    mov ah, cl          
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItR4:
    inc di
    inc si

    cmp FS:[Clip], 6        ;end of write?
    jb  ClipItR5        ;if so, skip the write
    mov ah, cl          ;bottom part to go
    shr ax, 4
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItR5:
    inc di
    inc si

    cmp FS:[Clip], 7        ;end of write?
    jb  ClipItR6        ;if so, skip the write
    mov ah, ch          
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItR6:
    inc di
    inc si

    cmp FS:[Clip], 8        ;end of write?
    jb  ClipItR7        ;if so, skip the write
    mov ah, ch          ;bottom part to go
    shr ax, 4
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItR7:
    inc di
    inc si
        add di, (80-8)
    xor cx, cx
    sub ecx, 10000h
    jnz CRcline
All_clipped:
    pop bx          ;get bx back here (avoid corrupting
                    ;stack)
    ret
ClippedWriteR ENDP

ClippedWriteL   PROC NEAR
    push    bx

    cmp     FS:[Clip], 7
    jae All_clipped2        ;if clip = 7 or 8 then no writes to do
                    ;opposite to right clip, and also left
                    ;sprite is offscreen for 2 frames
                    
    mov di, FS:[Letter[bx].CurrentPos]
    add di, FS:[APage]          ;adjust for active page
    mov si, FS:[Letter[bx].GFXPtr]
    mov bx, FS:[Letter[bx].MaskPtr]


    mov ecx, 200000h        ;32 lines
   CLcline:
    mov cx, fs:[bx]     ;get word from bx (masks for 2*2*4=16 pix)
    
    inc bx      
    inc bx
    
    cmp FS:[Clip], 0                    
    ja  ClipItL0
    mov ah, cl          
    SetMask
    mov al, ds:[si]     
    mov     es:[di], al 
ClipItL0:
    inc di
    inc si
    
    cmp FS:[Clip], 1        ;start of write?
    ja  ClipItL1        ;if not, skip the write
                    ;mask file already in sinc but SI/DI
                    ;are not - cannot skip the start
    mov ah, cl          ;bottom part to go
    shr ax, 4
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItL1:
    inc di
    inc si

    cmp FS:[Clip], 2        ;start of write?
    ja  ClipItL2        ;if not, skip the write
    mov ah, ch          
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItL2:
    inc di
    inc si

    cmp FS:[Clip], 3        ;start of write?
    ja  ClipItL3        ;if not, skip the write
    mov ah, ch          ;bottom part to go
    shr ax, 4
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItL3:
    inc di
    inc si

    mov cx, fs:[bx]     ;get word from bx (masks for 2*2*4=16 pix)
    inc bx      
    inc bx
    
    cmp FS:[Clip], 4        ;start of write?
    ja  ClipItL4        ;if not, skip the write
    mov ah, cl          
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItL4:
    inc di
    inc si

    cmp FS:[Clip], 5        ;start of write?
    ja  ClipItL5        ;if not, skip the write
    mov ah, cl          ;bottom part to go
    shr ax, 4
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItL5:
    inc di
    inc si

    cmp FS:[Clip], 6        ;start of write?
    ja  ClipItL6        ;if not, skip the write
    mov ah, ch          
    SetMask
    mov     al, ds:[si]
    mov     es:[di], al 
ClipItL6:
    inc di
    inc si

    mov ah, ch          ;bottom part to go
    shr ax, 4
    SetMask             ;no test - if in the loop there must
    mov     al, ds:[si]     ;be at least 1 write
    mov     es:[di], al 
    inc di
    inc si
        add di, (80-8)
    xor cx, cx
    sub ecx, 10000h
    jnz CLcline
All_clipped2:
    pop bx          ;get bx back here (avoid corrupting
                    ;stack)
    ret
ClippedWriteL ENDP
    
CopyBack    PROC NEAR
    xor bx, bx
    mov ecx, 0b0000h        ;11 sprites
    mov di, (19200 + 10240) ;base address of first background
    mov ah, 1111b
    SetMask
cpyloop:    
    mov si, FS:[Letter[bx].OldPos]
    add si, FS:[APage]      
    mov cx, 32
  cpyline:  
    mov al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    add si, (80 - 8)
    loop    cpyline
    
    add bx, 14
    sub ecx, 10000h
    jnz cpyloop
    

    ret
CopyBack    ENDP    

RestoreBack PROC NEAR
    xor bx, bx
    mov ecx, 0b0000h        ;11 sprites
    mov si, (19200 + 10240) ;base address of first background
    mov ah, 1111b
    SetMask
resloop:    
    mov di, FS:[Letter[bx].OldPos]
    add di, FS:[APage]      ;adjust for active page
    mov cx, 32
  rline:    
    mov     al, ds:[si]     ;unravelled for *speeeeeed* 8-)
    mov     es:[di], al     ;movsb is sloooow (can't use movsw
    inc di          ;or above because of latches - theres
    inc si          ;only 1 per plane
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    mov     al, ds:[si]
    mov     es:[di], al 
    inc di
    inc si
    add di, (80 - 8)
    loop    rline
    
    add bx, 14
    sub ecx, 10000h
    jnz resloop
    

    ret
RestoreBack ENDP        

CalcPositions   PROC NEAR

    cmp FS:[DelayCount], 0
    je  PauseOff
    dec FS:[DelayCount]
    jmp Cont
PauseOff:
    mov FS:[Paused], 0
Cont:

    xor bx, bx
    mov cx, 11
  posloop:
    xor eax, eax
    mov ax, FS:[Letter[bx].CurrentPos]  ;get pos before adjustment
    mov FS:[Letter[bx].OldPos], ax  ;and save it

    cmp FS:[Paused], 1
    je  NoXDec
    dec FS:[Letter[bx].XPos]    
NoXDec:
    mov ax, FS:[Letter[bx].CurrentY]
    add ax, Gravity
    mov FS:[Letter[bx].CurrentY], ax
    add FS:[Letter[bx].YPos], ax
    mov ax, FS:[Letter[bx].YPos]
    cmp ax, Floor
    jb  NoBounce
    mov ax, Floor - 1
    mov FS:[Letter[bx].YPos], ax
    not FS:[Letter[bx].CurrentY]    ;reverse direction, less 1
  NoBounce:
    
    FASTIMUL edx, eax, 240          ;mult by 240 
    shr edx, 9              ;div by 512
    FASTIMUL ax, dx, 80         ;mult by X Dimension
    add ax, FS:[Letter[bx].XPos]        
    sub ax, 40              ;adjust for X offset
    mov FS:[Letter[bx].CurrentPos], ax  ;save calc'd position
    
    add bx, 14              ;next element           
    loop    posloop
    

    ret
CalcPositions   ENDP
    

ReadLetter  PROC NEAR
    mov bx, FS:[MsgPtr]
    xor ax, ax
    mov al, FS:[bx]     ;get next letter
    
    cmp al, 94          ;"^" sign
    jne NoSmallPause
    mov FS:[DelayCount], 100    ;set up pause in message
    inc FS:[MsgPtr]     ;increment pointer
    inc bx          ;increase bx for immediate effect
    mov al, FS:[bx]     ;get next letter in advance for when
                    ; letters start moving again    
    mov FS:[Paused], 1      ;Pause on
    mov FS:[Clip], 0        ;set clip correctly
    jmp NoPause
NoSmallPause:
    cmp al, 38          ;"&" sign
    jne NoPause
    mov FS:[DelayCount], 300    ;set up pause in message
    inc FS:[MsgPtr]     ;increment pointer
    inc bx          ;increase bx for immediate effect
    mov al, FS:[bx]     ;get next letter in advance for when
                    ; letters start moving again    
    mov FS:[Paused], 1      ;Pause on
    mov FS:[Clip], 0        ;set clip correctly


NoPause:
    cmp al, 36          ;"$" sign
    jne NoWrap
    mov bx, offset ScrollyMsg   ;reset message pointer
    mov FS:[MsgPtr], bx
    mov al, FS:[bx]
 NoWrap:
    inc FS:[MsgPtr]
    cmp al, 32          ;[space]
    jne notspace
    mov bx, FS:[FarRight]       
    mov FS:[Letter[bx].MaskPtr], offset DummyMask
                       ;put blank mask (GFX doesn't matter)
    ret
notspace:
    cmp al, 57          ;'9'
    ja  alpha           ;goto A-Z (inc ?)   
    cmp al, 48          ;'0'
    jb  cntrl           ;goto extra characters


                ;if here, must be numeric
    sub ax, 22          ; sub 48 ('0'), add 26 (start of nos)
    jmp assignGFX
cntrl:
    cmp al, '!'
    jne not_shriek
    mov ax, 36          
    jmp assignGFX
  not_shriek:
    cmp al, '.'
    jne not_stop
    mov ax, 38
    jmp assignGFX
  not_stop:
    cmp al, 39          ; " ' "
    jne not_apos
    mov ax, 39          
    jmp assignGFX
  not_apos:
                    ;*invalid character*
    mov bx, FS:[FarRight]       
    mov FS:[Letter[bx].MaskPtr], offset DummyMask
                       ;put blank mask (GFX doesn't matter)
    ret
        
alpha:

    cmp al, '?'
    jne not_q
    mov ax, 37          
    jmp assignGFX
  not_q:

    sub ax, 65          ;all alphabetic characters
assignGFX:

    mov dx, ax          ;save letter value
    shl ax, 8           ;mult by 1024 (32*8) - size of GFX
    add ax, 19200       ;base offset of letter graphics
    mov bx, FS:[FarRight]       
    mov FS:[Letter[bx].GFXPtr], ax  ;put letter in far right
    shl dx, 7           ;mult by 128 (32*32/8)- size of mask
    mov ax, offset BitMask  ;base offset
    add ax, dx          ;add positioning
    mov FS:[Letter[bx].MaskPtr], ax  ;put mask in far right
    ret
ReadLetter  ENDP

CheckLetters    PROC NEAR
    mov bx, FS:[FarLeft]
    cmp FS:[Letter[bx].XPos], 32 ;32-40 = -8 ie off screen (8*4 = 32)
    ja  NoNewLetter
    mov FS:[FarRight], bx   ;Move this one over to Far Right

    mov bx, FS:[ParamPtr]   ;get start parameters
    mov ax, FS:[bx]     ;get CurrentY (or end marker)
    cmp ax, 999         ;end of list?
    jne NotEndParams
    mov bx, offset StartParams
    mov FS:[ParamPtr], bx   ;reset ptr
    mov ax, FS:[bx]     ;get next one
NotEndParams:
    add FS:[ParamPtr], 4    ;increment ptr (2 words)
    add bx, 2
    mov dx, FS:[bx]     ;get YPos
    
    mov bx, FS:[FarRight]   ;get bx back
    mov FS:[Letter[bx].XPos], 120  ;set max X (offscreen)
    mov FS:[Letter[bx].YPos], dx   ;set YPos
    mov FS:[Letter[bx].CurrentY], ax  ;set CurrentY
    add bx, 14          ;FarLeft = next one right
    cmp bx, (10 * 14)
    jna ValidBX
    xor bx, bx          ;Letter 0 if over 11th letter
ValidBX:        
    mov FS:[FarLeft], bx    ;save new FarLeft
    call    ReadLetter      ;get next letter from message
NoNewLetter:    
    ret
CheckLetters    ENDP

FlipVisualPage  PROC NEAR
    mov bx, FS:[APage]
    xor bx, PAGE2       ;flip address 0/32320
    mov FS:[APage], bx
    mov bx, FS:[APage]
    call    SetVGAOffset        ;set it (includes retrace)
                    ;WHY DOES IT WORK THIS WAY AROUND???!
    ret
FlipVisualPage  ENDP    

FadeOut PROC NEAR
    mov si, offset BPalette
    mov dx, DAC_INDEX
    xor ax, ax
    out dx, al      ;select colour 0
    inc dx      ;where we set RGB values    

    mov cx, 768 
  decloop1: 
    xor ax, ax
    mov al, FS:[si]
    sub ax, 2       ;word value as no byte penalty
    jnc StillOK2        ;if carry, has gone negative
    xor ax, ax
  StillOk2:     
    mov FS:[si], al
    out dx, al       ;set the colour    
    inc si
  loop decloop1
    ret
FadeOut ENDP


; **************************** MAIN PART *****************************
ScrollDemo  PROC NEAR
    call    Set13h
    mov cx, 40          ;v-screen 320 pix across
    call    SetModeX
    call    BlackPal        ;Black out palette to save flicker
    call    ClearModeX
    call    Set320x240      ;set 320 x 240 mode

    call    BlackPal        ;just to make sure
    
    mov bx, (240*80)
    call    SetVGAOffset        ;position below main screen
    
    call    WriteBack
    mov si, offset BPalette
    call    SetPal
    call    ScrollOn
    call    WaitRetrace     ;ensure offset has 'taken'
    call    WriteLetters
    xor [APage], PAGE2      ;flip the page pointer
    call    WriteBack       ;write in the second background
    xor [APage], PAGE2      ;flip pointer back
    
    push    ds
    pop fs          ;FS = DS
    push    es
    pop ds          ;VGA seg ito DS

    mov ah, 1
    call    SetWriteMode        ;set WM1

    call    SetUpSprites
    call    ReadLetter
    call    CalcPositions       ;initial set ups
    call    CopyBack
  keepup:
    cmp FS:[DelayCount], 0
    jne StillPaused         ;if stationary, no change in clip
    and FS:[Clip], 7
    inc FS:[Clip]   
StillPaused:                        
    call    FlipVisualPage
        
    call    RestoreBack
    call    CalcPositions
    call    CopyBack
    call    CopyLetters
    PollSB
    call    CheckLetters

    
    mov ah, 1
    int 16h
    jz  keepup
    
    
    mov ah, 0
    int 16h         ;discard keystroke

    mov cx, 50
  fadeloop2:
    push    cx
    cmp FS:[DelayCount], 0
    jne StillPaused2            ;if stationary, no change in clip
    and FS:[Clip], 7
    inc FS:[Clip]   
StillPaused2:                       
    call    FlipVisualPage
        
    call    RestoreBack
    call    CalcPositions
    call    CopyBack
    call    CopyLetters
    PollSB
    call    CheckLetters
    
    call    FadeOut
    
    pop cx
    loop    fadeloop2
    
                    
    push    fs
    pop ds
    
    
    ret
ScrollDemo  ENDP