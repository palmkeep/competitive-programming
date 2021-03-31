#include <stdio.h>
typedef long long unsigned llu;


bool isPrime(int n)
{
    if ( n == 2 || n == 3 )
        return true;
    else if ( n%2 == 0 || n%3 == 0)
        return false;

    long unsigned i=5, o=0, m=3;
    while ( n != 1 && 0 < n && i < n/m)
    {
        if ( n%i == 0 )
            return false;

        m = i;
        if ( i%6 == 5 ) {
            o++;
            i += 2;
        } else {
            i += 4;
        }
    }
    return true;
}

llu repMod(const llu a, const llu p)
{
    if (p == 0) return 1;

    llu e = p;
    llu rem = 1;

    llu c = a;

    while (1 <= e)
    {
        if (e % 2 == 1)
        {
            rem *= c;
            rem %= p;

            if (--e == 0) return rem;
        }

        c *= c;
        c %= p;

        e /= 2;
    }
    return rem;
}

void isBAPP(int a, int p)
{
    bool ans;
    if ( isPrime(p))
    {
        ans = false;
    }
    else
    {
        int rem = repMod(a, p);
        ans = (rem == a);
    }

    if (ans) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

}

int main()
{
    int p, a;
    while (1)
    {
        scanf("%d %d\n", &p, &a);
        if (p == 0 && a == 0) { break; } // EXIT condition

        // Calc.
        isBAPP(a, p);
    }
}
