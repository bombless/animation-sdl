PUBLIC render
EXTERN memset : PROC

.code

pick_color:
; 生成一个ARGB颜色值
  or eax, eax
  mov al, cl
  shl eax, 2
  or eax, 0ff000000h
; 颜色生成结束
  ret


render:

  push rbx ; rbx 存原始的step值以及后面生成的颜色值
  push r12 ; r12 存缓冲区基址
  push rdi ; rdi 在后面动用来填充内存，所以要保护起来

  sub rsp, 48h

  mov r12, rdx
  mov rbx, rcx

  mov rcx, rbx
  call pick_color

  mov ebx, eax
  mov rcx, r12
  mov edx, ebx
  mov r8d, 80000h


  call memset

; 假设：
; eax = 要填充的值
; rdi = 目标内存地址
; ecx = 要填充的字节数（必须是 4 的倍数）
  mov eax, ebx
  mov rdi, r12
  mov ecx, 80000h

fill_loop:
    test    ecx, ecx
    jz      done
    mov     [rdi], eax
    add     rdi, 4
    sub     ecx, 4
    jmp     fill_loop

done:

  mov edx, 0ffh
  mov rcx, r12
  add rcx, 80000h
  mov r8d, 80000h
  call memset

  add rsp,48h

  pop rdi
  pop r12
  pop rbx

  ret

END
