#include <stdio.h>
int mabs(int a, int *p) //此处应为一个空指针
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
    mabs(a, &b);        //不给b赋值，是一个空指针
    printf("%d\n", b);
    return 0;
}
