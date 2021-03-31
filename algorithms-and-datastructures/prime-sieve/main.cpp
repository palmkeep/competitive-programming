/*
 *  Author:      André Palmborg
 *  LiU ID:      andpa149
 * 
 *  Course:      TDDD95
 *    Task:      3.8: primesieve
 */

#include <stdio.h>
#include <math.h>
#include <vector>
using std::vector;



/* Sieve of Eratosthenes
 *
 * Generates primes within a fixed span by successively marking of composite
 * numbers divisible by primes. Starting marking from smallest prime leaves
 * the next smallest prime unmarked in the vector.
 *
 * O( exp(N) )  time complexity
 * O( N )       memory
 */

void eratosthenes_sieve(vector<bool>& primes, int N)
{
    int i=2;
    int j;
    while( true )
    {
        if( primes[i] == true && i*2 <= N )
        {
            j = 2;
            while( i*j <= N )
            {
                primes[ i*j ] = false;
                j++;
            }
        }
        if( ++i == N ) break;
    }
    primes[0] = false;
    primes[1] = false;
}

/* is_prime
 *
 * Returns wheter a given int n is prime.
 * Utilizes wheel factorization with wheel size=6.
 *
 * O( n )  time complexity
 * O( 1 )       memory
 */
bool is_prime(int n)
{
    if( n == 2 || n == 3 )
        return true;
    else if( n%2 == 0 || n%3 == 0)
        return false;

    long unsigned i=5, o=0, m=3;
    while( n != 1 && 0 < n && i < n/m)
    {
        if( n%i == 0 )
            return false;
        
        m = i;
        if( i%6 == 5 )
        {
            o++;
            i += 2;
        }
        else
        { i += 4; }
    }
    return true;
}


/*
 *
 */
int main()
{
    int N, q;
    scanf("%d ", &N);
    N += 1;
    vector<bool> primes(N, true);
    eratosthenes_sieve(primes, N);

    // Count primes
    int nPrimes = 0;
    int i=0;
    while( true )
    {
        if( primes[i] == true ) nPrimes++;
        if( ++i == N ) break;
    }
    printf("%d\n", nPrimes);

    // Handle queries
    scanf("%d ", &q);
    int query;
    while( 0 < q-- )
    {
        scanf("%d ", &query);
        if (primes[query] == false )
            puts("0");      // Not a prime
        else
            puts("1");      // Is a prime
    }
}
