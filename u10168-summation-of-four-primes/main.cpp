#include <iostream>
#include <math.h>

using std::sqrt;
using std::cout;
using std::endl;
using std::cin;

int isPrime(int x)
{
    int s = sqrt(x);
    for (int i = 2; i <= s; i++)
    {
        if (x % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void GBSolve(int n, int& a, int& b)
{
    // Separate case: (2, n-2) for a better loop through the rest of the integers
    if (isPrime(n-2))
    {
        a = 2;
        b = n-2;
        return;
    }
    else
    {
        for (int i = 3; i < n; i = i+2)
        {
            if (isPrime(i) && isPrime(n-i))
            {
                a = i;
                b = n - i;
                return;
            }
        }
    }
}

int main()
{
    int n;
    while (cin >> n)
    {
        if (n <= 7)
        {
            cout << "Impossible." << endl;
        }
        else if (n % 2 != 0)
        {
            // n is odd
            int a, b;
            GBSolve(n-5, a, b);
            cout << "2 3 " << a << " " << b << endl;
        }
        else
        {
            // n is even
            int a, b;
            GBSolve(n-4, a, b);
            cout << "2 2 " << a << " " << b << endl;
        }
    }
    return 0;
}
