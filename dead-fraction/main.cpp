#include <stdio.h>
#include <string.h>
//#include <stdexcept>

// DEBUG
// TODO: Comment out before submission
#include <iostream>
using std::cout;
using std::endl;
#define llui unsigned long long int

unsigned int pow(unsigned int b, unsigned p)
{
    unsigned int out = 1;
    for (unsigned int i = 0; i < p; i++)
        out *= b;
    return out;
}
int pow(int b, int p)
{
    int out = 1;
    for (int i = 0; i < p; i++)
        out *= b;
    return out;
}

llui gcd(llui u, llui v) {
    while (v != 0) {
        llui r = u % v;
        u = v;
        v = r;
    }
    return u;
}

void handle(llui a,
            llui b,
            int i, int l, 
            llui& s_a, 
            llui& s_b)
{
    /*
    cout << "i: " << i << endl;
    cout << "l: " << l << endl;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "smallest a: " << s_a << endl;
    cout << "smallest b: " << s_b << endl;
    */

    llui mul = 0;
    llui num;
    for (int j = 0; j < l - i; j++)
    {
        mul += 9*pow(10,j);
    }
    //cout << "mul: " << mul << endl;
    num = a*mul+b;
    llui den = mul;
    for (int j = 0; j < i; j++)
        den *= 10;

    llui tmp = gcd(num, den);
    
    if (den/tmp < s_b)
    {
        s_b = den/tmp;
        s_a = num/tmp;
    }
    /*
    cout << "numerator: " << num/tmp << endl;
    cout << "denomenator: " << den/tmp << endl;
    cout << endl;
    */
    return;
}


int main()
{
    char buf[13];
    buf[12] = '\0';
    scanf("0.%s...", buf);

    bool loop = true;
    char nstr[13];
    while(loop)
    {
        strcpy(nstr, buf);
        char* p = nstr;
        while (*p != '.')
            p++;
        *p = '\0';

        if (scanf(" 0.%s...", buf) == EOF)
        {
            //cout << "END: " << buf << endl;
            break;
        }
        else
        {
            int str_len = strlen(nstr);
            llui last_d = (int)(*(nstr+str_len-1)-'0') % 48; // Convert last char to int

            llui a;
            llui b;
            llui s_a;
            llui s_b;
            //llui d_i;
            char n[32];
            char d[32];
            if (str_len == 1)
            {
                if (last_d == 9)
                {
                    puts("1/1");    // !!! Correct format?
                    //throw std::invalid_argument("ASGINAOSPGVIN");
                }
                else if (last_d == 0)
                {
                    puts("0/1");    // -||-
                    //throw std::invalid_argument("ASGINAOSPGVIN");
                }
                else
                {
                    int tmp = (nstr[0] - '0')%48;
                    int d = 9;
                    int g = gcd(tmp,9);
                    tmp = tmp/g;
                    d = d/g;

                    char num[1];
                    char den[1];
                    sprintf(num, "%d", tmp);
                    sprintf(den, "%d", d);
                    fputs(num, stdout);
                    fputs("/", stdout);
                    fputs(den, stdout);
                    fputs("\n", stdout);

                }
                //cout << endl << endl;
            }
            else
            {
                /*
                cout << "str: " << nstr << endl;
                cout << "strln: " << str_len << endl;
                cout << "[BEGIN] iter" << endl << endl;
                */
                s_a = (unsigned)-1;
                s_b = (unsigned)-1;
                for (int i = 0; i < str_len; i++)
                {
                    a = 0;
                    b = 0;
                    for (int j = 0; j < i; j++)
                    {
                        a += ((nstr[j]-'0') % 48) * pow(10, i-j-1);
                    }
                    for (int j = str_len - 1; j >= i; j--)
                    {
                        b += ((nstr[j]-'0') % 48) * pow(10, str_len - 1 -j );
                    }
                    handle(a, b, i, str_len, s_a, s_b);

                }
                sprintf(n, "%llu", s_a);
                sprintf(d, "%llu", s_b);
                fputs(n, stdout);
                fputs("/", stdout);
                fputs(d, stdout);
                fputs("\n", stdout);
            }
        }
    }
    return 0;
}
