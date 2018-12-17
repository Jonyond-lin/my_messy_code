assume cs:code,ds:data,ss:stack

data segment
	
data ends

table segment
	
table ends

stack segment stack
	
stack ends

code segment

	start:
	mov ax,2000h
	mov ds,ax		
	mov bx,0
	s:
	mov cl,[bx]		;use the jcxz command to solve the problem
	mov ch,0
	jcxz ok			
	inc bx			;if the byte is not 0,then jump to the next unit
	loop s
	ok:
	dec bx		
	mov dx,bx
	
	
	mov ax,4c00H
	int 21H
		
		
code ends

end start
