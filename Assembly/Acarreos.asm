; Acarreos.asm
; Traduccion a x86-64 puro (MASM64 + WinAPI, sin Irvine32) de Acarreos.cpp
; Calcula el complemento a uno de 10101 (representado por digitos decimales)
;
; Ensamblar / enlazar (sin CRT, entrada directa en "main"):
;   ml64.exe /c Acarreos.asm
;   link.exe /entry:main /subsystem:console Acarreos.obj kernel32.lib

extrn ExitProcess:proc
extrn GetStdHandle:proc
extrn WriteConsoleA:proc

STD_OUTPUT_HANDLE equ -11

.data
numberBin       DWORD 10101
complementOne   DWORD 0
hStdOut         QWORD 0
bytesWritten    DWORD 0
newline         BYTE 0Dh, 0Ah
buffer          BYTE 24 DUP(?)

.code

; -----------------------------------------------------------
; int size(int number)
; Cuenta cuantos digitos decimales tiene "number"
; Entrada: ECX = number       Retorno: EAX = size
; (funcion "hoja": no hace CALL, no necesita shadow space)
; -----------------------------------------------------------
size PROC
    xor r8d, r8d            ; size = 0
L_size:
    cmp ecx, 0
    je L_size_end
    inc r8d                 ; size++
    mov eax, ecx
    cdq
    mov r9d, 10
    idiv r9d                ; eax = number / 10
    mov ecx, eax            ; number = eax
    jmp L_size
L_size_end:
    mov eax, r8d             ; return size
    ret
size ENDP

; -----------------------------------------------------------
; int pow(int number, int s)
; Entrada: ECX = number, EDX = s      Retorno: EAX = result
; (funcion "hoja": no hace CALL, no necesita shadow space)
; -----------------------------------------------------------
pow PROC
    xor eax, eax             ; result = 0
    xor r8d, r8d             ; i = 0

L_pow:
    cmp r8d, edx
    jge L_pow_end
    cmp eax, 0
    jne L_pow_else
    mov eax, ecx
    imul eax, ecx            ; result = number * number
    jmp L_pow_cont
L_pow_else:
    imul eax, ecx            ; result *= number
L_pow_cont:
    inc r8d                  ; i++
    jmp L_pow

L_pow_end:
    cmp eax, 0
    jne L_pow_ret
    mov eax, 1               ; result == 0 ? 1 : result
L_pow_ret:
    ret
pow ENDP

; -----------------------------------------------------------
; Convierte ECX (entero sin signo) a decimal y lo imprime + CRLF
; usando WriteConsoleA. Reserva shadow space (20h) + slot para el
; 5to parametro (lpReserved) que exige la convencion x64 de Windows.
; -----------------------------------------------------------
WriteInt PROC
    push rbx
    push rsi
    push rdi
    sub rsp, 30h

    mov eax, ecx              ; eax = number
    lea rbx, buffer
    add rbx, 24                ; rbx -> un byte despues del ultimo util
    xor esi, esi                ; esi = cantidad de digitos
    mov edi, 10

L_conv:
    xor edx, edx
    div edi                     ; eax = eax/10, edx = eax%10
    add dl, '0'
    dec rbx
    mov [rbx], dl
    inc esi
    test eax, eax
    jnz L_conv

    mov rcx, hStdOut
    mov rdx, rbx
    mov r8d, esi
    lea r9, bytesWritten
    mov qword ptr [rsp+20h], 0
    call WriteConsoleA

    mov rcx, hStdOut
    lea rdx, newline
    mov r8d, 2
    lea r9, bytesWritten
    mov qword ptr [rsp+20h], 0
    call WriteConsoleA

    add rsp, 30h
    pop rdi
    pop rsi
    pop rbx
    ret
WriteInt ENDP

; -----------------------------------------------------------
; int main()
; -----------------------------------------------------------
main PROC
    push rbx
    sub rsp, 20h              ; shadow space para GetStdHandle/pow/WriteInt/ExitProcess

    mov ecx, STD_OUTPUT_HANDLE
    call GetStdHandle
    mov hStdOut, rax

    mov complementOne, 0
    xor ebx, ebx               ; i = 0

L1:
    cmp ebx, 5
    jge L1_end

    mov eax, numberBin
    cdq
    mov r9d, 10
    idiv r9d                   ; edx = numberBin % 10
    cmp edx, 0
    jne L1_skip

    mov ecx, 10                ; number = 10
    mov edx, ebx                ; s = i
    call pow
    add complementOne, eax      ; complementOne += pow(10, i)

L1_skip:
    mov eax, numberBin
    cdq
    mov r9d, 10
    idiv r9d
    mov numberBin, eax          ; numberBin = numberBin / 10

    inc ebx                     ; i++
    jmp L1

L1_end:
    mov eax, complementOne
    cdq
    mov r9d, 10
    idiv r9d                    ; eax = complementOne / 10
    mov ecx, eax
    call WriteInt

    xor ecx, ecx
    call ExitProcess

    add rsp, 20h
    pop rbx
    ret
main ENDP

END
