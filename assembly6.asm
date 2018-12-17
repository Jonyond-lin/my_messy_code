assume cs:code,ds:data,ss:stack,es:table

data segment
	db '197519761977197819791980198119821983198419851986198719881989199019911992199319941995'
	dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514
	dd 345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000
	dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037
	dw 5635,8226,11542,14430,15257,17800
data ends

table segment
	db 21 dup('year summ ne ?? ')	
table ends

stack segment stack
	db 128 dup(0)
stack ends

code segment

	start:
	mov ax,stack
	mov ss,ax
	mov sp,128
	
	mov ax,data		;where is the data come from?(the ds register)
	mov ds,ax
	
	mov ax,table	;and where is the data going?(the es register)
	mov es,ax
	
	;now,Let's set the si,di,bx register to separate the different data part
	mov si,0
	mov di,84
	mov bx,168
	mov bp,0
	
	mov cx,21
	
input:
	push ds:[si]
	pop es:[bp]
	push ds:[si+2]
	pop es:[bp+2]
	
	mov ax,ds:[di]
	mov dx,ds:[di+2]
	mov es:[bp+5],ax
	mov es:[bp+7],dx
	
	push ds:[bx]
	pop es:[bp+0aH]
	
	;div 
	div word ptr ds:[bx]
	
	mov es:[bp+0dH],ax
	
	add si,4
	add di,4
	add bx,2
	add bp,16
	loop input
	
	
	
	
	mov ax,4c00H
	int 21H
		
		
code ends

end start
