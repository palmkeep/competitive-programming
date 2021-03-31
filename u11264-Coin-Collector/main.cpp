#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

void getCoins(vector<int>& coins, const int num_coins)
{
    for (int coin = 0; coin < num_coins; coin++)
    {
        int c;
        cin >> c;
        coins.push_back(c);
    }
}

void testCase()
{
    int C;
    cin >> C;

    vector<int> coins;
    getCoins(coins, C);

    int longest_chain = 0;

    // for (int i = 0; i < C - longest_chain; i++)
    for (int i = 0; i < C-longest_chain; i++)
    {
        int chain_sum = 0;
        vector<int> chain;
        for (int j = i; j < C; j++)
        {
            /*
            if (j+1 == C)
            {
                if ( longest_chain < (int)chain.size() + 1 ) longest_chain = chain.size() + 1;
                cout << "End of coin list. Chain.size(): " << (int)chain.size() + 1 << endl; 
            }
            else if */
            if (chain_sum + coins[j] < coins[j+1] || j+1 == C)
            {
                chain_sum += coins[j];
                chain.push_back(coins[j]);
            }
        }
        if ( longest_chain < (int)chain.size() ) longest_chain = chain.size();
    }
    cout << longest_chain << endl;
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

