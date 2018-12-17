assume cs:code,ds:data,ss:stack

stack segment stack
	dw 0,0,0,0,0,0,0,0
stack ends

data segment
	db 'BasIcasshole    '
	db 'BasIcasshole    '
	db 'BasIcasshole    '
	db 'BasIcasshole    '
data ends

code segment

	start:
	mov ax,stack
	mov ss,ax
	mov sp,16
	mov ax,data
	mov ds,ax
	mov bx,0
	mov cx,4
s:	
	push cx
	mov si,0
	mov cx,4
s0:
	mov al,[3+bx+si]
	and al,11011111B
	mov [3+bx+si],al
	inc si
	loop s0
	add bx,16
	pop cx
	loop s
	
	mov ax,4c00H
	int 21H
		
		
code ends

end start
