PUBLIC render
EXTERN memset : PROC

.code

render:
  sub rsp, 48h
  push rbx
  push r12
  push rdi

; 生成一个ARGB颜色值
  or ebx, ebx
  mov bl, cl
  shl ebx, 1
  or ebx, 0ff000000h
; 颜色生成结束

  mov eax, ecx
  mov rcx, rdx
  mov edx, eax
  mov r8d, 80000h

  mov r12, rcx

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

  pop rdi
  pop r12
  pop rbx

  add rsp,48h
  ret

END
