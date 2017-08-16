/*
ID: lizhita1
LANG: C
TASK: ariprog
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 25
#define MAX_M 251

int main() {
    int n, m, i, j, count, hasAnswer = 0;
    int bisquares[MAX_M*MAX_M*2];
    int numbers[MAX_M*MAX_M];

    FILE *fin = fopen("ariprog.in", "r");
    fscanf(fin, "%d%d", &n, &m);
    fclose(fin);

    memset(bisquares, 0, sizeof(int)*MAX_M*MAX_M*2);
    for (i=0; i<=m; ++i)
        for (j=i; j<=m; ++j) 
            bisquares[i*i+j*j] = 1;
    count = 0;
    for (i=0; i<=m*m*2; ++i)
        if (bisquares[i]) 
            numbers[count++] = i;

    FILE *fout = fopen("ariprog.out", "w");
    for (int b=1; b<=(numbers[count-1]-numbers[0])/(n-1); ++b)
        for (i=0; i<count-n+1; ++i) {
            int a = numbers[i];
            if (a+(n-1)*b>numbers[count-1])
                break;
            int last = 1;
            for (j=1; j<n; ++j)
                if (bisquares[a+j*b]==0) {
                    last = 0;
                    break;
                }
            if (last) { 
                fprintf(fout, "%d %d\n", a, b);
                hasAnswer = 1;
            }
        }
            
    if (!hasAnswer)
        fprintf(fout, "NONE\n");
    fclose(fout);
    return 0;
}
