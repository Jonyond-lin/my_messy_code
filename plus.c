#include <stdio.h>
#include <string.h>
int main()
{    
	int i,j,k,n,t,a1,b1;    
	char a[10001],b[10001];    
	int aa[100001],bb[10001];      
	for (t=1;t<=2;t++)          
	{              
		memset(a,0,sizeof(a));              
		memset(b,0,sizeof(b));              
		memset(aa,0,sizeof(aa));              
		memset(bb,0,sizeof(bb));              
		scanf("%s%s",a,b);              
		a1=strlen(a);              
		b1=strlen(b);              
		if (a1>b1) 
			k=a1;              
		else 
			k=b1;              
		j=k;              
		for (i=a1-1;i>=0;i--)              
		{                  
			aa[j]=a[i]-'0';                  
			j--;              
		}              
		j=k;              
		for (i=b1-1;i>=0;i--)              
		{                  
			bb[j]=b[i]-'0';                  
			j--;              
		}              
		for (i=k;i>=0;i--)              
		{                  
			bb[i]+=aa[i];                  
			if (bb[i]>=10) 
			{
				bb[i]-=10;
				bb[i-1]++;
			}              
		}                           
		printf("%s + %s = ",a,b);              
		if (bb[0]==0)
		{
			for (i=1;i<=k;i++) 
				printf("%d",bb[i]);              
		}
		else{
			for (i=0;i<=k;i++) 
				printf("%d",bb[i]);              
			if (t<n) 
				printf("\n\n");              
			else 
				printf("\n");
		}
	}
	return 0;
}
