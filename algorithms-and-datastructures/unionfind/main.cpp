/*
 *  Author:      André Palmborg
 * 
 *  Course:      TDDD95
 *    Task:      1.4: Unionfind
 */


#include <stdio.h>      /* scanf, printf, puts */
#include <stdlib.h>     /* malloc, free */


/* DisjunctSets
 *
 * unsigned N       :   Total number of elements.
 * unsigned* nodes  :   Array keeping track of an elements parent in its set.
 *                      The root elements parent is: (unsigned)(-1).
 *
 * Datastructure that keeps track of a set number of elements and the set they
 * belong to.
 * An element can only belong to one set at a time.
 * Joining two elements together joins the two sets they belong to into one set.
 *
 */
struct DisjunctSets
{
    unsigned N;
    unsigned* nodes;

    // Constructor initializes all elements so that they belong to the set
    // containing only themselves.
    DisjunctSets(unsigned _N) : N(_N)
    {
        nodes = (unsigned*) malloc(N * sizeof(unsigned));
        for (unsigned i = 0; i < N; i++)
        {
            nodes[i] = (unsigned)(-1);
        }
    }
    ~DisjunctSets() { free(nodes); }

    // Returns the root element of a set.
    // Side effects:    Compresses the route to the root element by setting the
    //                  parent of all elements accessed while seeking the root
    //                  element to the root.
    unsigned get_root(unsigned n)
    {
        // If checking the root element -> return root
        if (nodes[n] == (unsigned)(-1))
            return n;
        else
        {
            unsigned it = get_root(nodes[n]);
            nodes[n] = it;
            return it;
        }
    }

    // Returns true iff two elements are in the same set.
    bool query_same(unsigned a, unsigned b)
    {
        if (a == b)
            return true;
        else
            return (get_root(a) == get_root(b));
    }

    // Places two elements and the elements in their respective sets in the same set.
    void join_sets(unsigned a, unsigned b)
    {
        unsigned a_root = get_root(a);
        unsigned b_root = get_root(b);
        if (a_root != b_root)
            nodes[b_root] = a_root;
    }
};


int main()
{
    unsigned N, Q;
    scanf("%d ", &N);   // Get number of elements.
    scanf("%d ", &Q);   // Get number of operations to be executed on the sets.
    DisjunctSets set(N);

    char op;
    unsigned a, b;
    bool same;
    for (unsigned i = 0; i < Q; i++)
    {
        scanf("%c %d %d ", &op, &a, &b);  // Get operation type and arguments
        //scanf("%d ", &a);   // Get arguments
        //scanf("%d ", &b);   // -||-
        switch (op)
        {
        case '?':   same = set.query_same(a, b);
                    (same) ? puts("yes") : puts("no");
                    break;
        case '=':   set.join_sets(a, b);
                    break;
        default:    throw "Bad argument";
        }
    }

    return 0;
}
