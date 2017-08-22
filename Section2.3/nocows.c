/*
ID: lizhita1
LANG: C
TASK: nocows
*/

#include <stdio.h>
#include <string.h>

#define MAXN 200
#define MAXK 100
#define MODULO 9901

int main() {
    int n, k, f[MAXK][MAXN];
    FILE *fin = fopen("nocows.in", "r");
    fscanf(fin, "%d%d", &n, &k);
    fclose(fin); 

    memset(f, 0, sizeof(f));
    
    for (int i=1; i<=k; ++i)
        f[i][1] = 1;
    for (int i=2; i<=k; ++i) 
        for (int j=3; j<=n; j+=2) 
            for (int k=1; k<j; k+=2)
                f[i][j] = (f[i][j]+f[i-1][k]*f[i-1][j-1-k])%MODULO;

    FILE *fout = fopen("nocows.out", "w");
    fprintf(fout, "%d\n", (f[k][n]-f[k-1][n]+MODULO)%MODULO);
    fclose(fout);
    return 0;
}
