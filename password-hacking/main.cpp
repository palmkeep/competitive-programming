#include <vector>
#include <algorithm>
using std::vector;
using std::sort;
#include <cstdio>

int main()
{
    int n;
    scanf("%d\n", &n);
    char c[256];
    vector<double> pwds;
    for (int i{0}; i < n; ++i) {
        double p;
        scanf("%s", c);
        scanf("%lf\n", &p);
        pwds.push_back(p);
    }
    sort(pwds.begin(), pwds.end());

    double sum = 0;
    int t = 1;
    for (vector<double>::reverse_iterator i = pwds.rbegin(); i != pwds.rend(); ++i) {
        sum += (double)t * (*i);
        t++;
    }

    printf("%lf\n", sum);
}
