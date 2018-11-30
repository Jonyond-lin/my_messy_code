#include<stdio.h> 
#include<string.h> 
#include <ctype.h> 

char *keyword[8]={"if","for","else","while","do","float","int","break"}; 
char keywordtable[20][20],re_keywordtable[20][20]; 
char digittable[20][20],re_digittable[20][20]; 
char otherchartable[20][20],re_otherchartable[20][20]; 
char idtable[20][20],re_idtable[20][20]; 
char notetable[20][20]; 
char finaltable[100][20]; 
int  finaltableint[100]; 
char word[20]; 
void initialize(); 
void alpha(); 
void digit(); 
void error(); 
void otherchar(); 
void note(); 
void print();
void prin(); 
void check(); 
void program(); 
void block(); 
void stmts(); 
void stmt(); 
void Bool(); 
void expr(); 
void expr1(); 
void term(); 
void term1(); 
void factor(); 
void match(char *t); 
 
int digit_num=0,keyword_num=0,otherchar_num=0,id_num=0,note_num=0;  
int redigit_num=1,rekeyword_num=1,reotherchar_num=1,reid_num=1;  
int final_num=0,finalnum=0; 
int flag_error=0; 
int flagerror=0; 
char lookahead; 
 
int main() 
{ 
	printf("请输入要分析的语句:\n"); 
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
				strcpy(finaltable[final_num],"/"); 
				strcpy(otherchartable[otherchar_num++],"/"); 
				finaltableint[final_num++]=2; 
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
	{ 
		printf("词法分析结果如下:\n"); 
		print(); 
		prin(); 
		program(); 
		if(finalnum==final_num) 
			printf("语法分析完成!\n"); 
	} 
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
	{ 
		strcpy(keywordtable[keyword_num++],word); 
		strcpy(finaltable[final_num],word); 
		if(strcmp(word,"if")==0) 
			finaltableint[final_num++]=100; 
		if(strcmp(word,"for")==0) 
			finaltableint[final_num++]=200; 
		if(strcmp(word,"else")==0) 
			finaltableint[final_num++]=300; 
		if(strcmp(word,"while")==0) 
			finaltableint[final_num++]=400; 
		if(strcmp(word,"do")==0) 
			finaltableint[final_num++]=500; 
		if(strcmp(word,"float")==0) 
			finaltableint[final_num++]=600; 
		if(strcmp(word,"int")==0) 
			finaltableint[final_num++]=700; 
		if(strcmp(word,"break")==0) 
			finaltableint[final_num++]=800; 
	} 
	else 
	{ 
		strcpy(idtable[id_num++],word); 
		strcpy(finaltable[final_num],"id"); 
		finaltableint[final_num++]=1; 
	} 
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
	{ 
		strcpy(idtable[id_num++],word); 
		strcpy(finaltable[final_num],"id"); 
		finaltableint[final_num++]=1; 
	} 
	else 
	{ 
		strcpy(digittable[digit_num++],word); 
		strcpy(finaltable[final_num],"num"); 
		finaltableint[final_num++]=99; 
	} 
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
		{ 
			strcpy(otherchartable[otherchar_num++],"!="); 
			strcpy(finaltable[final_num],"!="); 
			finaltableint[final_num++]=3; 
		} 
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
		{ 
			strcpy(otherchartable[otherchar_num++],"=="); 
			strcpy(finaltable[final_num],"=="); 
			finaltableint[final_num++]=4; 
		} 
		else { 
			strcpy(otherchartable[otherchar_num++],"="); 
			strcpy(finaltable[final_num],"="); 
			finaltableint[final_num++]=5; 
			ungetc(ch,stdin); 
		} 
	} 
	break; 
	case '(': 
		strcpy(otherchartable[otherchar_num++],"("); 
		strcpy(finaltable[final_num],"("); 
		finaltableint[final_num++]=6;                      // ( 6 
	break; 
	case ')': 
		strcpy(otherchartable[otherchar_num++],")"); 
		strcpy(finaltable[final_num],")"); 
		finaltableint[final_num++]=7;                      // ) 7 
	break; 
	case ';': 
		strcpy(otherchartable[otherchar_num++],";"); 
		strcpy(finaltable[final_num],";"); 
		finaltableint[final_num++]=8;      // ; 8 
	break; 
	case '{': 
		strcpy(otherchartable[otherchar_num++],"{"); 
		strcpy(finaltable[final_num],"{"); 
		finaltableint[final_num++]=9;      // { 9 
	break; 
	case '}': 
		strcpy(otherchartable[otherchar_num++],"}"); 
		strcpy(finaltable[final_num],"}"); 
		finaltableint[final_num++]=10;      // } 10 
	break; 
	case '||': 
		strcpy(otherchartable[otherchar_num++],"||"); 
		strcpy(finaltable[final_num],"||"); 
		finaltableint[final_num++]=11;      // || 11 
	break; 
	case '&&': 
		strcpy(otherchartable[otherchar_num++],"&&"); 
		strcpy(finaltable[final_num],"&&"); 
		finaltableint[final_num++]=12;      //&& 12 
	break; 
	case '+': 
		strcpy(otherchartable[otherchar_num++],"+"); 
		strcpy(finaltable[final_num],"+"); 
		finaltableint[final_num++]=13;      // + 13 
	break; 
	case '-': 
		strcpy(otherchartable[otherchar_num++],"-"); 
		strcpy(finaltable[final_num],"-"); 
		finaltableint[final_num++]=19;      // - 19 
	break; 
	case '>': 
	{ 
		ch=getchar(); 
		if(ch=='=') 
		{ 
			strcpy(otherchartable[otherchar_num++],">="); 
			strcpy(finaltable[final_num],">="); 
			finaltableint[final_num++]=14; 
		}            // >= 14 
		else 
		{ 
			strcpy(otherchartable[otherchar_num++],">"); 
			strcpy(finaltable[final_num],">"); 
			finaltableint[final_num++]=15;    // > 15 
			ungetc(ch,stdin); 
		} 
	} 
	break; 
	case '<':
	{ 
		ch=getchar(); 
		if(ch=='=') 
		{ 
			strcpy(otherchartable[otherchar_num++],"<="); 
			strcpy(finaltable[final_num],"<="); 
			finaltableint[final_num++]=16; 
		}            // <= 16 
		else 
		{ 
			strcpy(otherchartable[otherchar_num++],"<"); 
			strcpy(finaltable[final_num++],"<"); 
			finaltableint[final_num++]=17;    //< 17 
			ungetc(ch,stdin); 
		} 
	} 
	break; 
	case '*': 
		strcpy(finaltable[final_num],"*"); 
		finaltableint[final_num++]=18;      // * 18 
	break; 
	default: 
		error();break; 
	} 
} 
 
void error() 
{ 
	flag_error=1; 
	printf("出现错误,中止分析!\n"); 
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
			printf("%s\n",notetable[i]); 
	} 
	printf("词法分析完成!\n"); 
} 
 
void prin() 
{ 
	int i; 
	finaltableint[final_num]='\0'; 
	printf("语法分析结果如下：\n"); 
	for(i=0;i<final_num;i++) 
		printf("%s",finaltable[i]); 
	printf("\n语法分析过程如下:\n"); 
} 

 void program() 
{ 
	printf("program-->block\n"); 
	block(); 
	if(flagerror==1) 
	{ 
		error(); 
		return; 
	} 
}
 
 
void block() 
{ 
	if(flagerror==1) 
	{ 
		return; 
	} 

	printf("block-->{stmts}\n"); 
	match("{"); 
	stmts(); 
	match("}"); 
} 
 
void stmts() 
{ 
	if(flagerror==1) 
	{ 
		return; 
	} 
	if(finaltableint[finalnum]==10) 
	{ 
		printf("stmts-->null\n"); 
		return; 
	} 
	printf("stmts-->{stmt stmts}\n"); 
	stmt(); 
	stmts(); 
} 
 
void stmt() 
{ 
	if(flagerror==1) 
	{ 
		return;
	} 

	switch(finaltableint[finalnum]){ 
		case 1: 
			printf("stmt-->id=expr\n"); 
			match("id"); 
			match("="); 
			expr(); 
			match(";"); 
		break; 
		case 100: 
			match("if"); 
			match("("); 
			Bool(); 
			match(")"); 
			stmt(); 
			if(strcmp(finaltable[finalnum],"else")==0) 
			{ 
				printf("stmt-->if(bool) stmt else stmt\n"); 
				match("else"); 
				stmt(); 
				break; 
			} 
			else 
			{ 
				printf("stmt-->{if(bool) stmt\n"); 
				break; 
			} 
		case 400: 
			printf("stmt-->while(bool) stmt\n"); 
			match("while"); 
			match("("); 
			Bool(); 
			match(")"); 
			stmt(); 
		break; 
		case 500: 
			printf("stmt-->do stmt while(bool)\n"); 
			match("do"); 
			stmt(); 
			match("while"); 
			match("("); 
			Bool(); 
			match(")"); 
			match(";");
		break; 
		case 800: 
			printf("stmt-->break;\n"); 
			match("break"); 
			match(";"); 
			break; 
		default: 
			printf("stmt-->block\n"); 
			block(); 
		break; 
	} 
} 
 
void Bool() 
{ 
	if(flagerror==1) 
	{ 
		return; 
	} 
	expr(); 
	switch(finaltableint[finalnum]){ 
		case 17: 
			printf("bool-->expr<expr\n"); 
			match("<"); 
			expr(); 
		break; 
		case 16: 
			printf("bool-->expr<=expr\n"); 
			match("<="); 
			expr(); 
		break; 
		case 15: 
			printf("bool-->expr>expr\n"); 
			match(">"); 
			expr(); 
		break; 
		case 14: 
			printf("bool-->expr>=expr\n"); 
			match(">="); 
			expr(); 
		break; 
		default: 
			printf("bool-->expr\n"); 
			expr();
		break; 
	} 
} 
 
void expr() 
{ 
	if(flagerror==1) 
	{ 
		return; 
	} 
	printf("expr-->term expr1\n"); 
	term(); 
	expr1(); 
} 
 
void expr1() 
{ 
	if(flagerror==1) 
	{ 
		return; 
	} 
	switch(finaltableint[finalnum]){ 
		case 13: 
			printf("expr1-->+term expr1\n"); 
			match("+"); 
			term(); 
			expr1(); 
		break; 
		case 19: 
			printf("expr1-->-term expr1\n"); 
			match("-"); 
			term(); 
			expr1(); 
		break; 
		default: 
			printf("expr1-->null\n"); 
		return; 
	} 
} 
 
void term() 
{ 
	if(flagerror==1) 
	{
		return; 
	} 
	printf("term-->factor term1\n"); 
	factor(); 
	term1(); 
} 
 
void term1() 
{ 
	if(flagerror==1) 
	{ 
		return; 
	} 
	switch(finaltableint[finalnum]){ 
		case 18: 
			printf("term1-->*factor term1\n"); 
			match("*"); 
			factor(); 
			term1(); 
		break; 
		case 2: 
			printf("term1-->/factor term1\n"); 
			match("/"); 
			factor(); 
			term1(); 
		break; 
		default: 
			printf("term1-->null\n"); 
		return; 
	} 
} 
 
void factor() 
{ 
	if(flagerror==1) 
	{ 
		return; 
	} 
	switch(finaltableint[finalnum]){ 
		case 6: 
			printf("fatcor-->(expr)\n"); 
			match("("); 
			expr(); 
			match(")");
		break; 
		case 1: 
			printf("factor-->id\n"); 
			match("id"); 
		break; 
		case 99: 
			printf("factor-->num\n"); 
			match("num"); 
		break; 
		default: 
			flagerror=1; 
		break; 
	} 
} 
 
void match(char *t) 
{ 
	if(strcmp(finaltable[finalnum],t)!=0) 
	{
		flagerror=1; 
		return; 
	} 
	finalnum++; 
} 
