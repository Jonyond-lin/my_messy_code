#include<stdio.h> 
#include<string.h> 
#include <ctype.h> 
 
char *keyword[8]={"if","for","else","while","do","float","int","break"}; 
char keywordtable[20][20],re_keywordtable[20][20]; 
char digittable[20][20],re_digittable[20][20]; 
char otherchartable[20][20],re_otherchartable[20][20]; 
char idtable[20][20],re_idtable[20][20]; 
char notetable[20][20]; 
char word[20]; 
void initialize(); 
void alpha(); 
void digit(); 
void error(); 
void otherchar(); 
void print(); 
void check(); 
void note(); 
 
int digit_num=0,keyword_num=0,otherchar_num=0,id_num=0,note_num=0;  
int redigit_num=1,rekeyword_num=1,reotherchar_num=1,reid_num=1;  
int flag_error=0; 
char lookahead;
void main() 
{ 
	printf("请输入要分析的语句：\n"); 
	initialize(); 
	lookahead=getchar(); 
	while(1) 
	{ 

		if(isalpha(lookahead)) 
		{ 
			alpha(); 
			initialize(); 
		} 
		else if(isdigit(lookahead)) 
		{ 
			digit(); 
			initialize(); 
		} 
		else if(lookahead=='\t'||lookahead==' ') 
		{ 
			; 
		} 
		else if(lookahead=='\n') 
			break; 
		else if(lookahead=='/') 
		{ 
			lookahead=getchar(); 
			if(lookahead=='*') 
			{ 
				note(); 
				initialize(); 
			} 
			else 
			{ 
				ungetc(lookahead,stdin); 
				strcpy(otherchartable[otherchar_num++],"/"); 
				initialize(); 
			} 
		} 
		else 
		{ 
			otherchar(); 
			initialize(); 
		} 
		lookahead=getchar(); 
	} 
	check(); 
	if(flag_error==0) 
		print(); 
} 
 
 
void alpha() 
{ 
	int i=1,flag; 
	char ch; 
	ch=lookahead; 
	word[0]=ch; 
	ch=getchar(); 
	while(isalpha(ch)||isdigit(ch)) 
	{ 
		word[i++]=ch; 
		ch=getchar(); 
	} 
	ungetc(ch,stdin); 
	flag=0; 
	for(i=0;i<8;i++) 
	{ 
		if(strcmp(word,keyword[i])==0) 
		flag=1;  
	} 
	if(flag==1) 
		strcpy(keywordtable[keyword_num++],word); 
	else 
		strcpy(idtable[id_num++],word); 
} 
 
void digit() 
{ 
	int i=1,flag; 
	char ch; 
	ch=lookahead;
	word[0]=ch; 
	ch=getchar(); 
	while(isalpha(ch)||isdigit(ch)) 
	{ 
		word[i++]=ch; 
		ch=getchar(); 
	} 
	ungetc(ch,stdin); 
	flag=0; 
	for(i=0;word[i]!='\0';i++) 
	{ 
		if(word[i]<'0'||word[i]>'9') 
		flag=1; 
	} 
	if(flag==1) 
		strcpy(idtable[id_num++],word); 
	else 
		strcpy(digittable[digit_num++],word); 
} 
 
void otherchar() 
{ 
	char ch; 
	ch=lookahead; 
	switch(ch){ 
		case '!': 
		{ 
			ch=getchar(); 
			if(ch=='=') 
				strcpy(otherchartable[otherchar_num++],"!="); 
			else 
			{ 
				ungetc(ch,stdin); 
				error(); 
			} 
		} 
		break; 
		case '=': 
		{ 
			ch=getchar(); 
			if(ch=='=')
				strcpy(otherchartable[otherchar_num++],"=="); 
			else 
			{ 
				strcpy(otherchartable[otherchar_num++],"="); 
				ungetc(ch,stdin); 
			} 
		} 
		break; 
		case '(': 
			strcpy(otherchartable[otherchar_num++],"(");break; 
		case ')': 
			strcpy(otherchartable[otherchar_num++],")");break; 
		case ';': 
			strcpy(otherchartable[otherchar_num++],";");break; 
		case '{': 
			strcpy(otherchartable[otherchar_num++],"{");break; 
		case '}': 
			strcpy(otherchartable[otherchar_num++],"}");break; 
		case '||': 
			strcpy(otherchartable[otherchar_num++],"||");break; 
		case '&&': 
			strcpy(otherchartable[otherchar_num++],"&&");break; 
		case '+': 
			strcpy(otherchartable[otherchar_num++],"+");break; 
		case '>': 
		{ 
			ch=getchar(); 
			if(ch=='=') 
				strcpy(otherchartable[otherchar_num++],">="); 
			else 
			{ 
				strcpy(otherchartable[otherchar_num++],">"); 
				ungetc(ch,stdin); 
			} 
		} 
		break; 
		case '<': 
		{ 
			ch=getchar(); 
			if(ch=='=') 
				strcpy(otherchartable[otherchar_num++],"<=");
			else 
			{ 
				strcpy(otherchartable[otherchar_num++],"<"); 
				ungetc(ch,stdin); 
			} 
		} 
		break; 
		default: 
			error();break; 
	} 
} 
 
void error() 
{ 
	flag_error=1; 
	printf("输入有误!\n"); 
} 
 
   
void initialize() 
{ 
	int i; 
	for(i=0;i<20;i++) 
	{ 
		word[i]='\0'; 
	} 
} 
 
void check() 
{ 
	int i,j,flag; 
	strcpy(re_keywordtable[0],keywordtable[0]); 
	for(i=1;i<keyword_num;i++) 
	{ 
		flag=0; 
		for(j=0;j<rekeyword_num;j++) 
		{ 
			if(strcmp(keywordtable[i],re_keywordtable[j])==0) 
			{ 
				flag=1; 
				break;
			} 
		} 
		if(flag==0) 
			strcpy(re_keywordtable[rekeyword_num++],keywordtable[i]); 
	} 

	strcpy(re_digittable[0],digittable[0]); 
	for(i=1;i<digit_num;i++) 
	{ 
		flag=0; 
		for(j=0;j<redigit_num;j++) 
		{ 
			if(strcmp(digittable[i],re_digittable[j])==0) 
			{ 
				flag=1; 
				break; 
			} 
		} 

		if(flag==0) 
			strcpy(re_digittable[redigit_num++],digittable[i]); 
	} 

	strcpy(re_otherchartable[0],otherchartable[0]); 
	for(i=1;i<otherchar_num;i++) 
	{ 
		flag=0; 
		for(j=0;j<reotherchar_num;j++) 
		{ 
			if(strcmp(otherchartable[i],re_otherchartable[j])==0) 
			{ 
				flag=1; 
				break; 
			} 
		} 
		if(flag==0) 
			strcpy(re_otherchartable[reotherchar_num++],otherchartable[i]); 
	} 

	strcpy(re_idtable[0],idtable[0]);
	for(i=1;i<id_num;i++) 
	{ 
		flag=0; 
		for(j=0;j<reid_num;j++) 
		{ 
			if(strcmp(idtable[i],re_idtable[j])==0) 
			{ 
				flag=1; 
				break; 
			} 
		} 
		if(flag==0) 
			strcpy(re_idtable[reid_num++],idtable[i]); 
	} 
} 
 
void note() 
{ 
	char ch; 
	int i=0; 
	ch=getchar(); 
	while(1) 
	{ 
		if(ch=='*') 
		{ 
			ch=getchar(); 
			if(ch=='/') 
				break; 
			else 
			{ 
				ungetc(ch,stdin); 
				word[i++]=ch; 
			} 
		} 
		else 
		{ 
			word[i++]=ch; 
		} 
		ch=getchar(); 
	} 
	strcpy(notetable[note_num++],word);
} 
 
 
 
void print() 
{ 
	int i; 
	//printf("Keywords:\n"); 
	if(keyword_num!=0) 
		for(i=0;i<rekeyword_num;i++) 
			printf("< %s, >\n",re_keywordtable[i]); 
	//printf("\nDigits:\n"); 
	if(digit_num!=0) 
		for(i=0;i<redigit_num;i++) 
			printf("< number,%s >\n",re_digittable[i]); 
	//printf("\nOtherchars:\n"); 
	if(otherchar_num!=0) 
		for(i=0;i<reotherchar_num;i++) 
			printf("< comparison,%s >\n",re_otherchartable[i]); 
	//printf("\nId:\n"); 
	if(id_num!=0) 
		for(i=0;i<reid_num;i++) 
			printf("< id,%s >\n",re_idtable[i]); 
	if(note_num!=0) 
	{ 
		printf("注释:\n"); 
		for(i=0;i<note_num;i++) 
			printf("%s  ",notetable[i]); 
	} 
	printf("\n词法分析完成!\n"); 
} 
