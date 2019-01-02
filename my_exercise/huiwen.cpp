#include<stdio.h>
#include<string.h>
#include<ctype.h>
 
int main()
{
	char c, a[100];
	int i = 0, n;
	
	while ((c = getchar()) != '\n'){
		
		if(toupper(c) >= 'A'&&toupper(c) <= 'Z'){
 			a[i++] = toupper(c); 
		}
		
    }
    
	a[i] = '\0';
		
	for (n = 0, --i; i >= 0; i--, n++ ){
		
		
		if(a[i] != a[n]){ 
		
		   printf("不是回文哦\n");
		   break;
		   
		} else if (i == 0){
			
		   printf("是回文哦\n");
		   
		}
		
	
    }
	return 0;
 } 
