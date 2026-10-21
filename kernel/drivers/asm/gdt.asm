.text:
global loadGDT

gdt:
    ;Null descriptor
    dq 0x00000000

    ;Code Segment
    dw 0xFFFF ;Limit
    dw 0x00 ;Base
    db 0x0 ;Base
    db 0x9A;access
    db 0xCF ;Limit + Flags
    db 0x0 ;Base

    ;Data Segment
    dw 0xFFFF ;Limit
    dw 0x00 ;Base
    db 0x0 ;Base
    db 0x92;access
    db 0xCF ;Limit + Flags
    db 0x0 ;Base

gdtr:
    dw 0x17
    dd gdt

loadGDT:
    LGDT [gdtr]
    call reloadSegments
    RET


reloadSegments:
    JMP 0x08:.reload_CS
    ret

.reload_CS:
    MOV AX, 0x10
    MOV DS, AX
    MOV ES, AX
    MOV FS, AX
    MOV GS, AX
    MOV SS, AX
    RET
