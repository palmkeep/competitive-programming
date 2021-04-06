#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cin;

void getIndex(vector<int>& ixs)
{
    string s;
    std::getline(cin, s);
    std::getline(cin, s);
    std::getline(cin, s);
    std::stringstream ss;
    ss << s;

    int n;
    while (ss >> n)
    {
        ixs.push_back(n);
    }

}
void getNumbers(vector<double>& num, const int N)
{
    for (int i = 0; i < N; i++)
    {
        double n;
        cin >> n;
        num.push_back(n);
    }
}

void testCase()
{
    vector<int> ixs;
    getIndex(ixs);

    vector<double> nl;
    getNumbers(nl, (int)ixs.size());


    double* out;
    out = (double*) malloc(sizeof(double) * (int)ixs.size());
    for (int i = 0; i < (int)ixs.size(); i++)
    {
        out[(int)ixs[i]-1] = nl[i];
    }

    for (int i = 0; i < (int)ixs.size(); i++)
    {
        cout << out[i] << endl;
    }
    cout << endl;
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

