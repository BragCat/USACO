/*
ID: lizhita1
LANG: C
TASK: money
*/

#include <stdio.h>
#include <string.h>

#define MAXV 25
#define MAXN 10000 

int main() {
    int v, n, coins[MAXV];
    FILE *fin = fopen("money.in", "r");
    fscanf(fin, "%d%d", &v, &n);
    for (int i=0; i<v; ++i)
        fscanf(fin, "%d", coins+i);
    fclose(fin);

    long long f[MAXN+1][MAXV+1];
    memset(f, 0, sizeof(f));
    for (int i=0; i<=v; ++i)
        f[0][i] = 1;
    for (int i=1; i<=n; ++i)
        for (int j=1; j<=v; ++j)
            for (int k=0; k<=i/coins[j-1]; ++k)
                f[i][j] += f[i-k*coins[j-1]][j-1]; 
    
    FILE *fout = fopen("money.out", "w");
    fprintf(fout, "%lld\n", f[n][v]);
    fclose(fout);
    return 0;
}
