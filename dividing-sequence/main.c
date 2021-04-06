#include <stdio.h>

int main()
{
    int N;
    scanf("%d\n", &N);

    int m = 0;
    int c = 1;
    do {
        ++m;
        c *= 2;
    } while (c*2 <= N);

    printf("%d\n", m+1);
    printf("1");
    c = 1;
    while (0 < m--) {
        c *= 2;
        printf(" %d", c);
    }
    printf("\n");
}
