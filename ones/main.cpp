#include <cstdio>
#include <cstdint>
#include <cassert>

int main()
{
    uint64_t N;
    while (scanf("%lu\n", &N) != EOF)
    {
        uint64_t cmp = 1;
        unsigned cmp_i = 1;
        for (; cmp % N != 0 ;)
        {
            /*
             *   11 = d+r
             *  111 mod d === (d+r)*10 + 1 mod d === r10 + 1 mod d
             */
            cmp = (cmp % N) * 10 + 1;

            ++cmp_i;
        }
        printf("%u\n", cmp_i);
    }
}
