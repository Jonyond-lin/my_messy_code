#include<ctype.h>
#include<stdio.h>
int lookahead;
void expr();
void term();
void match(int t);
int error();
int lexan();
  
 
void factor();
void main()
{
	lookahead=getchar();
	expr();
	putchar('\n');
}
void expr()
{
	term();
	while(1)
	{
		if(lookahead=='+')
		{
			match('+');
			term();
			putchar('+');
		}
		else if(lookahead=='-'){
			match('-');
			term();
			putchar('-');
		}
		else if(lookahead==')')
		{
			break;
		}
		else 
			break;
	}
}
void term()
{
	factor();
	if(isdigit(lookahead))
	{
		lookahead=lexan();
		printf("%d",lookahead);
		match(lookahead);
	}
	else if(isalpha(lookahead))
	{
		putchar(lookahead);
		lookahead=getchar();
		term();
	}
	else if(lookahead=='*')
	{
		match('*');
		term();
		putchar('*');
	}
	else if(lookahead=='/')
	{
		match('/');
		term();
		putchar('/');
	}
}
void factor()
{
	if(isdigit(lookahead))
	{
		lookahead=lexan();
		printf("%d",lookahead);
		match(lookahead);
	}
	else if(isalpha(lookahead))
	{
		putchar(lookahead);
		lookahead=getchar();
		factor();
	}
	else if(lookahead=='(')
	{
		match('(');
		expr();
		match(')');
	}
	else
		error();
}
void match(int t)
{
	if(lookahead==t)
	lookahead=getchar();
	else error();
}
int error()
{
	printf("syntaxerror\n");
	return 0;
}
int lexan()
{
	int tokenval=0;
	int ch;
	while(1){
		ch=lookahead;
		if(isdigit(ch))
		{
			tokenval=ch-'0';
			ch=getchar();
			while(isdigit(ch))
			{
				tokenval=tokenval*10+ch-'0';
				ch=getchar();
			}
			ungetc(ch,stdin);
			return tokenval;
		}
	}
}
