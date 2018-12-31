#include <stdio.h>
int mabs(int a, int *p)
{
    if(!p)return -1;
    if(a>0)*p=a;
    else *p=-a;
    return 0;
}
int main()
{
    int a, b;
    scanf("%d", &a);
    mabs(a, &b);
    printf("%d\n", b);
    return 0;
}
