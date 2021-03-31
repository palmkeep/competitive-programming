#include <iostream>
#include <math.h>
#include <vector>
#include <utility>

using std::vector;
using std::pair;
using std::cout;
using std::endl;
using std::cin;

void getBets(vector<int>& bets, const int num_bets)
{
    for (int i = 0; i < num_bets; i++)
    {
        int bet;
        cin >> bet;

        if (bets.empty())
        {
            bets.push_back(bet);
        }
        else if (0 < bet)
        {
            if (bets.back() <= 0)
            {
                bets.push_back(bet);
            }
            else if (0 < bets.back())
            {
                int back = bets.back();
                bets.pop_back();
                bets.push_back(back + bet);
            }
        }
        else if (bet <= 0)
        {
            if (bets.back() <= 0)
            {
                int back = bets.back();
                bets.pop_back();
                bets.push_back(back + bet);
            }
            else
            {
                bets.push_back(bet);
            }
        }
    }
}

int loop(vector<int>& bets, int streak, int i, int max)
{
    //cout << "i: " << i << " bet[i]: " << bets[i] << endl; 
    //cout << "bs: " << bets.size() << endl;

    if (i == (int)bets.size()) return max;
    
    if (0 < bets[i])
    {
        streak += bets[i];
        if (max < streak) max = streak;
        max = loop(bets, streak, i+1, max);
    }
    else if (0 < streak + bets[i])
    {
        if (max < streak) max = streak;
        max = loop(bets, streak + bets[i], i+1, max);
    }
    else
    {
        max = loop(bets, 0, i+1, max);
    }


    return max;
}


void testCase(const int N)
{
    vector<int> bets;
    getBets(bets, N);

    int largest_streak = 0;

    largest_streak = loop(bets, 0, 0, 0);

    if (largest_streak <= 0)
    {
        cout << "Losing streak." << endl;
    }
    else
    {
        cout << "The maximum winning streak is " << largest_streak << "." << endl;
    }
}

int main()
{
    int N;
    cin >> N;

    while (N != 0)
    {
        testCase(N);
        cin >> N;
    }

    return 0;
}

