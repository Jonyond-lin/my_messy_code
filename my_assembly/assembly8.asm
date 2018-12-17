assume cs:code

data segment
	dw 1,2,3,4,5,6,7,8
	dd 0,0,0,0,0,0,0,0
data ends


;stack segment stack
	
;stack ends

code segment

	start:
	mov ax,data
	mov ds,ax
	mov si,0
	mov di,16
	
	mov cx,8
s:	mov bx,[si]
	call cube
	mov [di],ax
	;mov [di].2,ax
	add si,2
	add di,4
	loop s
	
	
	mov ax,4c00H
	int 21H
	
cube:
	mov ax,bx
	mul bx
	mul bx
	ret
		
code ends

end start
