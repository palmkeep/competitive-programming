#include <stdio.h>
#include <vector>

int prefs[100][8];
int choice[100][8];


void print_result(int res)
{
    int d3 = (res>>2);
    int d2 = (res>>1)&1;
    int d1 = (res)&1;

    char c3 = 'Y'*(d3 == 1) + 'N'*(d3 == 0);
    char c2 = 'Y'*(d2 == 1) + 'N'*(d2 == 0);
    char c1 = 'Y'*(d1 == 1) + 'N'*(d1 == 0);
    printf("%c%c%c\n", c3, c2, c1);
}

void round(int n_pr)
{
    // Get preferences
    for (int i{0}; i < n_pr; ++i) {
        scanf("%d %d %d %d %d %d %d %d\n",
                &prefs[i][0], &prefs[i][1], &prefs[i][2], &prefs[i][3],
                &prefs[i][4], &prefs[i][5], &prefs[i][6], &prefs[i][7]
        );
    }

    for (int pr{n_pr-1}; 0 <= pr; --pr)
    {
        // For each possible state (states=[0, 7]) before a stone is turned
        // see which of the 3 outcome states would be most prefered by the
        // current priest and set that as the priests choice in the array
        if (pr < n_pr-1) {
            for (int c{0}; c < 8; ++c)
            {
                // Min value == highest preference
                int min_i   = c^1;
                int min     = prefs[pr][ choice[pr+1][c^1] ];

                if (prefs[pr][ choice[pr+1][c^2] ] < min) {
                    min_i = c^2;
                    min = prefs[pr][ choice[pr+1][c^2] ];
                }
                if (prefs[pr][ choice[pr+1][c^4] ] < min) {
                    min_i = c^4;
                    min = prefs[pr][ choice[pr+1][c^4] ];
                }
                choice[pr][c] = choice[pr+1][min_i];
            }
        } else {
            for (int c{0}; c < 8; ++c)
            {
                int min_i   = c^1;
                int min     = prefs[pr][c^1];

                if (prefs[pr][c^2] < min) {
                    min_i = c^2;
                    min = prefs[pr][c^2];
                }

                if (prefs[pr][c^4] < min) {
                    min_i = c^4;
                    min = prefs[pr][c^4];
                }
                choice[pr][c] = min_i;
            }
        }
    }

    // Last priest gets to choose which one of 1,2,4 that he likes best
    print_result(choice[0][0]);
}




int main()
{
    int n_rounds, n_priests;
    scanf("%d\n", &n_rounds);
    while (0 < n_rounds--)
    {
        scanf("%d\n", &n_priests);
        round(n_priests);
    }
}
