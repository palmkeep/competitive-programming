// m x n == rows x columns

#include <stdio.h>


int checkForPathFrom(m, n, start, field) int m; int n; int start; int field[m][n];
{
	int tmpField[m][n-1];
	for (int i = 0; i < m; i++){
		for (int j = 1; j < n; j++){
			tmpField[i][j-1] = field[i][j];
		}
	}
}


int main()
{
    int m,n,a,min,tmp;

    while (scanf("%d %d\n",&m,&n) == 2){
			int field[m][n];
			//printf("m x n: %d %d\n", m, n);
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++){
					scanf("%d", &field[i][j]);
					//printf("%d = field[%d][%d]\n", field[i][j], i, j);
				}
			}
			printf("\nm (row):%d, n (col):%d\n",m,n);
			for (int i = 0; i < m; i++){
				for (int j = 0; j < n; j++){
					if (j % n != 0 || (i == 0 && i == 0)){
						printf("%d ", field[i][j]);
					} else {
						printf("\n%d ", field[i][j]);
					}
				}
			}
			printf("\n\n");
			
			int found = 0;
			while (found != 1){
				for (int i = m-1; i > -1; i--){
					for (int j = 0; j < n; j++){
						printf("i: %d, j: %d, field[j][i]: %d\n", i, j, field[j][i]);
						if (field[j][i] < 1){
							if (n == i+1){
								found = 1;
								printf("found last row");
								break;
							} else if(j > m){
							} else {
								field[j-1][i+1]		= field[j-1][i+1] - 1;
								field[j][i+1]			= field[j][i+1]		- 1;
								field[j+1][i+1]		= field[j+1][i+1] - 1;
							}
						}
					}
					if (found == 1){
						break;
					}
				}
				found = 1;
			}
			/*
			for (int k = 0; k < m; k++){
				printf("\n RES:%d\n", checkForPathFrom(m, n, k, field));
			}
			*/
			//printf("%d\n",checkForPath(m, n, field));
    }
    return(0);
 }
