#include <iostream>
#include <math.h>
#include <vector>
#include <utility>

using std::vector;
using std::cout;
using std::endl;
using std::cin;


void testCase()
{
    int s, d;
    cin >> s;
    cin >> d;

    if (s < d)
    {
        cout << "impossible" << endl;
    }
    else
    {
        int a,b;
        a = d + ((s-d)/2);
        b = (s-d)/2;
        int diff = a-b;
        if (diff < 0) diff = -diff;

        if (a + b == s && diff == d)
        {
            cout << a << " " << b << endl;
        }
        else
        {
            cout << "impossible" << endl;
        }
    }
}

int main()
{
    int nTests;
    cin >> nTests;

    for (int tI = 0; tI < nTests; tI++)
    {
        testCase();
    }

    return 0;
}

