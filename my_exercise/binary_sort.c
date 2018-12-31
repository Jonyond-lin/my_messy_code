#include <stdio.h>
#include <iostream>
using namespace std;

void sort(int array[],int n)
{
	int i,j,k,t;
	for (i = 0; i < n-1; ++i)
	{
		k=i;
		for (j = i+1; j < n; ++j)
		{
			if (array[j]<array[k])
			{
				k=j;
			}
		}
		t=array[i];
		array[i]=array[k];
		array[k]=t;
	}	
}

//recurve
int recurbinary(int *a, int key, int low, int high)
{
    int mid,tmp;
    if(low > high)
    {
        return -1;
    }else{
    	mid = (low + high)/2;
	    if(a[mid] == key) return mid;
	    else if(a[mid] > key)
	         return recurbinary(a,key,low,mid -1);
	    else
	         return recurbinary(a,key,mid + 1,high);
    }
}
//non-recurve
int binary( int *a, int key, int n )
{
    int left = 0, right = n - 1, mid = 0;
    mid = ( left + right ) / 2;
    while( left < right && a[mid] != key )
    {
        if( a[mid] < key ) {
            left = mid + 1;
        } else if( a[mid] > key ) {
            right = mid - 1;
        }
        mid = ( left + right ) / 2;
    }
    if( a[mid] == key )
        return mid;
    return -1;
}

int main()
{
	int n,m;
	int a[10001];
	int i,k;
	scanf("%d%d",&n,&m);
	for (i = 0; i < n; ++i)
	{
		scanf("%d",&a[i]);
	}
	sort(a,n);
	k = recurbinary(a,m,a[0],a[n-1]);
	//k = binary(a,m,n);  //recurve
	if(k == -1){
		printf("NOT FOUND!\n");
	}else{
		printf("%d is the %dth number in the array\n",a[k],k+1);
	}
	return 0;
}
