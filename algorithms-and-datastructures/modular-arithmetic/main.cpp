#include <stdexcept>
#include <stdio.h>

#define ll long long int


inline void add(ll lhs, ll rhs, ll n)
{
    ll out = lhs+rhs;
    if( out < 0 )
        out += n;
    printf("%lld\n", (lhs+rhs)%n);
}
inline void sub(ll lhs, ll rhs, ll n)
{
    ll out = lhs-rhs;
    while( out < 0 )
        out += n;
    printf("%lld\n", out%n);
}
inline void mul(ll lhs, ll rhs, ll n)
{
    //if (lhs < 0 || rhs < 0) throw std::invalid_argument("BAD");
    ll out = lhs*rhs;
    while( out < 0 )
        out += n;
    printf("%lld\n", out%n);
}

bool extEuclid(ll m, ll n, ll &a, ll &b)
{
    ll a1 = 1;
    ll b1 = 0;
    a = 0;
    b = 1;

    ll c = m;
    ll d = n;
    ll q;
    ll r;
    if (d == 0) return false;

    ll t;
    while (true)
    {
        q = c/d;
        r = c%d;
        //printf("a'(%lld) a(%lld) b'(%lld) b(%lld) c(%lld) d(%lld) q(%lld) r(%lld)\n", a1, a, b1, b, c, d, q, r);
        if (r == 0) break;

        c = d;
        d = r;

        t = a1;
        a1 = a;
        a = t - q*a;

        t = b1;
        b1 = b;
        b = t - q*b;
    }
    return true;
}

inline void div(ll lhs, ll rhs, ll n)
{
    //printf("lhs(%lld) rhs(%lld)\n", lhs, rhs);
    if( rhs == 0 )      { puts("-1"); return; }
    //else if( lhs == 0 ) { puts("0");  return; }
    

    ll a, inv;
    if( extEuclid(n, rhs, a, inv) && n*a + rhs*inv == 1 )
    {
        //printf("lhs(%lld) inv(%lld)\n", lhs, inv);
        //printf("sum: %d\n", n*a + rhs*inv);
        while( inv < 0 )
            inv += n;
        inv %= n;
        mul( lhs, inv, n );
    }
    else
    {
        puts("-1");
        return;
    }
}


int main()
{
    ll n;
    int nOps;

    char op;
    ll lhs, rhs;

    scanf("%lld %d ", &n, &nOps);
    while( !(n == 0 && nOps == 0) )
    {
        //printf("n(%lld) nOps(%d)\n", n, nOps);
        while(nOps--)
        {
            scanf("%lld %c %lld ", &lhs, &op, &rhs);
            lhs %= n;
            rhs %= n;
            //printf("lhs(%lld) op(%c) rhs(%lld)\n", lhs, op, rhs);
            
            switch( op )
            {
            case '+':   add(lhs, rhs, n);
                        break;
            case '-':   sub(lhs, rhs, n);
                        break;
            case '*':   mul(lhs, rhs, n);
                        break;
            case '/':   div(lhs, rhs, n);
                        break;
            default:    throw std::invalid_argument("BAD OP");
            }

        }

        scanf("%lld %d ", &n, &nOps);
    }


    return 0;
}
