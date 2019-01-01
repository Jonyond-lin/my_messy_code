#include <stdio.h>
 
void find_two_largest(int a[], int m, int n, int *largest, int *second_largest)
{
    int i;

    *largest = a[m];
    *second_largest = a[m];
    for (i = m; i < n; ++i)
    {
        if (a[i] > *largest)
        {
            *second_largest = *largest;
            *largest = a[i];
        }
        else if (a[i] > *second_largest)
            *second_largest = a[i];
    }
}

int main()
{
    int up, i, m, n, largest, second_largest;
    int a[1005] = { 0 };
 
    scanf("%d", &up);
    for (i = 0; i < up; ++i)
        scanf("%d", &a[i]);
    scanf("%d%d",&m,&n);
    find_two_largest(a, m, n, &largest, &second_largest);
    printf("%d %d\n", largest, second_largest);
    return 0;
}
