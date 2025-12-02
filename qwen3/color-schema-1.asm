PUBLIC render
EXTERN memset : PROC

.code
; author: Qwen3 Coder

render:
  sub rsp, 48h
  push rbx
  push r12
  push rdi

; 生成一个基于正弦函数的ARGB颜色值
; 使用位操作创建正弦波效果

  ; 计算红色分量: 基于ecx的正弦波
  mov eax, ecx
  imul eax, 3               ; 频率因子
  and eax, 0FFh
  ; 创建简单的三角波近似正弦波
  cmp eax, 64
  jg red_down
  imul eax, 4               ; 0-64 映射到 0-256
  jmp red_done
red_down:
  mov ebx, 128
  sub ebx, eax
  imul ebx, 4
  mov eax, ebx
red_done:
  and eax, 0FFh
  shl eax, 16               ; 红色分量

  ; 计算绿色分量: 不同频率和相位
  mov ebx, ecx
  imul ebx, 5               ; 不同频率
  add ebx, 85               ; 相位偏移
  and ebx, 0FFh
  cmp ebx, 64
  jg green_down
  imul ebx, 4
  jmp green_done
green_down:
  mov ecx, 128
  sub ecx, ebx
  imul ecx, 4
  mov ebx, ecx
green_done:
  and ebx, 0FFh
  shl ebx, 8                ; 绿色分量
  or eax, ebx

  ; 计算蓝色分量: 第三个正弦波
  mov ebx, ecx
  imul ebx, 7               ; 不同频率
  add ebx, 170              ; 相位偏移
  and ebx, 0FFh
  cmp ebx, 64
  jg blue_down
  imul ebx, 4
  jmp blue_done
blue_down:
  mov ecx, 128
  sub ecx, ebx
  imul ecx, 4
  mov ebx, ecx
blue_done:
  and ebx, 0FFh
  or eax, ebx

  ; 设置alpha通道为255
  or eax, 0FF000000h

  mov ebx, eax              ; 颜色生成结束

  ; 恢复ecx的原始值
  mov ecx, ebx
  shr ecx, 24               ; 恢复原始ecx (实际上不需要，因为我们已经用完了)

  ; 重新计算用于memset
  mov ecx, edx              ; 恢复原来的参数
  mov eax, edx

  mov rcx, rdx
  mov edx, eax
  mov r8d, 80000h

  mov r12, rcx
  call memset

; 填充循环
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
