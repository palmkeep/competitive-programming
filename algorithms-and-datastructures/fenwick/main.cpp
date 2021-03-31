/*
 *  Author:      André Palmborg
 * 
 *  Course:      TDDD95
 *    Task:      1.5: Fenwick
 */

#include <stdio.h>
#include <stdlib.h>



// Fenwick Tree
//
// Stores partial cumulative sums of a value array in a binary indexed tree:
//
// 0
// |---------------8
// |-------4       |---------12
// |---2   |---6   |---10    |-----14
// |-1 |-3 |-5 |-7 |-9 |--11 |--13 |--15
//
// Position 8 stores the sum from 0 to 8.
// So to calculate the sum from 0 to 13 only the partial sums at 
// position 8, 12 and 13 need to be accessed.
template<typename T>
struct Fenwick_Tree
{
    T* tree;
    size_t size;
    Fenwick_Tree(size_t N)
    {
        tree = (T*) malloc(N * sizeof(T));
        size = N;
        for (size_t i = 0; i < size; i++)
        {
            tree[i] = 0;
        }
    };
    ~Fenwick_Tree()
    {
        delete[] tree;
    };


    // Add &d to hypothetical value array at index &i
    void add(long int i, T d)
    {
        while (i <= (long int)size)
        {
            tree[i] += d;
            if (i == 0)
                i++;
            else
                i += ((i) & -(i)); // Add least sig. bit
        }
    };

    // Base sum function
    T _sum(long int i)
    {
        T sum = 0;
        while (i > 0)
        {
            sum += tree[i];
            i -= ((i) & -(i)); // Remove least sig. bit
        }
        return sum;
    };

    // Sums the range [l,r]
    T sumRange(long int l, long int r)
    {
        return _sum(r) - _sum(l-1);
    };

    // Sums the range [0,r) non inclusive on right side
    T sumUpTo(long int i)
    {
        if (i == 0)
            return 0;
        else if (i == 1)
            return tree[0];
        else
            return _sum(i-1);
    };

    // Debug for prints
    T get(size_t i)
    {
        return tree[i];
    };
};



int main()
{
    unsigned N, Q;
    scanf("%u %u ", &N, &Q);
    Fenwick_Tree<long int> t(N);

    char op;
    unsigned i;
    long int d, s;
    while (0 < Q--)
    {
        scanf("%c ", &op);
        if (op == '+')
        {
            scanf("%u %ld ", &i, &d);
            t.add(i, d);
        }
        else if (op == '?')
        {
            scanf("%u ", &i);
            s = t.sumUpTo(i);
            printf("%ld\n", s);
        }
        else
            puts("Throws exception... Lazily");
    }
}
