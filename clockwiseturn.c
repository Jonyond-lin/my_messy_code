#include<stdio.h>
#include<string.h>
int main()
{
	int a[3][3];
	int i,j;
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			scanf("%d",&a[i][j]);
		}
	}
	for (i = 0; i < 3; ++i)
	{
		for (j = 2; j >=0; --j)
		{
			printf("%d ", a[j][i]);
		}
		printf("\n");
	}
	
	return 0;
}
