global loadPageDirectory
loadPageDirectory:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 8]
    mov cr3, eax
    mov esp, ebp
    pop ebp
    ret

global enablePaging
enablePaging:
    push ebp
    mov ebp, esp
    mov eax, cr0
    or eax, 080000000
    mov cr0, eax
    mov esp, ebp
    pop ebp
ret
