section .data
    msg db 'Hola mundo', 0Ah  ; Mensaje con salto de línea

section .text
    global _start

_start:
    mov eax, 4        ; Llamada al sistema "write"
    mov ebx, 1        ; Escribir en la salida estándar
    mov ecx, msg      ; Dirección del mensaje
    mov edx, 11       ; Longitud del mensaje
    int 0x80          ; Interrupción al sistema operativo

    mov eax, 1        ; Llamada al sistema "exit"
    xor ebx, ebx      ; Código de salida 0
    int 0x80
end:
    svc 0