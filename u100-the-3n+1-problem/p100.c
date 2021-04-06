// 

#include <stdio.h>

int cycle(int a)
{
    int i = 1;

    while( a != 1 )
    {
        if( a % 2 == 0 ) {
            a = a/2;
        } else {
            a = 3*a+1;
        }
        i++;
    }
    return i;
}


int main()
{
    int a, b, max, temp;
    int aOrig, bOrig;
    int i;

    while( scanf("%d %d\n",&a,&b)==2 ) {

        aOrig = a;
        bOrig = b;

        if (a > b)
        {
            temp = a;
            a = b;
            b = temp;
        }

        max = cycle(a);
        for( i=a+1; i<=b; i++ )
        {
            temp = cycle(i);
            if(temp > max) {
                max = temp;
            }
        }
        printf("%d %d %d\n", aOrig, bOrig, max);
    }
    return 0;
}
