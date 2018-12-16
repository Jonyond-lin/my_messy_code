assume cs:code

code segment

	dw 0123H,0456H,0789H,0ABCH,0DEFH,0fedH,0cbaH,0987H
	dw 0,0,0,0,0,0,0,0
	;用dw定义8个字型数据，在程序加载后，讲取得8个字的内存空间
	;然后再申请8个内存空间，用作堆栈，以此来实现逆转
	
	start:
		mov ax,cs
		mov ss,ax
		mov sp,32
		mov bx,0
		mov cx,8
		
		s:
			push cs:[bx]
			add bx,2
		loop s 
			
		mov bx,0
		mov cx,8
			
		s1:
			pop cs:[bx]
			add bx,2
		loop s1			
		
	mov ax,4c00H
	int 21H
		
		
code ends

end start
