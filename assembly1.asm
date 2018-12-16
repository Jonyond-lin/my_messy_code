assume cs:code

code segment

	mov bx,0	;mov dl,0
	mov ax,0020H
	mov ds,ax
	
	mov cx,64
	
	addnumber:	
		mov [bx],bl;dl
		inc bx
		;inc dl
		
	loop addnumber	;多用了两条指令
		
	mov ax,4c00H
	int 21H
		
		
code ends

end
