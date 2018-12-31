#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
const unsigned int MAX_OK_RAND = (RAND_MAX/6)*6-1;
int throw_die(){
	static int flag = 0;
	int value;
	if (!flag)
	{
		flag = 1;
		srand((unsigned int)time(NULL));
	}
	while((value = rand())>MAX_OK_RAND);
	return value%6+1;
}

void define_prize(int a[])
{
	int cnt_4,cnt_2,cnt_3,cnt_1,cnt_5,cnt_6;
	int i;
	for (i = 0; i < 6; ++i)
	{
		switch(a[i])
		{
			case 1:cnt_1++;break;
			case 2:cnt_2++;break;
			case 3:cnt_3++;break;
			case 4:cnt_4++;break;
			case 5:cnt_5++;break;
			case 6:cnt_6++;break;
		}	
	}
	if (cnt_4>=4)
	{
		printf("champion!\n");
	}else if (cnt_4==3)
	{
		printf("the three red!\n");
	}else if (cnt_2==4)
	{
		printf("four in!\n");printf("the two lift!\n");
	}else if (cnt_4==2)
	{
		printf("the two lift!\n");
	}else if (cnt_1==1&&cnt_2==1&&cnt_3==1&&cnt_4==1&&cnt_5==1&&cnt_6==1)
	{
		printf("Second place!\n");
	}else if (cnt_4==1)
	{
		printf("one excellent!\n");
	}else{
		printf("none!\n");
	}
	
}

int main(){
	int a[100];
	//int v = MAX_OK_RAND;
	int i = -1;
	while(++i<6){
		a[i] = throw_die();
		printf("%d\n", a[i]);
	}
	define_prize(a);

	return EXIT_SUCCESS;
}
 
