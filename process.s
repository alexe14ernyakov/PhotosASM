bits	64
; processing of jpeg file
section	.text
global	process
process:
	push	rbp
	mov		rbp, rsp

	mov		rax, rdx
	mul		rcx
	mul		r8

	mov		r12, rax

	mov		r13, r8

	cmp		r12, 0
	je		exit

	mov		r14, 0

cicle_start:
	mov		al, [rsi+r14]

	mov		[rdi+r14], al
	mov		[rdi+r14+1], al
	mov		[rdi+r14+2], al

	add		r14, r13

	cmp		r14, r12
	jl		cicle_start

exit:
	leave
	ret
