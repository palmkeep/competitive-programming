#include <iostream>
#include <math.h>
#include <vector>
#include <utility>

using std::vector;
using std::pair;
using std::cout;
using std::endl;
using std::cin;

using std::ceil;
using std::pow;
using std::sqrt;

void getPoly(vector<int>& poly, const int degree)
{
    for (int i = 0; i <= degree; i++)
    {
        int c;
        cin >> c;
        poly.push_back(c);
    }
}

void testCase()
{
    int degree;
    cin >> degree;
    
    vector<int> poly;
    getPoly(poly, degree);

    float d, k;
    cin >> d;
    cin >> k;

    float kv = k/d;
    kv = ceil(kv);
    float n = -0.5 + sqrt(0.25 + 2*kv);
    n = std::ceil(n);

    //cout << "n: " << n << endl;
    long long sum = poly[0];
    for (int i = 1; i <= degree; i++)
    {
        if (poly[i] != 0)
        {
            sum += poly[i] * pow(n,i);
        }
    }
    cout << sum << endl;

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

