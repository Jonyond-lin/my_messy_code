assume cs:code,ds:data

data segment
	db 'BasIc'
	db 'iNfoRmAtion'
data ends

code segment

	
	start:
	mov ax,data
	mov ds,ax
	mov bx,0
	mov cx,5
	s:
	mov al,[bx]
	and al,11011111B
	mov [bx],al		;写回原单元
	inc bx
	loop s 
	mov bx,5
	mov cx,11
	s0:
	mov al,[bx]
	and al,11011111B
	mov [bx],al		;写回原单元
	inc bx
	loop s0 
	mov ax,4c00H
	int 21H
		
		
code ends

end start
