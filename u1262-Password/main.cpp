#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
#include <string>
#include <string.h>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::string;


void getGrid(vector<vector<string>>& g )
{
    int rows = 6;
    int cols = 5;

    for (int i = 0; i < rows; i++)
    {
        vector<string> row;
        g.push_back(row);
    }

    for (int i = 0; i < rows; i++)
    {
        string s;
        std::getline(cin, s);
        for (int j = 0; j < cols; j++)
        {
            string c = "";
            c += s[j];
            g[j].push_back(c);
        }
    }

    for (int i = 0; i < rows; i++)
    {
        std::sort(g[i].begin(), g[i].end());
    }

}

void getCommon(const vector<vector<string>>& a, const vector<vector<string>>& b, vector<vector<string>>& f)
{

    for (int i = 0; i < 5; i++)
    {
        vector<string> col;
        f.push_back(col);

        vector<string>::const_iterator it_a = a[i].begin();
        vector<string>::const_iterator it_b = b[i].begin();

        while (it_a != a[i].end() && it_b != b[i].end())
        {
            if (it_a != a[i].begin() && *it_a == *(it_a-1) )
            {
                it_a++;
            }
            else if ( *it_a == *it_b )
            {
                string c = "";
                c += *it_a;
                f[i].push_back(c);
                it_a++;
                it_b++;
            }
            else if ( *it_a < *it_b )
            {
                it_a++;
            }
            else
            {
                it_b++;
            }
        }
    }
}

void printSol(const int K, const vector<vector<string>>& g, const int tot, const vector<int>& prd_cmb)
{

    /*
    cout << "Entering PRINTSOL" << endl;

    for (int i = 0; i < (int)g.size(); i++)
    {
        for (int j = 0; j < (int)g[i].size(); j++)
        {
            cout << g[i][j];
        }
        cout << endl;
    }
    cout << endl;

    cout << "Tot: " << tot << endl;
    cout << "K: " << K << endl;
    */

    int rem = K - 1;

    vector<int> removed;
    for (int k = 0; k < 5; k++)
    {
        int q = 0;
        removed.push_back(q);
    }

    if (tot < K || tot == 0)
    {
        cout << "NO" << endl;
    }
    else
    {
        int i = 0;
        while (rem != 0)
        {
            if (rem < prd_cmb[i])
            {
                i++;
            }
            else
            {
                rem -= prd_cmb[i];
                removed[i] += 1;
                i = 0;
            }
        }
        for (int i = 0; i < 5; i++)
        {
            /*
            cout << endl << "i: " << i << endl;
            cout << "rem[i]: " << removed[i] << endl;
            cout << "print" << endl;
            */

            cout << g[i][removed[i]];
        }

        cout << endl;
    }
//    cout << "Exiting PRINTSOL" << endl;
}

void testCase()
{
    int K;
    cin >> K;

    string s;
    std::getline(cin,s); //Throw away rest of line so getGrid is not confused

    vector<vector<string>> g1;
    getGrid(g1);
    vector<vector<string>> g2;
    getGrid(g2);

    vector<vector<string>> g3;
    getCommon(g1, g2, g3);

    if (g3.size() != 0)
    {
        vector<int> num_e;
        vector<int> comb_e;
        for (int i = 0; i < 5; i++)
        {
            num_e.push_back(g3[i].size());
        }

        int combs = 1;
        for (int i = 4; 0 < i; i--)
        {
            combs *= num_e[i];

            vector<int>::iterator it;
            it = comb_e.begin();
            comb_e.insert(it, combs);
        }
        comb_e.push_back(1);
        combs *= num_e[0];

        for (int i = 0; i < (int)g3.size(); i++)
        {
            if (g3[i].size() <= 0)
            {
                cout << "NO" << endl;
                return;
            }
        }
        printSol(K, g3, combs, comb_e);
    }
    else
    {
        cout << "NO" << endl;
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
//    cout << endl;

    return 0;
}

