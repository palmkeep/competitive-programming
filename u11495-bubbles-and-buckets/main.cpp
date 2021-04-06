#include <iostream>
#include <math.h>
#include <vector>
#include <utility>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

void getIntList(vector<int>& list, const int N)
{
    for (int i = 0; i < N; i++)
    {
        int n;
        cin >> n;
        list.push_back(n);
    }
}

void testCase(int N)
{
    vector<int> num_list;
    getIntList(num_list, N);

    int sum = 0;

    int i = 0;
    bool unsorted = true;
    while (unsorted)
    {
        if (i+1 == num_list[i])
        {
            i++;
        }
        else
        {
            int a = num_list[i];
            int b = num_list[num_list[i]-1];
            num_list[i] = b;
            num_list[a-1] = a;
            sum++;
        }
        if (i == N-1 && num_list[i] == i+1) break;
    }
    
    if (sum % 2 != 0)
    {
        cout << "Marcelo" << endl;
    }
    else
    {
        cout << "Carlos" << endl;
    }
}

int main()
{
    int N = -1;
    while(1)
    {
        cin >> N;
        if (N == 0) break;
        testCase(N);
    }

    return 0;
}

